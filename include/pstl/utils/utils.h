#pragma once

#include <algorithm>
#include <iostream>
#include <limits>
#include <type_traits>

#include <benchmark/benchmark.h>

#ifdef PSTL_BENCH_USE_PAR_ALLOC
#include "pstl/utils/par_alloc.h"
#endif

#include "pstl/utils/input_gen.h"
#include "pstl/utils/timing.h"

extern int GLOBAL_NUM_THREADS;

#define PSTL_BENCH_CUSTOM_STATISTICS                                                                                   \
	ComputeStatistics("max", [](const auto & v) -> double { return *(std::max_element(std::begin(v), std::end(v))); }) \
	    ->ComputeStatistics("min",                                                                                     \
	                        [](const auto & v) -> double { return *(std::min_element(std::begin(v), std::end(v))); })  \
	    ->UseManualTime()

#define PSTL_BENCH_BENCHMARK_PARAMETERS                               \
	PSTL_BENCH_CUSTOM_STATISTICS->RangeMultiplier(2)                  \
	    ->Range(PSTL_BENCH_MIN_INPUT_SIZE, PSTL_BENCH_MAX_INPUT_SIZE) \
	    ->UseManualTime();

namespace pstl
{
	/**
	 * Computes (an estimation) the amount of bytes used by a container
	 * @param container the container to compute the size for
	 * @return the amount of (estimated) bytes used by the container
	 */
	static auto container_size(const auto & container)
	{
		using base_type = std::decay_t<decltype(container)>;
		return sizeof(base_type) * container.size() + sizeof(container);
	}

	/**
	 * Compute the amount of bytes computed by a benchmark
	 *
	 * @param state the benchmark state
	 * @param containers the containers used by the benchmark
	 * @return the amount of bytes computed by the benchmark
	 */
	static auto computed_bytes(const ::benchmark::State & state, const auto &... containers)
	{
		std::size_t bytes = 0;

		const auto accumulate_bytes = [&bytes](const auto & container) {
			bytes += pstl::container_size(container);
		};

		// Use fold expression to iterate over all containers even when they have different types
		(accumulate_bytes(containers), ...);

		return bytes * state.iterations();
	}

	/**
	 * Add custom statistics to every benchmark
	 * @param state the benchmark state
	 * @param containers the containers used by the benchmark
	 */
	static void add_global_custom_statistics(::benchmark::State & state, const auto &... containers)
	{
		// Add computed bytes to the benchmark
		const auto bytes = computed_bytes(state, containers...);
		state.SetBytesProcessed(bytes);

#ifndef PSTL_BENCH_USE_GPU
		// Add the number of threads to the benchmark
		state.counters.insert({ "used_threads", GLOBAL_NUM_THREADS });
#endif
	}

	/**
	 * Check if two values are equivalent, i.e. if they are equal or if they are within a certain tolerance
	 * @param v1 First value
	 * @param v2 Second value
	 * @return
	 */
	template<typename T, typename U, std::enable_if_t<std::is_integral_v<T> and std::is_integral_v<U>, bool> = true>
	static bool are_equivalent(const T & v1, const U & v2)
	{
		const auto are_eq = v1 == v2;

		if (not are_eq) { std::cerr << "Values are not equivalent: " << v1 << " != " << v2 << std::endl; }

		return are_eq;
	}

	/**
	 * Check if two values are equivalent, i.e. if they are equal or if they are within a certain tolerance
	 * @param v1 First value
	 * @param v2 Second value
	 * @return
	 */
	template<typename T, typename U,
	         std::enable_if_t<std::is_floating_point_v<T> and std::is_floating_point_v<U>, bool> = true>
	static bool are_equivalent(const T & v1, const U & v2)
	{
		using fp_t = std::decay_t<decltype(v1)>;

		static constexpr auto DEFAULT_ABSOLUTE_TOLERANCE = std::numeric_limits<T>::epsilon();
		static constexpr auto DEFAULT_RELATIVE_TOLERANCE = 0.01; // 1% tolerance

		static const auto ABSOLUTE_TOLERANCE = std::getenv("PSTL_BENCH_ABS_TOL") == nullptr ?
		                                           DEFAULT_ABSOLUTE_TOLERANCE :
		                                           std::strtod(std::getenv("PSTL_BENCH_ABS_TOL"), nullptr);
		static const auto RELATIVE_TOLERANCE = std::getenv("PSTL_BENCH_REL_TOL") == nullptr ?
		                                           DEFAULT_RELATIVE_TOLERANCE :
		                                           std::strtod(std::getenv("PSTL_BENCH_REL_TOL"), nullptr);

		const auto abs_error = std::abs(v1 - v2);
		const auto rel_error = abs_error / std::max(std::abs(v1), std::abs(v2));

		const auto are_eq = abs_error <= ABSOLUTE_TOLERANCE or rel_error <= RELATIVE_TOLERANCE;

		if (not are_eq)
		{
			std::cerr << "Values are not equivalent: " << v1 << " != " << v2 << ". Abs. error: " << abs_error
			          << ", rel. error: " << rel_error << ". Abs. tol.: " << ABSOLUTE_TOLERANCE
			          << ", rel. tol.: " << RELATIVE_TOLERANCE << std::endl;
		}

		return are_eq;
	}

	/**
	 * Check if two values are equivalent, i.e. if they are equal or if they are within a certain tolerance
	 * @param v1 First value
	 * @param v2 Second value
	 * @return
	 */
	template<typename T, typename U,
	         std::enable_if_t<not std::is_arithmetic_v<T> or not std::is_arithmetic_v<U>, bool> = true>
	static bool are_equivalent(const T & v1, const U & v2)
	{
		return v1 == v2;
	}
} // namespace pstl
