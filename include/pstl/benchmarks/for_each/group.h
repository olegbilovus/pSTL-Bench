#pragma once

#include "pstl/utils/benchmark_naming.h"

#include <benchmark/benchmark.h>

#include "for_each_utils.h"

#include "for_each_std.h"

#ifdef PSTL_BENCH_USE_GNU
#include "for_each_gnu.h"
#endif

#ifdef PSTL_BENCH_USE_HPX
#include "for_each_hpx.h"
#endif

#ifdef PSTL_BENCH_USE_ONEDPL
#include "for_each_onedpl.h"
#include <oneapi/dpl/execution>
#endif

//region for_each
template<class Policy>
static void for_each_std_wrapper(benchmark::State & state)
{
	benchmark_for_each::benchmark_for_each_wrapper<Policy>(state, benchmark_for_each::for_each_std);
}

#define FOR_EACH_SEQ_WRAPPER                                                    \
	BENCHMARK_TEMPLATE1(for_each_std_wrapper, std::execution::sequenced_policy) \
	    ->Name(PSTL_BENCH_BENCHMARK_NAME_WITH_BACKEND("SEQ", "std::for_each"))  \
	    ->PSTL_BENCH_BENCHMARK_PARAMETERS

#ifdef PSTL_BENCH_USE_PSTL
#define FOR_EACH_STD_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(for_each_std_wrapper, std::execution::parallel_unsequenced_policy) \
	    ->Name(PSTL_BENCH_BENCHMARK_NAME("std::for_each"))                                 \
	    ->PSTL_BENCH_BENCHMARK_PARAMETERS
#else
#define FOR_EACH_STD_WRAPPER
#endif
//endregion for_each

//region for_each_gnu
#ifdef PSTL_BENCH_USE_GNU
template<class Policy>
static void for_each_gnu_wrapper(benchmark::State & state)
{
	benchmark_for_each::benchmark_for_each_wrapper<Policy>(state, benchmark_for_each::for_each_gnu);
}

#define FOR_EACH_GNU_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(for_each_gnu_wrapper, std::execution::parallel_unsequenced_policy) \
	    ->Name(PSTL_BENCH_BENCHMARK_NAME("gnu::for_each"))                                 \
	    ->PSTL_BENCH_BENCHMARK_PARAMETERS
#else
#define FOR_EACH_GNU_WRAPPER
#endif
//endregion for_each_gnu

//region for_each_hpx
#ifdef PSTL_BENCH_USE_HPX
template<class Policy>
static void for_each_hpx_wrapper(benchmark::State & state)
{
	benchmark_for_each::benchmark_for_each_wrapper<Policy>(state, benchmark_for_each::for_each_hpx);
}

#define FOR_EACH_HPX_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(for_each_hpx_wrapper, hpx::execution::parallel_unsequenced_policy) \
	    ->Name(PSTL_BENCH_BENCHMARK_NAME("hpx::for_each"))                                 \
	    ->PSTL_BENCH_BENCHMARK_PARAMETERS
#else
#define FOR_EACH_HPX_WRAPPER
#endif
//endregion for_each_hpx

//region for_each_onedpl
#ifdef PSTL_BENCH_USE_ONEDPL
template<class Policy>
static void for_each_onedpl_wrapper(benchmark::State & state)
{
	benchmark_for_each::benchmark_for_each_wrapper<Policy>(state, benchmark_for_each::for_each_onedpl);
}

/*
the std policy is just a placeholder, it will use oneapi::dpl::execution::dpcpp_default when executing the algorithm. 
Check the algorithm implementation.
*/
#define FOR_EACH_ONEDPL_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(for_each_onedpl_wrapper, std::execution::parallel_unsequenced_policy) \
	    ->Name(PSTL_BENCH_BENCHMARK_NAME("onedpl::for_each"))                                 \
	    ->PSTL_BENCH_BENCHMARK_PARAMETERS
#else
#define FOR_EACH_ONEDPL_WRAPPER
#endif
//endregion for_each_onedpl

#define FOR_EACH_GROUP   \
	FOR_EACH_SEQ_WRAPPER \
	FOR_EACH_STD_WRAPPER \
	FOR_EACH_GNU_WRAPPER \
	FOR_EACH_HPX_WRAPPER \
	FOR_EACH_ONEDPL_WRAPPER

FOR_EACH_GROUP