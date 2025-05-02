#pragma once

#include <oneapi/dpl/algorithm>
#include <oneapi/dpl/execution>

namespace benchmark_partition
{
	const auto partition_onedpl = [](auto && policy, auto & input, auto && condition) {
		return oneapi::dpl::partition(oneapi::dpl::execution::dpcpp_default, input.begin(), input.end(),
		                              std::forward<decltype(condition)>(condition));
	};
} // namespace benchmark_partition
