
#pragma once

#include "pstl/utils/benchmark_naming.h"

#include "find_utils.h"

#include "find_std.h"

#ifdef PSTL_BENCH_USE_GNU
#include "find_gnu.h"
#endif

#ifdef PSTL_BENCH_USE_HPX
#include "find_hpx.h"
#endif

#ifdef PSTL_BENCH_USE_ONEDPL
#include "find_onedpl.h"
#endif

//region find
template<class Policy>
static void find_std_wrapper(benchmark::State & state)
{
	benchmark_find::benchmark_wrapper<Policy>(state, benchmark_find::find_std);
}

#define FIND_SEQ_WRAPPER                                                    \
	BENCHMARK_TEMPLATE1(find_std_wrapper, std::execution::sequenced_policy) \
	    ->Name(PSTL_BENCH_BENCHMARK_NAME_WITH_BACKEND("SEQ", "std::find"))  \
	    ->PSTL_BENCH_BENCHMARK_PARAMETERS

#ifdef PSTL_BENCH_USE_PSTL
#define FIND_STD_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(find_std_wrapper, std::execution::parallel_unsequenced_policy) \
	    ->Name(PSTL_BENCH_BENCHMARK_NAME("std::find"))                                 \
	    ->PSTL_BENCH_BENCHMARK_PARAMETERS
#else
#define FIND_STD_WRAPPER
#endif
//endregion find

//region find_gnu
#ifdef PSTL_BENCH_USE_GNU
template<class Policy>
static void find_gnu_wrapper(benchmark::State & state)
{
	benchmark_find::benchmark_wrapper<Policy>(state, benchmark_find::find_gnu);
}

#define FIND_GNU_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(find_gnu_wrapper, std::execution::parallel_unsequenced_policy) \
	    ->Name(PSTL_BENCH_BENCHMARK_NAME("gnu::find"))                                 \
	    ->PSTL_BENCH_BENCHMARK_PARAMETERS
#else
#define FIND_GNU_WRAPPER
#endif
//endregion find_gnu

//region find_hpx
#ifdef PSTL_BENCH_USE_HPX
template<class Policy>
static void find_hpx_wrapper(benchmark::State & state)
{
	benchmark_find::benchmark_wrapper<Policy>(state, benchmark_find::find_hpx);
}

#define FIND_HPX_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(find_hpx_wrapper, hpx::execution::parallel_unsequenced_policy) \
	    ->Name(PSTL_BENCH_BENCHMARK_NAME("hpx::find"))                                 \
	    ->PSTL_BENCH_BENCHMARK_PARAMETERS
#else
#define FIND_HPX_WRAPPER
#endif
//endregion find_hpx

//region find_onedpl
#ifdef PSTL_BENCH_USE_ONEDPL
template<class Policy>
static void find_onedpl_wrapper(benchmark::State & state)
{
	benchmark_find::benchmark_wrapper<Policy>(state, benchmark_find::find_onedpl);
}

/*
the std policy is just a placeholder, it will use oneapi::dpl::execution::dpcpp_default when executing the algorithm. 
Check the algorithm implementation.
*/
#define FIND_ONEDPL_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(find_onedpl_wrapper, std::execution::parallel_unsequenced_policy) \
	    ->Name(PSTL_BENCH_BENCHMARK_NAME("onedpl::find"))                                 \
	    ->PSTL_BENCH_BENCHMARK_PARAMETERS
#else
#define FIND_ONEDPL_WRAPPER
#endif
//endregion find_onedpl

// Register the function as a benchmark
#define FIND_GROUP   \
	FIND_SEQ_WRAPPER \
	FIND_STD_WRAPPER \
	FIND_GNU_WRAPPER \
	FIND_HPX_WRAPPER \
	FIND_ONEDPL_WRAPPER

FIND_GROUP