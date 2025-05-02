#pragma once

#include "pstl/utils/benchmark_naming.h"

#include <benchmark/benchmark.h>

#include "transform_reduce_utils.h"

#include "transform_reduce_std.h"

#ifdef PSTL_BENCH_USE_HPX
#include "transform_reduce_hpx.h"
#endif

#ifdef PSTL_BENCH_USE_ONEDPL
#include "transform_reduce_onedpl.h"
#endif

//region transform_reduce
template<class Policy>
static void transform_reduce_std_wrapper(benchmark::State & state)
{
	benchmark_transform_reduce::benchmark_wrapper<Policy>(state, benchmark_transform_reduce::transform_reduce_std);
}

#define TRANSFORM_REDUCE_SEQ_WRAPPER                                                    \
	BENCHMARK_TEMPLATE1(transform_reduce_std_wrapper, std::execution::sequenced_policy) \
	    ->Name(PSTL_BENCH_BENCHMARK_NAME_WITH_BACKEND("SEQ", "std::transform_reduce"))  \
	    ->PSTL_BENCH_BENCHMARK_PARAMETERS

#ifdef PSTL_BENCH_USE_PSTL
#define TRANSFORM_REDUCE_STD_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(transform_reduce_std_wrapper, std::execution::parallel_unsequenced_policy) \
	    ->Name(PSTL_BENCH_BENCHMARK_NAME("std::transform_reduce"))                                 \
	    ->PSTL_BENCH_BENCHMARK_PARAMETERS
#else
#define TRANSFORM_REDUCE_STD_WRAPPER
#endif
//endregion transform_reduce

//region transform_reduce_hpx
#ifdef PSTL_BENCH_USE_HPX
template<class Policy>
static void transform_reduce_hpx_wrapper(benchmark::State & state)
{
	benchmark_transform_reduce::benchmark_wrapper<Policy>(state, benchmark_transform_reduce::transform_reduce_hpx);
}

#define TRANSFORM_REDUCE_HPX_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(transform_reduce_hpx_wrapper, hpx::execution::parallel_unsequenced_policy) \
	    ->Name(PSTL_BENCH_BENCHMARK_NAME("hpx::transform_reduce"))                                 \
	    ->PSTL_BENCH_BENCHMARK_PARAMETERS
#else
#define TRANSFORM_REDUCE_HPX_WRAPPER
#endif
//endregion transform_reduce_hpx

//region transform_reduce_onedpl
#ifdef PSTL_BENCH_USE_ONEDPL
template<class Policy>
static void transform_reduce_onedpl_wrapper(benchmark::State & state)
{
	benchmark_transform_reduce::benchmark_wrapper<Policy>(state, benchmark_transform_reduce::transform_reduce_onedpl);
}

/*
the std policy is just a placeholder, it will use oneapi::dpl::execution::dpcpp_default when executing the algorithm. 
Check the algorithm implementation.
*/
#define TRANSFORM_REDUCE_ONEDPL_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(transform_reduce_onedpl_wrapper, std::execution::parallel_unsequenced_policy) \
	    ->Name(PSTL_BENCH_BENCHMARK_NAME("onedpl::transform_reduce"))                                 \
	    ->PSTL_BENCH_BENCHMARK_PARAMETERS
#else
#define TRANSFORM_REDUCE_ONEDPL_WRAPPER
#endif
//endregion transform_reduce_onedpl

#define TRANSFORM_REDUCE_GROUP   \
	TRANSFORM_REDUCE_SEQ_WRAPPER \
	TRANSFORM_REDUCE_STD_WRAPPER \
	TRANSFORM_REDUCE_HPX_WRAPPER \
	TRANSFORM_REDUCE_ONEDPL_WRAPPER

TRANSFORM_REDUCE_GROUP