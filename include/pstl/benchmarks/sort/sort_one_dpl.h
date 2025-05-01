#pragma once

#include <oneapi/dpl/algorithm>
#include <oneapi/dpl/execution>

namespace benchmark_sort
{
	const auto sort_one_dpl = [](auto && policy, auto & input) {
		oneapi::dpl::sort(oneapi::dpl::execution::dpcpp_default, input.begin(), input.end());
	};

} // namespace benchmark_sort