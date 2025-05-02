#pragma once

#include "pstl/utils/benchmark_naming.h"

#include "all_of_utils.h"

#include "all_of_std.h"

#ifdef PSTL_BENCH_USE_HPX
#include "all_of_hpx.h"
#endif

#ifdef PSTL_BENCH_USE_ONEDPL
#include "all_of_onedpl.h"
#endif

//region all_of_std
template<class Policy>
static void all_of_std_wrapper(benchmark::State & state)
{
	benchmark_all_of::benchmark_wrapper<Policy>(state, benchmark_all_of::all_of_std);
}

#define ALL_OF_SEQ_WRAPPER                                                    \
	BENCHMARK_TEMPLATE1(all_of_std_wrapper, std::execution::sequenced_policy) \
	    ->Name(PSTL_BENCH_BENCHMARK_NAME_WITH_BACKEND("SEQ", "std::all_of"))  \
	    ->PSTL_BENCH_BENCHMARK_PARAMETERS

#ifdef PSTL_BENCH_USE_PSTL
#define ALL_OF_STD_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(all_of_std_wrapper, std::execution::parallel_unsequenced_policy) \
	    ->Name(PSTL_BENCH_BENCHMARK_NAME("std::all_of"))                                 \
	    ->PSTL_BENCH_BENCHMARK_PARAMETERS
#else
#define ALL_OF_STD_WRAPPER
#endif
//endregion all_of_std

//region all_of_hpx
#ifdef PSTL_BENCH_USE_HPX
template<class Policy>
static void all_of_hpx_wrapper(benchmark::State & state)
{
	benchmark_all_of::benchmark_wrapper<Policy>(state, benchmark_all_of::all_of_hpx);
}

#define ALL_OF_HPX_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(all_of_hpx_wrapper, hpx::execution::parallel_unsequenced_policy) \
	    ->Name(PSTL_BENCH_BENCHMARK_NAME("hpx::all_of"))                                 \
	    ->PSTL_BENCH_BENCHMARK_PARAMETERS
#else
#define ALL_OF_HPX_WRAPPER
#endif
//endregion all_of_hpx

//region all_of_onedpl
#ifdef PSTL_BENCH_USE_ONEDPL
template<class Policy>
static void all_of_onedpl_wrapper(benchmark::State & state)
{
	benchmark_all_of::benchmark_wrapper<Policy>(state, benchmark_all_of::all_of_onedpl);
}

/*
the std policy is just a placeholder, it will use oneapi::dpl::execution::dpcpp_default when executing the algorithm. 
Check the algorithm implementation.
*/
#define ALL_OF_ONEDPL_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(all_of_onedpl_wrapper, std::execution::parallel_unsequenced_policy) \
	    ->Name(PSTL_BENCH_BENCHMARK_NAME("onedpl::all_of"))                                 \
	    ->PSTL_BENCH_BENCHMARK_PARAMETERS
#else
#define ALL_OF_ONEDPL_WRAPPER
#endif
//endregion all_of_onedpl

#define ALL_OF_GROUP   \
	ALL_OF_SEQ_WRAPPER \
	ALL_OF_STD_WRAPPER \
	ALL_OF_HPX_WRAPPER \
	ALL_OF_ONEDPL_WRAPPER

ALL_OF_GROUP