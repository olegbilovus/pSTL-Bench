#pragma once

#include "pstl/utils/benchmark_naming.h"

#include "partial_sort_utils.h"

#include "partial_sort_std.h"

#ifdef PSTL_BENCH_USE_GNU
#include "partial_sort_gnu.h"
#endif

#ifdef PSTL_BENCH_USE_HPX
#include "partial_sort_hpx.h"
#endif

#ifdef PSTL_BENCH_USE_ONE_DPL
#include "partial_sort_one_dpl.h"
#endif

//region partial_sort_std
template<class Policy>
static void partial_sort_std_wrapper(benchmark::State & state)
{
	benchmark_partial_sort::benchmark_wrapper<Policy>(state, benchmark_partial_sort::partial_sort_std);
}

#define PARTIAL_SORT_SEQ_WRAPPER                                                    \
	BENCHMARK_TEMPLATE1(partial_sort_std_wrapper, std::execution::sequenced_policy) \
	    ->Name(PSTL_BENCH_BENCHMARK_NAME_WITH_BACKEND("SEQ", "std::partial_sort"))  \
	    ->PSTL_BENCH_BENCHMARK_PARAMETERS

#ifdef PSTL_BENCH_USE_PSTL
#define PARTIAL_SORT_STD_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(partial_sort_std_wrapper, std::execution::parallel_unsequenced_policy) \
	    ->Name(PSTL_BENCH_BENCHMARK_NAME("std::partial_sort"))                                 \
	    ->PSTL_BENCH_BENCHMARK_PARAMETERS
#else
#define PARTIAL_SORT_STD_WRAPPER
#endif
//endregion partial_sort_std

//region partial_sort_gnu
#ifdef PSTL_BENCH_USE_GNU
template<class Policy>
static void partial_sort_gnu_wrapper(benchmark::State & state)
{
	benchmark_partial_sort::benchmark_wrapper<Policy>(state, benchmark_partial_sort::partial_sort_gnu);
}

#define PARTIAL_SORT_GNU_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(partial_sort_gnu_wrapper, std::execution::parallel_unsequenced_policy) \
	    ->Name(PSTL_BENCH_BENCHMARK_NAME("gnu::partial_sort"))                                 \
	    ->PSTL_BENCH_BENCHMARK_PARAMETERS
#else
#define PARTIAL_SORT_GNU_WRAPPER
#endif
//endregion partial_sort_gnu

//region partial_sort_hpx
#ifdef PSTL_BENCH_USE_HPX
template<class Policy>
static void partial_sort_hpx_wrapper(benchmark::State & state)
{
	benchmark_partial_sort::benchmark_wrapper<Policy>(state, benchmark_partial_sort::partial_sort_hpx);
}

#define PARTIAL_SORT_HPX_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(partial_sort_hpx_wrapper, hpx::execution::parallel_unsequenced_policy) \
	    ->Name(PSTL_BENCH_BENCHMARK_NAME("hpx::partial_sort"))                                 \
	    ->PSTL_BENCH_BENCHMARK_PARAMETERS
#else
#define PARTIAL_SORT_HPX_WRAPPER
#endif
//endregion partial_sort_hpx

//region partial_sort_one_dpl
#ifdef PSTL_BENCH_USE_ONE_DPL
template<class Policy>
static void partial_sort_one_dpl_wrapper(benchmark::State & state)
{
	benchmark_partial_sort::benchmark_wrapper<Policy>(state, benchmark_partial_sort::partial_sort_one_dpl);
}

/*
the std policy is just a placeholder, it will use oneapi::dpl::execution::dpcpp_default when executing the algorithm. 
Check the algorithm implementation.
*/
#define PARTIAL_SORT_ONE_DPL_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(partial_sort_one_dpl_wrapper, std::execution::parallel_unsequenced_policy) \
	    ->Name(PSTL_BENCH_BENCHMARK_NAME("oneDPL::partial_sort"))                                  \
	    ->PSTL_BENCH_BENCHMARK_PARAMETERS
#else
#define PARTIAL_SORT_ONE_DPL_WRAPPER
#endif
//endregion partial_sort_one_dpl

#define PARTIAL_SORT_GROUP   \
	PARTIAL_SORT_SEQ_WRAPPER \
	PARTIAL_SORT_STD_WRAPPER \
	PARTIAL_SORT_GNU_WRAPPER \
	PARTIAL_SORT_HPX_WRAPPER \
	PARTIAL_SORT_ONE_DPL_WRAPPER

PARTIAL_SORT_GROUP