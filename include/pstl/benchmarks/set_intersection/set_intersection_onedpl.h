#pragma once

#include <oneapi/dpl/algorithm>
#include <oneapi/dpl/execution>

namespace benchmark_set_intersection
{
	const auto set_intersection_onedpl = [](auto && policy, const auto & data1, const auto & data2, auto & output) {
		return oneapi::dpl::set_intersection(oneapi::dpl::execution::dpcpp_default, data1.begin(), data1.end(),
		                                     data2.begin(), data2.end(), output.begin());
	};
} // namespace benchmark_set_intersection
