#pragma once

#include "pstl/utils/benchmark_naming.h"

#include "inclusive_scan_utils.h"

#include "inclusive_scan_std.h"

#ifdef PSTL_BENCH_USE_HPX
#include "inclusive_scan_hpx.h"
#endif

#ifdef PSTL_BENCH_USE_ONEDPL
#include "inclusive_scan_onedpl.h"
#endif

//region inclusive_scan_std
template<class Policy>
static void inclusive_scan_std_wrapper(benchmark::State & state)
{
	benchmark_inclusive_scan::benchmark_wrapper<Policy>(state, benchmark_inclusive_scan::inclusive_scan_std);
}

#define INCLUSIVE_SCAN_SEQ_WRAPPER                                                    \
	BENCHMARK_TEMPLATE1(inclusive_scan_std_wrapper, std::execution::sequenced_policy) \
	    ->Name(PSTL_BENCH_BENCHMARK_NAME_WITH_BACKEND("SEQ", "std::inclusive_scan"))  \
	    ->PSTL_BENCH_BENCHMARK_PARAMETERS

#ifdef PSTL_BENCH_USE_PSTL
#define INCLUSIVE_SCAN_STD_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(inclusive_scan_std_wrapper, std::execution::parallel_unsequenced_policy) \
	    ->Name(PSTL_BENCH_BENCHMARK_NAME("std::inclusive_scan"))                                 \
	    ->PSTL_BENCH_BENCHMARK_PARAMETERS
#else
#define INCLUSIVE_SCAN_STD_WRAPPER
#endif
//endregion inclusive_scan_std

//region inclusive_scan_hpx
#ifdef PSTL_BENCH_USE_HPX
template<class Policy>
static void inclusive_scan_hpx_wrapper(benchmark::State & state)
{
	benchmark_inclusive_scan::benchmark_wrapper<Policy>(state, benchmark_inclusive_scan::inclusive_scan_hpx);
}

#define INCLUSIVE_SCAN_HPX_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(inclusive_scan_hpx_wrapper, hpx::execution::parallel_unsequenced_policy) \
	    ->Name(PSTL_BENCH_BENCHMARK_NAME("hpx::inclusive_scan"))                                 \
	    ->PSTL_BENCH_BENCHMARK_PARAMETERS
#else
#define INCLUSIVE_SCAN_HPX_WRAPPER
#endif
//endregion inclusive_scan_hpx

//region inclusive_scan_onedpl
#ifdef PSTL_BENCH_USE_ONEDPL
template<class Policy>
static void inclusive_scan_onedpl_wrapper(benchmark::State & state)
{
	benchmark_inclusive_scan::benchmark_wrapper<Policy>(state, benchmark_inclusive_scan::inclusive_onedpl);
}

/*
the std policy is just a placeholder, it will use oneapi::dpl::execution::dpcpp_default when executing the algorithm. 
Check the algorithm implementation.
*/
#define INCLUSIVE_SCAN_ONEDPL_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(inclusive_scan_onedpl_wrapper, std::execution::parallel_unsequenced_policy) \
	    ->Name(PSTL_BENCH_BENCHMARK_NAME("onedpl::inclusive_scan"))                                 \
	    ->PSTL_BENCH_BENCHMARK_PARAMETERS
#else
#define INCLUSIVE_SCAN_ONEDPL_WRAPPER
#endif
//endregion inclusive_scan_onedpl

#define INCLUSIVE_SCAN_GROUP   \
	INCLUSIVE_SCAN_SEQ_WRAPPER \
	INCLUSIVE_SCAN_STD_WRAPPER \
	INCLUSIVE_SCAN_HPX_WRAPPER \
	INCLUSIVE_SCAN_ONEDPL_WRAPPER

INCLUSIVE_SCAN_GROUP