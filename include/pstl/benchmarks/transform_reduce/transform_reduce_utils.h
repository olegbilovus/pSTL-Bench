#pragma once

#include "pstl/utils/utils.h"

#include <benchmark/benchmark.h>

namespace benchmark_transform_reduce
{
	const auto transform_kernel = [](const auto & input) {
		return input * input;
	};

	template<class Policy, class Function>
	static void benchmark_wrapper(benchmark::State & state, Function && f)
	{
		constexpr auto execution_policy = Policy{};

		const auto & size = state.range(0);

		auto input = pstl::generate_increment(execution_policy, size);

		const auto solution = std::transform_reduce(std::execution::seq, input.cbegin(), input.cend(), pstl::elem_t{},
		                                            std::plus<>(), transform_kernel);

		for (auto _ : state)
		{
			const auto output =
			    pstl::wrap_timing(state, std::forward<Function>(f), execution_policy, input, transform_kernel);

			assert(pstl::are_equivalent(solution, output));
		}

		pstl::add_global_custom_statistics(state, input);
	}
} // namespace benchmark_transform_reduce
