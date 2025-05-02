#pragma once

#include <oneapi/dpl/algorithm>
#include <oneapi/dpl/execution>

namespace benchmark_partial_sort
{
	const auto partial_sort_one_dpl = [](auto && policy, auto begin, auto middle, auto end) {
		return oneapi::dpl::partial_sort(oneapi::dpl::execution::dpcpp_default, begin, middle, end);
	};
} // namespace benchmark_partial_sort
