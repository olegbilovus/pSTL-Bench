#pragma once

#include <oneapi/dpl/algorithm>
#include <oneapi/dpl/execution>

namespace benchmark_merge
{
	const auto merge_one_dpl = [](auto && policy, auto first1, auto last1, auto first2, auto last2, auto d_first) {
		return oneapi::dpl::merge(oneapi::dpl::execution::dpcpp_default, first1, last1, first2, last2, d_first);
	};
} // namespace benchmark_merge
