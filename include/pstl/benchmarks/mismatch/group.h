#pragma once

#include "pstl/utils/benchmark_naming.h"

#include "mismatch_utils.h"

#include "mismatch_std.h"

#ifdef PSTL_BENCH_USE_GNU
#include "mismatch_gnu.h"
#endif

#ifdef PSTL_BENCH_USE_HPX
#include "mismatch_hpx.h"
#endif

#ifdef PSTL_BENCH_USE_ONE_DPL
#include "mismatch_one_dpl.h"
#endif

//region mismatch_std
template<class Policy>
static void mismatch_std_wrapper(benchmark::State & state)
{
	benchmark_mismatch::benchmark_wrapper<Policy>(state, benchmark_mismatch::mismatch_std);
}

#define MISMATCH_SEQ_WRAPPER                                                    \
	BENCHMARK_TEMPLATE1(mismatch_std_wrapper, std::execution::sequenced_policy) \
	    ->Name(PSTL_BENCH_BENCHMARK_NAME_WITH_BACKEND("SEQ", "std::mismatch"))  \
	    ->PSTL_BENCH_BENCHMARK_PARAMETERS

#ifdef PSTL_BENCH_USE_PSTL
#define MISMATCH_STD_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(mismatch_std_wrapper, std::execution::parallel_unsequenced_policy) \
	    ->Name(PSTL_BENCH_BENCHMARK_NAME("std::mismatch"))                                 \
	    ->PSTL_BENCH_BENCHMARK_PARAMETERS
#else
#define MISMATCH_STD_WRAPPER
#endif
//endregion mismatch_std

//region mismatch_gnu
#ifdef PSTL_BENCH_USE_GNU
template<class Policy>
static void mismatch_gnu_wrapper(benchmark::State & state)
{
	benchmark_mismatch::benchmark_wrapper<Policy>(state, benchmark_mismatch::mismatch_gnu);
}

#define MISMATCH_GNU_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(mismatch_gnu_wrapper, std::execution::parallel_unsequenced_policy) \
	    ->Name(PSTL_BENCH_BENCHMARK_NAME("gnu::mismatch"))                                 \
	    ->PSTL_BENCH_BENCHMARK_PARAMETERS
#else
#define MISMATCH_GNU_WRAPPER
#endif
//endregion mismatch_gnu

//region mismatch_hpx
#ifdef PSTL_BENCH_USE_HPX
template<class Policy>
static void mismatch_hpx_wrapper(benchmark::State & state)
{
	benchmark_mismatch::benchmark_wrapper<Policy>(state, benchmark_mismatch::mismatch_hpx);
}

#define MISMATCH_HPX_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(mismatch_hpx_wrapper, hpx::execution::parallel_unsequenced_policy) \
	    ->Name(PSTL_BENCH_BENCHMARK_NAME("hpx::mismatch"))                                 \
	    ->PSTL_BENCH_BENCHMARK_PARAMETERS
#else
#define MISMATCH_HPX_WRAPPER
#endif
//endregion mismatch_hpx

//region mismatch_one_dpl
#ifdef PSTL_BENCH_USE_ONE_DPL
template<class Policy>
static void mismatch_one_dpl_wrapper(benchmark::State & state)
{
	benchmark_mismatch::benchmark_wrapper<Policy>(state, benchmark_mismatch::mismatch_one_dpl);
}

/*
the std policy is just a placeholder, it will use oneapi::dpl::execution::dpcpp_default when executing the algorithm. 
Check the algorithm implementation.
*/
#define MISMATCH_ONE_DPL_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(mismatch_one_dpl_wrapper, std::execution::parallel_unsequenced_policy) \
	    ->Name(PSTL_BENCH_BENCHMARK_NAME("oneDPL::mismatch"))                                  \
	    ->PSTL_BENCH_BENCHMARK_PARAMETERS
#else
#define MISMATCH_ONE_DPL_WRAPPER
#endif
//endregion mismatch_one_dpl

#define MISMATCH_GROUP   \
	MISMATCH_SEQ_WRAPPER \
	MISMATCH_STD_WRAPPER \
	MISMATCH_GNU_WRAPPER \
	MISMATCH_HPX_WRAPPER \
	MISMATCH_ONE_DPL_WRAPPER

MISMATCH_GROUP