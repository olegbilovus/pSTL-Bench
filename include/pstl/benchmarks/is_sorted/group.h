#pragma once

#include "pstl/utils/benchmark_naming.h"

#include "is_sorted_utils.h"

#include "is_sorted_std.h"

#ifdef PSTL_BENCH_USE_HPX
#include "is_sorted_hpx.h"
#endif

#ifdef PSTL_BENCH_USE_ONEDPL
#include "is_sorted_onedpl.h"
#endif

//region is_sorted_std
template<class Policy>
static void is_sorted_std_wrapper(benchmark::State & state)
{
	benchmark_is_sorted::benchmark_wrapper<Policy>(state, benchmark_is_sorted::is_sorted_std);
}

#define IS_SORTED_SEQ_WRAPPER                                                    \
	BENCHMARK_TEMPLATE1(is_sorted_std_wrapper, std::execution::sequenced_policy) \
	    ->Name(PSTL_BENCH_BENCHMARK_NAME_WITH_BACKEND("SEQ", "std::is_sorted"))  \
	    ->PSTL_BENCH_BENCHMARK_PARAMETERS

#ifdef PSTL_BENCH_USE_PSTL
#define IS_SORTED_STD_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(is_sorted_std_wrapper, std::execution::parallel_unsequenced_policy) \
	    ->Name(PSTL_BENCH_BENCHMARK_NAME("std::is_sorted"))                                 \
	    ->PSTL_BENCH_BENCHMARK_PARAMETERS
#else
#define IS_SORTED_STD_WRAPPER
#endif
//endregion is_sorted_std

//region is_sorted_hpx
#ifdef PSTL_BENCH_USE_HPX
template<class Policy>
static void is_sorted_hpx_wrapper(benchmark::State & state)
{
	benchmark_is_sorted::benchmark_wrapper<Policy>(state, benchmark_is_sorted::is_sorted_hpx);
}

#define IS_SORTED_HPX_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(is_sorted_hpx_wrapper, hpx::execution::parallel_unsequenced_policy) \
	    ->Name(PSTL_BENCH_BENCHMARK_NAME("hpx::is_sorted"))                                 \
	    ->PSTL_BENCH_BENCHMARK_PARAMETERS
#else
#define IS_SORTED_HPX_WRAPPER
#endif
//endregion is_sorted_hpx

//region is_sorted_onedpl
#ifdef PSTL_BENCH_USE_ONEDPL
template<class Policy>
static void is_sorted_onedpl_wrapper(benchmark::State & state)
{
	benchmark_is_sorted::benchmark_wrapper<Policy>(state, benchmark_is_sorted::is_sorted_onedpl);
}

/*
the std policy is just a placeholder, it will use oneapi::dpl::execution::dpcpp_default when executing the algorithm. 
Check the algorithm implementation.
*/
#define IS_SORTED_ONEDPL_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(is_sorted_onedpl_wrapper, std::execution::parallel_unsequenced_policy) \
	    ->Name(PSTL_BENCH_BENCHMARK_NAME("onedpl::is_sorted"))                                 \
	    ->PSTL_BENCH_BENCHMARK_PARAMETERS
#else
#define IS_SORTED_ONEDPL_WRAPPER
#endif
//endregion is_sorted_onedpl

#define IS_SORTED_GROUP   \
	IS_SORTED_SEQ_WRAPPER \
	IS_SORTED_STD_WRAPPER \
	IS_SORTED_HPX_WRAPPER \
	IS_SORTED_ONEDPL_WRAPPER

IS_SORTED_GROUP