#pragma once

#include "pstl/utils/benchmark_naming.h"

#include <benchmark/benchmark.h>

#include "transform_exclusive_scan_utils.h"

#include "transform_exclusive_scan_std.h"

#ifdef PSTL_BENCH_USE_HPX
#include "transform_exclusive_scan_hpx.h"
#endif

#ifdef PSTL_BENCH_USE_ONE_DPL
#include "transform_exclusive_scan_one_dpl.h"
#endif

//region transform_exclusive_scan
template<class Policy>
static void transform_exclusive_scan_std_wrapper(benchmark::State & state)
{
	benchmark_transform_exclusive_scan::benchmark_wrapper<Policy>(
	    state, benchmark_transform_exclusive_scan::transform_exclusive_scan_std);
}

#define TRANSFORM_EXCLUSIVE_SCAN_SEQ_WRAPPER                                                    \
	BENCHMARK_TEMPLATE1(transform_exclusive_scan_std_wrapper, std::execution::sequenced_policy) \
	    ->Name(PSTL_BENCH_BENCHMARK_NAME_WITH_BACKEND("SEQ", "std::transform_exclusive_scan"))  \
	    ->PSTL_BENCH_BENCHMARK_PARAMETERS

#ifdef PSTL_BENCH_USE_PSTL
#define TRANSFORM_EXCLUSIVE_SCAN_STD_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(transform_exclusive_scan_std_wrapper, std::execution::parallel_unsequenced_policy) \
	    ->Name(PSTL_BENCH_BENCHMARK_NAME("std::transform_exclusive_scan"))                                 \
	    ->PSTL_BENCH_BENCHMARK_PARAMETERS
#else
#define TRANSFORM_EXCLUSIVE_SCAN_STD_WRAPPER
#endif
//endregion transform_exclusive_scan

//region transform_exclusive_scan_hpx
#ifdef PSTL_BENCH_USE_HPX
template<class Policy>
static void transform_exclusive_scan_hpx_wrapper(benchmark::State & state)
{
	benchmark_transform_exclusive_scan::benchmark_wrapper<Policy>(
	    state, benchmark_transform_exclusive_scan::transform_exclusive_scan_hpx);
}

#define TRANSFORM_EXCLUSIVE_SCAN_HPX_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(transform_exclusive_scan_hpx_wrapper, hpx::execution::parallel_unsequenced_policy) \
	    ->Name(PSTL_BENCH_BENCHMARK_NAME("hpx::transform_exclusive_scan"))                                 \
	    ->PSTL_BENCH_BENCHMARK_PARAMETERS
#else
#define TRANSFORM_EXCLUSIVE_SCAN_HPX_WRAPPER
#endif
//endregion transform_exclusive_scan_hpx

//region transform_exclusive_scan_one_dpl
#ifdef PSTL_BENCH_USE_ONE_DPL
template<class Policy>
static void transform_exclusive_scan_one_dpl_wrapper(benchmark::State & state)
{
	benchmark_transform_exclusive_scan::benchmark_wrapper<Policy>(
	    state, benchmark_transform_exclusive_scan::transform_exclusive_scan_one_dpl);
}

/*
the std policy is just a placeholder, it will use oneapi::dpl::execution::dpcpp_default when executing the algorithm. 
Check the algorithm implementation.
*/
#define TRANSFORM_EXCLUSIVE_SCAN_ONE_DPL_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(transform_exclusive_scan_one_dpl_wrapper, std::execution::parallel_unsequenced_policy) \
	    ->Name(PSTL_BENCH_BENCHMARK_NAME("oneDPL::transform_exclusive_scan"))                                  \
	    ->PSTL_BENCH_BENCHMARK_PARAMETERS
#else
#define TRANSFORM_EXCLUSIVE_SCAN_ONE_DPL_WRAPPER
#endif
//endregion transform_exclusive_scan_one_dpl

#define TRANSFORM_EXCLUSIVE_SCAN_GROUP   \
	TRANSFORM_EXCLUSIVE_SCAN_SEQ_WRAPPER \
	TRANSFORM_EXCLUSIVE_SCAN_STD_WRAPPER \
	TRANSFORM_EXCLUSIVE_SCAN_HPX_WRAPPER \
	TRANSFORM_EXCLUSIVE_SCAN_ONE_DPL_WRAPPER

TRANSFORM_EXCLUSIVE_SCAN_GROUP