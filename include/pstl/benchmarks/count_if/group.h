#pragma once

#include "pstl/utils/benchmark_naming.h"

#include "count_if_utils.h"

#include "count_if_std.h"

#ifdef PSTL_BENCH_USE_GNU
#include "count_if_gnu.h"
#endif

#ifdef PSTL_BENCH_USE_HPX
#include "count_if_hpx.h"
#endif

#ifdef PSTL_BENCH_USE_ONE_DPL
#include "count_if_one_dpl.h"
#endif

//region count_if_std
template<class Policy>
static void count_if_std_wrapper(benchmark::State & state)
{
	benchmark_count_if::benchmark_wrapper<Policy>(state, benchmark_count_if::count_if_std);
}

#define COUNT_IF_SEQ_WRAPPER                                                    \
	BENCHMARK_TEMPLATE1(count_if_std_wrapper, std::execution::sequenced_policy) \
	    ->Name(PSTL_BENCH_BENCHMARK_NAME_WITH_BACKEND("SEQ", "std::count_if"))  \
	    ->PSTL_BENCH_BENCHMARK_PARAMETERS

#ifdef PSTL_BENCH_USE_PSTL
#define COUNT_IF_STD_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(count_if_std_wrapper, std::execution::parallel_unsequenced_policy) \
	    ->Name(PSTL_BENCH_BENCHMARK_NAME("std::count_if"))                                 \
	    ->PSTL_BENCH_BENCHMARK_PARAMETERS
#else
#define COUNT_IF_STD_WRAPPER
#endif
//endregion count_if_std

//region count_if_gnu
#ifdef PSTL_BENCH_USE_GNU
template<class Policy>
static void count_if_gnu_wrapper(benchmark::State & state)
{
	benchmark_count_if::benchmark_wrapper<Policy>(state, benchmark_count_if::count_if_gnu);
}

#define COUNT_IF_GNU_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(count_if_gnu_wrapper, std::execution::parallel_unsequenced_policy) \
	    ->Name(PSTL_BENCH_BENCHMARK_NAME("gnu::count_if"))                                 \
	    ->PSTL_BENCH_BENCHMARK_PARAMETERS
#else
#define COUNT_IF_GNU_WRAPPER
#endif
//endregion count_if_gnu

//region count_if_hpx
#ifdef PSTL_BENCH_USE_HPX
template<class Policy>
static void count_if_hpx_wrapper(benchmark::State & state)
{
	benchmark_count_if::benchmark_wrapper<Policy>(state, benchmark_count_if::count_if_hpx);
}

#define COUNT_IF_HPX_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(count_if_hpx_wrapper, hpx::execution::parallel_unsequenced_policy) \
	    ->Name(PSTL_BENCH_BENCHMARK_NAME("hpx::count_if"))                                 \
	    ->PSTL_BENCH_BENCHMARK_PARAMETERS
#else
#define COUNT_IF_HPX_WRAPPER
#endif
//endregion count_if_hpx

//region count_if_one_dpl
#ifdef PSTL_BENCH_USE_ONE_DPL
template<class Policy>
static void count_if_one_dpl_wrapper(benchmark::State & state)
{
	benchmark_count_if::benchmark_wrapper<Policy>(state, benchmark_count_if::count_if_one_dpl);
}

/*
the std policy is just a placeholder, it will use oneapi::dpl::execution::dpcpp_default when executing the algorithm. 
Check the algorithm implementation.
*/
#define COUNT_IF_ONE_DPL_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(count_if_one_dpl_wrapper, std::execution::parallel_unsequenced_policy) \
	    ->Name(PSTL_BENCH_BENCHMARK_NAME("oneDPL::count_if"))                                  \
	    ->PSTL_BENCH_BENCHMARK_PARAMETERS
#else
#define COUNT_IF_ONE_DPL_WRAPPER
#endif
//endregion count_if_one_dpl

#define COUNT_IF_GROUP   \
	COUNT_IF_SEQ_WRAPPER \
	COUNT_IF_STD_WRAPPER \
	COUNT_IF_GNU_WRAPPER \
	COUNT_IF_HPX_WRAPPER \
	COUNT_IF_ONE_DPL_WRAPPER

COUNT_IF_GROUP