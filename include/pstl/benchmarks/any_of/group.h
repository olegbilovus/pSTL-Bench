#pragma once

#include "pstl/utils/benchmark_naming.h"

#include "any_of_utils.h"

#include "any_of_std.h"

#ifdef PSTL_BENCH_USE_HPX
#include "any_of_hpx.h"
#endif

#ifdef PSTL_BENCH_USE_ONEDPL
#include "any_of_onedpl.h"
#endif

//region any_of_std
template<class Policy>
static void any_of_std_wrapper(benchmark::State & state)
{
	benchmark_any_of::benchmark_wrapper<Policy>(state, benchmark_any_of::any_of_std);
}

#define ANY_OF_SEQ_WRAPPER                                                    \
	BENCHMARK_TEMPLATE1(any_of_std_wrapper, std::execution::sequenced_policy) \
	    ->Name(PSTL_BENCH_BENCHMARK_NAME_WITH_BACKEND("SEQ", "std::any_of"))  \
	    ->PSTL_BENCH_BENCHMARK_PARAMETERS

#ifdef PSTL_BENCH_USE_PSTL
#define ANY_OF_STD_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(any_of_std_wrapper, std::execution::parallel_unsequenced_policy) \
	    ->Name(PSTL_BENCH_BENCHMARK_NAME("std::any_of"))                                 \
	    ->PSTL_BENCH_BENCHMARK_PARAMETERS
#else
#define ANY_OF_STD_WRAPPER
#endif
//endregion any_of_std

//region any_of_hpx
#ifdef PSTL_BENCH_USE_HPX
template<class Policy>
static void any_of_hpx_wrapper(benchmark::State & state)
{
	benchmark_any_of::benchmark_wrapper<Policy>(state, benchmark_any_of::any_of_hpx);
}

#define ANY_OF_HPX_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(any_of_hpx_wrapper, hpx::execution::parallel_unsequenced_policy) \
	    ->Name(PSTL_BENCH_BENCHMARK_NAME("hpx::any_of"))                                 \
	    ->PSTL_BENCH_BENCHMARK_PARAMETERS
#else
#define ANY_OF_HPX_WRAPPER
#endif
//endregion any_of_hpx

//region any_of_onedpl
#ifdef PSTL_BENCH_USE_ONEDPL
template<class Policy>
static void any_of_onedpl_wrapper(benchmark::State & state)
{
	benchmark_any_of::benchmark_wrapper<Policy>(state, benchmark_any_of::any_of_onedpl);
}

/*
the std policy is just a placeholder, it will use oneapi::dpl::execution::dpcpp_default when executing the algorithm. 
Check the algorithm implementation.
*/
#define ANY_OF_ONEDPL_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(any_of_onedpl_wrapper, std::execution::parallel_unsequenced_policy) \
	    ->Name(PSTL_BENCH_BENCHMARK_NAME("onedpl::any_of"))                                 \
	    ->PSTL_BENCH_BENCHMARK_PARAMETERS
#else
#define ANY_OF_ONEDPL_WRAPPER
#endif
//endregion any_of_onedpl

#define ANY_OF_GROUP   \
	ANY_OF_SEQ_WRAPPER \
	ANY_OF_STD_WRAPPER \
	ANY_OF_HPX_WRAPPER \
	ANY_OF_ONEDPL_WRAPPER

ANY_OF_GROUP