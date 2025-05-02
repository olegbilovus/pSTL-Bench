#pragma once

#include <oneapi/dpl/algorithm>
#include <oneapi/dpl/execution>

namespace benchmark_search
{
	const auto search_onedpl = [](auto && policy, const auto & data1, const auto & data2) {
		return oneapi::dpl::search(oneapi::dpl::execution::dpcpp_default, data1.begin(), data1.end(), data2.begin(),
		                           data2.end());
	};
} // namespace benchmark_search
