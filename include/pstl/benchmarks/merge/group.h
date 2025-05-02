#pragma once

#include "pstl/utils/benchmark_naming.h"

#include "merge_utils.h"

#include "merge_std.h"

#ifdef PSTL_BENCH_USE_GNU
#include "merge_gnu.h"
#endif

#ifdef PSTL_BENCH_USE_HPX
#include "merge_hpx.h"
#endif

#ifdef PSTL_BENCH_USE_ONE_DPL
#include "merge_one_dpl.h"
#endif

//region merge_std
template<class Policy>
static void merge_std_wrapper(benchmark::State & state)
{
	benchmark_merge::benchmark_wrapper<Policy>(state, benchmark_merge::merge_std);
}

#define MERGE_SEQ_WRAPPER                                                    \
	BENCHMARK_TEMPLATE1(merge_std_wrapper, std::execution::sequenced_policy) \
	    ->Name(PSTL_BENCH_BENCHMARK_NAME_WITH_BACKEND("SEQ", "std::merge"))  \
	    ->PSTL_BENCH_BENCHMARK_PARAMETERS

#ifdef PSTL_BENCH_USE_PSTL
#define MERGE_STD_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(merge_std_wrapper, std::execution::parallel_unsequenced_policy) \
	    ->Name(PSTL_BENCH_BENCHMARK_NAME("std::merge"))                                 \
	    ->PSTL_BENCH_BENCHMARK_PARAMETERS
#else
#define MERGE_STD_WRAPPER
#endif
//endregion merge_std

//region merge_gnu
#ifdef PSTL_BENCH_USE_GNU
template<class Policy>
static void merge_gnu_wrapper(benchmark::State & state)
{
	benchmark_merge::benchmark_wrapper<Policy>(state, benchmark_merge::merge_gnu);
}

#define MERGE_GNU_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(merge_gnu_wrapper, std::execution::parallel_unsequenced_policy) \
	    ->Name(PSTL_BENCH_BENCHMARK_NAME("gnu::merge"))                                 \
	    ->PSTL_BENCH_BENCHMARK_PARAMETERS
#else
#define MERGE_GNU_WRAPPER
#endif
//endregion merge_gnu

//region merge_hpx
#ifdef PSTL_BENCH_USE_HPX
template<class Policy>
static void merge_hpx_wrapper(benchmark::State & state)
{
	benchmark_merge::benchmark_wrapper<Policy>(state, benchmark_merge::merge_hpx);
}

#define MERGE_HPX_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(merge_hpx_wrapper, hpx::execution::parallel_unsequenced_policy) \
	    ->Name(PSTL_BENCH_BENCHMARK_NAME("hpx::merge"))                                 \
	    ->PSTL_BENCH_BENCHMARK_PARAMETERS
#else
#define MERGE_HPX_WRAPPER
#endif
//endregion merge_hpx

//region merge_one_dpl
#ifdef PSTL_BENCH_USE_ONE_DPL
template<class Policy>
static void merge_one_dpl_wrapper(benchmark::State & state)
{
	benchmark_merge::benchmark_wrapper<Policy>(state, benchmark_merge::merge_one_dpl);
}

/*
the std policy is just a placeholder, it will use oneapi::dpl::execution::dpcpp_default when executing the algorithm. 
Check the algorithm implementation.
*/
#define MERGE_ONE_DPL_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(merge_one_dpl_wrapper, std::execution::parallel_unsequenced_policy) \
	    ->Name(PSTL_BENCH_BENCHMARK_NAME("oneDPL::merge"))                                  \
	    ->PSTL_BENCH_BENCHMARK_PARAMETERS
#else
#define MERGE_ONE_DPL_WRAPPER
#endif
//endregion merge_one_dpl

#define MERGE_GROUP   \
	MERGE_SEQ_WRAPPER \
	MERGE_STD_WRAPPER \
	MERGE_GNU_WRAPPER \
	MERGE_HPX_WRAPPER \
	MERGE_ONE_DPL_WRAPPER

MERGE_GROUP