#pragma once

#include <oneapi/dpl/algorithm>
#include <oneapi/dpl/execution>

namespace benchmark_lexicographical_compare
{
	const auto lexicographical_compare_onedpl = [](auto && policy, const auto & data_a, const auto & data_b) {
		return oneapi::dpl::lexicographical_compare(oneapi::dpl::execution::dpcpp_default, data_a.begin(), data_a.end(),
		                                            data_b.begin(), data_b.end());
	};
} // namespace benchmark_lexicographical_compare
