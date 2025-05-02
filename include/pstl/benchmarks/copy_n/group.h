#pragma once

#include "pstl/utils/benchmark_naming.h"

#include "copy_n_utils.h"

#include "copy_n_std.h"

#ifdef PSTL_BENCH_USE_HPX
#include "copy_n_hpx.h"
#endif

#ifdef PSTL_BENCH_USE_ONEDPL
#include "copy_n_onedpl.h"
#endif

//region copy_n_std
template<class Policy>
static void copy_n_std_wrapper(benchmark::State & state)
{
	benchmark_copy_n::benchmark_wrapper<Policy>(state, benchmark_copy_n::copy_n_std);
}

#define COPY_N_SEQ_WRAPPER                                                    \
	BENCHMARK_TEMPLATE1(copy_n_std_wrapper, std::execution::sequenced_policy) \
	    ->Name(PSTL_BENCH_BENCHMARK_NAME_WITH_BACKEND("SEQ", "std::copy_n"))  \
	    ->PSTL_BENCH_BENCHMARK_PARAMETERS

#ifdef PSTL_BENCH_USE_PSTL
#define COPY_N_STD_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(copy_n_std_wrapper, std::execution::parallel_unsequenced_policy) \
	    ->Name(PSTL_BENCH_BENCHMARK_NAME("std::copy_n"))                                 \
	    ->PSTL_BENCH_BENCHMARK_PARAMETERS
#else
#define COPY_N_STD_WRAPPER
#endif
//endregion copy_n_std

//region copy_n_hpx
#ifdef PSTL_BENCH_USE_HPX
template<class Policy>
static void copy_n_hpx_wrapper(benchmark::State & state)
{
	benchmark_copy_n::benchmark_wrapper<Policy>(state, benchmark_copy_n::copy_n_hpx);
}

#define COPY_N_HPX_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(copy_n_hpx_wrapper, hpx::execution::parallel_unsequenced_policy) \
	    ->Name(PSTL_BENCH_BENCHMARK_NAME("hpx::copy_n"))                                 \
	    ->PSTL_BENCH_BENCHMARK_PARAMETERS
#else
#define COPY_N_HPX_WRAPPER
#endif
//endregion copy_n_hpx

//region copy_n_onedpl
#ifdef PSTL_BENCH_USE_ONEDPL
template<class Policy>
static void copy_n_onedpl_wrapper(benchmark::State & state)
{
	benchmark_copy_n::benchmark_wrapper<Policy>(state, benchmark_copy_n::copy_n_onedpl);
}

/*
the std policy is just a placeholder, it will use oneapi::dpl::execution::dpcpp_default when executing the algorithm. 
Check the algorithm implementation.
*/
#define COPY_N_ONEDPL_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(copy_n_onedpl_wrapper, std::execution::parallel_unsequenced_policy) \
	    ->Name(PSTL_BENCH_BENCHMARK_NAME("onedpl::copy_n"))                                 \
	    ->PSTL_BENCH_BENCHMARK_PARAMETERS
#else
#define COPY_N_ONEDPL_WRAPPER
#endif
//endregion copy_n_onedpl

#define COPY_N_GROUP   \
	COPY_N_SEQ_WRAPPER \
	COPY_N_STD_WRAPPER \
	COPY_N_HPX_WRAPPER \
	COPY_N_ONEDPL_WRAPPER

COPY_N_GROUP