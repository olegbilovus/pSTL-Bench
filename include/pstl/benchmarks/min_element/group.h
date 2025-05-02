#pragma once

#include "pstl/utils/benchmark_naming.h"

#include "min_element_utils.h"

#include "min_element_std.h"

#ifdef PSTL_BENCH_USE_GNU
#include "min_element_gnu.h"
#endif

#ifdef PSTL_BENCH_USE_HPX
#include "min_element_hpx.h"
#endif

#ifdef PSTL_BENCH_USE_ONE_DPL
#include "min_element_one_dpl.h"
#endif

//region min_element_std
template<class Policy>
static void min_element_std_wrapper(benchmark::State & state)
{
	benchmark_min_element::benchmark_wrapper<Policy>(state, benchmark_min_element::min_element_std);
}

#define MIN_ELEMENT_SEQ_WRAPPER                                                    \
	BENCHMARK_TEMPLATE1(min_element_std_wrapper, std::execution::sequenced_policy) \
	    ->Name(PSTL_BENCH_BENCHMARK_NAME_WITH_BACKEND("SEQ", "std::min_element"))  \
	    ->PSTL_BENCH_BENCHMARK_PARAMETERS

#ifdef PSTL_BENCH_USE_PSTL
#define MIN_ELEMENT_STD_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(min_element_std_wrapper, std::execution::parallel_unsequenced_policy) \
	    ->Name(PSTL_BENCH_BENCHMARK_NAME("std::min_element"))                                 \
	    ->PSTL_BENCH_BENCHMARK_PARAMETERS
#else
#define MIN_ELEMENT_STD_WRAPPER
#endif
//endregion min_element_std

//region min_element_gnu
#ifdef PSTL_BENCH_USE_GNU
template<class Policy>
static void min_element_gnu_wrapper(benchmark::State & state)
{
	benchmark_min_element::benchmark_wrapper<Policy>(state, benchmark_min_element::min_element_gnu);
}

#define MIN_ELEMENT_GNU_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(min_element_gnu_wrapper, std::execution::parallel_unsequenced_policy) \
	    ->Name(PSTL_BENCH_BENCHMARK_NAME("gnu::min_element"))                                 \
	    ->PSTL_BENCH_BENCHMARK_PARAMETERS
#else
#define MIN_ELEMENT_GNU_WRAPPER
#endif
//endregion min_element_gnu

//region min_element_hpx
#ifdef PSTL_BENCH_USE_HPX
template<class Policy>
static void min_element_hpx_wrapper(benchmark::State & state)
{
	benchmark_min_element::benchmark_wrapper<Policy>(state, benchmark_min_element::min_element_hpx);
}

#define MIN_ELEMENT_HPX_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(min_element_hpx_wrapper, hpx::execution::parallel_unsequenced_policy) \
	    ->Name(PSTL_BENCH_BENCHMARK_NAME("hpx::min_element"))                                 \
	    ->PSTL_BENCH_BENCHMARK_PARAMETERS
#else
#define MIN_ELEMENT_HPX_WRAPPER
#endif
//endregion min_element_hpx

//region min_element_one_dpl
#ifdef PSTL_BENCH_USE_ONE_DPL
template<class Policy>
static void min_element_one_dpl_wrapper(benchmark::State & state)
{
	benchmark_min_element::benchmark_wrapper<Policy>(state, benchmark_min_element::min_element_one_dpl);
}

/*
the std policy is just a placeholder, it will use oneapi::dpl::execution::dpcpp_default when executing the algorithm. 
Check the algorithm implementation.
*/
#define MIN_ELEMENT_ONE_DPL_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(min_element_one_dpl_wrapper, std::execution::parallel_unsequenced_policy) \
	    ->Name(PSTL_BENCH_BENCHMARK_NAME("oneDPL::min_element"))                                  \
	    ->PSTL_BENCH_BENCHMARK_PARAMETERS
#else
#define MIN_ELEMENT_ONE_DPL_WRAPPER
#endif
//endregion min_element_one_dpl

#define MIN_ELEMENT_GROUP   \
	MIN_ELEMENT_SEQ_WRAPPER \
	MIN_ELEMENT_STD_WRAPPER \
	MIN_ELEMENT_GNU_WRAPPER \
	MIN_ELEMENT_HPX_WRAPPER \
	MIN_ELEMENT_ONE_DPL_WRAPPER

MIN_ELEMENT_GROUP