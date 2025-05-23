#pragma once

#include "pstl/utils/benchmark_naming.h"

#include "fill_utils.h"

#include "fill_std.h"

#ifdef PSTL_BENCH_USE_HPX
#include "fill_hpx.h"
#endif

#ifdef PSTL_BENCH_USE_ONEDPL
#include "fill_onedpl.h"
#endif

//region fill_std
template<class Policy>
static void fill_std_wrapper(benchmark::State & state)
{
	benchmark_fill::benchmark_wrapper<Policy>(state, benchmark_fill::fill_std);
}

#define FILL_SEQ_WRAPPER                                                    \
	BENCHMARK_TEMPLATE1(fill_std_wrapper, std::execution::sequenced_policy) \
	    ->Name(PSTL_BENCH_BENCHMARK_NAME_WITH_BACKEND("SEQ", "std::fill"))  \
	    ->PSTL_BENCH_BENCHMARK_PARAMETERS

#ifdef PSTL_BENCH_USE_PSTL
#define FILL_STD_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(fill_std_wrapper, std::execution::parallel_unsequenced_policy) \
	    ->Name(PSTL_BENCH_BENCHMARK_NAME("std::fill"))                                 \
	    ->PSTL_BENCH_BENCHMARK_PARAMETERS
#else
#define FILL_STD_WRAPPER
#endif
//endregion fill_std

//region fill_hpx
#ifdef PSTL_BENCH_USE_HPX
template<class Policy>
static void fill_hpx_wrapper(benchmark::State & state)
{
	benchmark_fill::benchmark_wrapper<Policy>(state, benchmark_fill::fill_hpx);
}

#define FILL_HPX_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(fill_hpx_wrapper, hpx::execution::parallel_unsequenced_policy) \
	    ->Name(PSTL_BENCH_BENCHMARK_NAME("hpx::fill"))                                 \
	    ->PSTL_BENCH_BENCHMARK_PARAMETERS
#else
#define FILL_HPX_WRAPPER
#endif
//endregion fill_hpx

//region fill_onedpl
#ifdef PSTL_BENCH_USE_ONEDPL
template<class Policy>
static void fill_onedpl_wrapper(benchmark::State & state)
{
	benchmark_fill::benchmark_wrapper<Policy>(state, benchmark_fill::fill_onedpl);
}

/*
the std policy is just a placeholder, it will use oneapi::dpl::execution::dpcpp_default when executing the algorithm. 
Check the algorithm implementation.
*/
#define FILL_ONEDPL_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(fill_onedpl_wrapper, std::execution::parallel_unsequenced_policy) \
	    ->Name(PSTL_BENCH_BENCHMARK_NAME("onedpl::fill"))                                 \
	    ->PSTL_BENCH_BENCHMARK_PARAMETERS
#else
#define FILL_ONEDPL_WRAPPER
#endif
//endregion fill_onedpl

#define FILL_GROUP   \
	FILL_SEQ_WRAPPER \
	FILL_STD_WRAPPER \
	FILL_HPX_WRAPPER \
	FILL_ONEDPL_WRAPPER

FILL_GROUP