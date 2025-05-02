#pragma once

#include "pstl/utils/benchmark_naming.h"

#include <benchmark/benchmark.h>

#include "transform_inclusive_scan_utils.h"

#include "transform_inclusive_scan_std.h"

#ifdef PSTL_BENCH_USE_HPX
#include "transform_inclusive_scan_hpx.h"
#endif

#ifdef PSTL_BENCH_USE_ONEDPL
#include "transform_inclusive_scan_onedpl.h"
#endif

//region transform_inclusive_scan
template<class Policy>
static void transform_inclusive_scan_std_wrapper(benchmark::State & state)
{
	benchmark_transform_inclusive_scan::benchmark_wrapper<Policy>(
	    state, benchmark_transform_inclusive_scan::transform_inclusive_scan_std);
}

#define TRANSFORM_INCLUSIVE_SCAN_SEQ_WRAPPER                                                    \
	BENCHMARK_TEMPLATE1(transform_inclusive_scan_std_wrapper, std::execution::sequenced_policy) \
	    ->Name(PSTL_BENCH_BENCHMARK_NAME_WITH_BACKEND("SEQ", "std::transform_inclusive_scan"))  \
	    ->PSTL_BENCH_BENCHMARK_PARAMETERS

#ifdef PSTL_BENCH_USE_PSTL
#define TRANSFORM_INCLUSIVE_SCAN_STD_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(transform_inclusive_scan_std_wrapper, std::execution::parallel_unsequenced_policy) \
	    ->Name(PSTL_BENCH_BENCHMARK_NAME("std::transform_inclusive_scan"))                                 \
	    ->PSTL_BENCH_BENCHMARK_PARAMETERS
#else
#define TRANSFORM_INCLUSIVE_SCAN_STD_WRAPPER
#endif
//endregion transform_inclusive_scan

//region transform_inclusive_scan_hpx
#ifdef PSTL_BENCH_USE_HPX
template<class Policy>
static void transform_inclusive_scan_hpx_wrapper(benchmark::State & state)
{
	benchmark_transform_inclusive_scan::benchmark_wrapper<Policy>(
	    state, benchmark_transform_inclusive_scan::transform_inclusive_scan_hpx);
}

#define TRANSFORM_INCLUSIVE_SCAN_HPX_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(transform_inclusive_scan_hpx_wrapper, hpx::execution::parallel_unsequenced_policy) \
	    ->Name(PSTL_BENCH_BENCHMARK_NAME("hpx::transform_inclusive_scan"))                                 \
	    ->PSTL_BENCH_BENCHMARK_PARAMETERS
#else
#define TRANSFORM_INCLUSIVE_SCAN_HPX_WRAPPER
#endif
//endregion transform_inclusive_scan_hpx

//region transform_inclusive_scan_onedpl
#ifdef PSTL_BENCH_USE_ONEDPL
template<class Policy>
static void transform_inclusive_scan_onedpl_wrapper(benchmark::State & state)
{
	benchmark_transform_inclusive_scan::benchmark_wrapper<Policy>(
	    state, benchmark_transform_inclusive_scan::transform_inclusive_scan_onedpl);
}

/*
the std policy is just a placeholder, it will use oneapi::dpl::execution::dpcpp_default when executing the algorithm. 
Check the algorithm implementation.
*/
#define TRANSFORM_INCLUSIVE_SCAN_ONEDPL_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(transform_inclusive_scan_onedpl_wrapper, std::execution::parallel_unsequenced_policy) \
	    ->Name(PSTL_BENCH_BENCHMARK_NAME("onedpl::transform_inclusive_scan"))                                 \
	    ->PSTL_BENCH_BENCHMARK_PARAMETERS
#else
#define TRANSFORM_INCLUSIVE_SCAN_ONEDPL_WRAPPER
#endif
//endregion transform_inclusive_scan_onedpl

#define TRANSFORM_INCLUSIVE_SCAN_GROUP   \
	TRANSFORM_INCLUSIVE_SCAN_SEQ_WRAPPER \
	TRANSFORM_INCLUSIVE_SCAN_STD_WRAPPER \
	TRANSFORM_INCLUSIVE_SCAN_HPX_WRAPPER \
	TRANSFORM_INCLUSIVE_SCAN_ONEDPL_WRAPPER

TRANSFORM_INCLUSIVE_SCAN_GROUP