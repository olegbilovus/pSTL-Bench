#pragma once

#include <oneapi/dpl/algorithm>
#include <oneapi/dpl/execution>

namespace benchmark_mismatch
{
	const auto mismatch_onedpl = [](auto && policy, const auto & data1, const auto & data2) {
		return oneapi::dpl::mismatch(oneapi::dpl::execution::dpcpp_default, data1.begin(), data1.end(), data2.begin());
	};
} // namespace benchmark_mismatch
