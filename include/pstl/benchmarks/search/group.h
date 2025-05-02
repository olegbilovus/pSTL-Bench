#pragma once

#include "pstl/utils/benchmark_naming.h"

#include "search_utils.h"

#include "search_std.h"

#ifdef PSTL_BENCH_USE_GNU
#include "search_gnu.h"
#endif

#ifdef PSTL_BENCH_USE_HPX
#include "search_hpx.h"
#endif

#ifdef PSTL_BENCH_USE_ONE_DPL
#include "search_one_dpl.h"
#endif

//region search_std
template<class Policy>
static void search_std_wrapper(benchmark::State & state)
{
	benchmark_search::benchmark_wrapper<Policy>(state, benchmark_search::search_std);
}

#define SEARCH_SEQ_WRAPPER                                                    \
	BENCHMARK_TEMPLATE1(search_std_wrapper, std::execution::sequenced_policy) \
	    ->Name(PSTL_BENCH_BENCHMARK_NAME_WITH_BACKEND("SEQ", "std::search"))  \
	    ->PSTL_BENCH_BENCHMARK_PARAMETERS

#ifdef PSTL_BENCH_USE_PSTL
#define SEARCH_STD_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(search_std_wrapper, std::execution::parallel_unsequenced_policy) \
	    ->Name(PSTL_BENCH_BENCHMARK_NAME("std::search"))                                 \
	    ->PSTL_BENCH_BENCHMARK_PARAMETERS
#else
#define SEARCH_STD_WRAPPER
#endif
//endregion search_std

//region search_gnu
#ifdef PSTL_BENCH_USE_GNU
template<class Policy>
static void search_gnu_wrapper(benchmark::State & state)
{
	benchmark_search::benchmark_wrapper<Policy>(state, benchmark_search::search_gnu);
}

#define SEARCH_GNU_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(search_gnu_wrapper, std::execution::parallel_unsequenced_policy) \
	    ->Name(PSTL_BENCH_BENCHMARK_NAME("gnu::search"))                                 \
	    ->PSTL_BENCH_BENCHMARK_PARAMETERS
#else
#define SEARCH_GNU_WRAPPER
#endif
//endregion search_gnu

//region search_hpx
#ifdef PSTL_BENCH_USE_HPX
template<class Policy>
static void search_hpx_wrapper(benchmark::State & state)
{
	benchmark_search::benchmark_wrapper<Policy>(state, benchmark_search::search_hpx);
}

#define SEARCH_HPX_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(search_hpx_wrapper, hpx::execution::parallel_unsequenced_policy) \
	    ->Name(PSTL_BENCH_BENCHMARK_NAME("hpx::search"))                                 \
	    ->PSTL_BENCH_BENCHMARK_PARAMETERS
#else
#define SEARCH_HPX_WRAPPER
#endif
//endregion search_hpx

//region search_one_dpl
#ifdef PSTL_BENCH_USE_ONE_DPL
template<class Policy>
static void search_one_dpl_wrapper(benchmark::State & state)
{
	benchmark_search::benchmark_wrapper<Policy>(state, benchmark_search::search_one_dpl);
}

/*
the std policy is just a placeholder, it will use oneapi::dpl::execution::dpcpp_default when executing the algorithm. 
Check the algorithm implementation.
*/
#define SEARCH_ONE_DPL_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(search_one_dpl_wrapper, std::execution::parallel_unsequenced_policy) \
	    ->Name(PSTL_BENCH_BENCHMARK_NAME("oneDPL::search"))                                  \
	    ->PSTL_BENCH_BENCHMARK_PARAMETERS
#else
#define SEARCH_ONE_DPL_WRAPPER
#endif
//endregion search_one_dpl

#define SEARCH_GROUP   \
	SEARCH_SEQ_WRAPPER \
	SEARCH_STD_WRAPPER \
	SEARCH_GNU_WRAPPER \
	SEARCH_HPX_WRAPPER \
	SEARCH_ONE_DPL_WRAPPER

SEARCH_GROUP