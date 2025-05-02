#pragma once

#include "pstl/utils/benchmark_naming.h"

#include "copy_utils.h"

#include "copy_std.h"

#ifdef PSTL_BENCH_USE_HPX
#include "copy_hpx.h"
#endif

#ifdef PSTL_BENCH_USE_ONEDPL
#include "copy_onedpl.h"
#endif

//region copy_std
template<class Policy>
static void copy_std_wrapper(benchmark::State & state)
{
	benchmark_copy::benchmark_wrapper<Policy>(state, benchmark_copy::copy_std);
}

#define COPY_SEQ_WRAPPER                                                    \
	BENCHMARK_TEMPLATE1(copy_std_wrapper, std::execution::sequenced_policy) \
	    ->Name(PSTL_BENCH_BENCHMARK_NAME_WITH_BACKEND("SEQ", "std::copy"))  \
	    ->PSTL_BENCH_BENCHMARK_PARAMETERS

#ifdef PSTL_BENCH_USE_PSTL
#define COPY_STD_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(copy_std_wrapper, std::execution::parallel_unsequenced_policy) \
	    ->Name(PSTL_BENCH_BENCHMARK_NAME("std::copy"))                                 \
	    ->PSTL_BENCH_BENCHMARK_PARAMETERS
#else
#define COPY_STD_WRAPPER
#endif
//endregion copy_std

//region copy_hpx
#ifdef PSTL_BENCH_USE_HPX
template<class Policy>
static void copy_hpx_wrapper(benchmark::State & state)
{
	benchmark_copy::benchmark_wrapper<Policy>(state, benchmark_copy::copy_hpx);
}

#define COPY_HPX_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(copy_hpx_wrapper, hpx::execution::parallel_unsequenced_policy) \
	    ->Name(PSTL_BENCH_BENCHMARK_NAME("hpx::copy"))                                 \
	    ->PSTL_BENCH_BENCHMARK_PARAMETERS
#else
#define COPY_HPX_WRAPPER
#endif
//endregion copy_hpx

//region copy_onedpl
#ifdef PSTL_BENCH_USE_ONEDPL
template<class Policy>
static void copy_onedpl_wrapper(benchmark::State & state)
{
	benchmark_copy::benchmark_wrapper<Policy>(state, benchmark_copy::copy_onedpl);
}

/*
the std policy is just a placeholder, it will use oneapi::dpl::execution::dpcpp_default when executing the algorithm. 
Check the algorithm implementation.
*/
#define COPY_ONEDPL_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(copy_onedpl_wrapper, std::execution::parallel_unsequenced_policy) \
	    ->Name(PSTL_BENCH_BENCHMARK_NAME("onedpl::copy"))                                 \
	    ->PSTL_BENCH_BENCHMARK_PARAMETERS
#else
#define COPY_ONEDPL_WRAPPER
#endif
//endregion copy_onedpl

#define COPY_GROUP   \
	COPY_SEQ_WRAPPER \
	COPY_STD_WRAPPER \
	COPY_HPX_WRAPPER \
	COPY_ONEDPL_WRAPPER

COPY_GROUP