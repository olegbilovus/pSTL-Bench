#ifndef PSTL_BENCH_ADJACENT_DIFFERENCE_GROUP_H
#define PSTL_BENCH_ADJACENT_DIFFERENCE_GROUP_H

#include "benchmark_prefix.h"

#include "adjacent_difference_utils.h"

#include "adjacent_difference_std.h"

#ifdef USE_GNU
#include "adjacent_difference_gnu.h"
#endif

#ifdef USE_HPX
#include "adjacent_difference_hpx.h"
#endif

//region adjacent_difference_std
template<class Policy>
static void adjacent_difference_std_wrapper(benchmark::State & state)
{
	benchmark_adjacent_difference::benchmark_wrapper<Policy>(state,
	                                                         benchmark_adjacent_difference::adjacent_difference_std);
}

#define ADJACENT_DIFFERENCE_SEQ_WRAPPER                                                    \
	BENCHMARK_TEMPLATE1(adjacent_difference_std_wrapper, std::execution::sequenced_policy) \
	    ->Name(BENCHMARK_NAME_WITH_BACKEND("SEQ", "std::adjacent_difference"))             \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                            \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE);

#ifdef USE_PSTL
#define ADJACENT_DIFFERENCE_STD_WRAPPER                                                   \
	BENCHMARK_TEMPLATE1(adjacent_difference_std_wrapper, std::execution::parallel_policy) \
	    ->Name(BENCHMARK_NAME("std::adjacent_difference"))                                \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                           \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE);
#else
#define ADJACENT_DIFFERENCE_STD_WRAPPER
#endif
//endregion adjacent_difference_std

//region adjacent_difference_gnu
#ifdef USE_GNU
template<class Policy>
static void adjacent_difference_gnu_wrapper(benchmark::State & state)
{
	benchmark_adjacent_difference::benchmark_wrapper<Policy>(state,
	                                                         benchmark_adjacent_difference::adjacent_difference_gnu);
}

#define ADJACENT_DIFFERENCE_GNU_WRAPPER                                                   \
	BENCHMARK_TEMPLATE1(adjacent_difference_gnu_wrapper, std::execution::parallel_policy) \
	    ->Name(BENCHMARK_NAME("gnu::adjacent_difference"))                                \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                           \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE);
#else
#define ADJACENT_DIFFERENCE_GNU_WRAPPER
#endif
//endregion adjacent_difference_gnu

//region adjacent_difference_hpx
#ifdef USE_HPX
template<class Policy>
static void adjacent_difference_hpx_wrapper(benchmark::State & state)
{
	benchmark_adjacent_difference::benchmark_wrapper<Policy>(state,
	                                                         benchmark_adjacent_difference::adjacent_difference_hpx);
}

#define ADJACENT_DIFFERENCE_HPX_WRAPPER                                                   \
	BENCHMARK_TEMPLATE1(adjacent_difference_hpx_wrapper, std::execution::parallel_policy) \
	    ->Name(BENCHMARK_NAME("hpx::adjacent_difference"))                                \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                           \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE);
#else
#define ADJACENT_DIFFERENCE_HPX_WRAPPER
#endif

#define ADJACENT_DIFFERENCE_GROUP   \
	ADJACENT_DIFFERENCE_SEQ_WRAPPER \
	ADJACENT_DIFFERENCE_STD_WRAPPER \
	ADJACENT_DIFFERENCE_HPX_WRAPPER

#endif //PSTL_BENCH_ADJACENT_DIFFERENCE_GROUP_H
