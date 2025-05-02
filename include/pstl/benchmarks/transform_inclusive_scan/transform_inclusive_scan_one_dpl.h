#pragma once

#include <oneapi/dpl/algorithm>
#include <oneapi/dpl/execution>

namespace benchmark_transform_inclusive_scan
{

	const auto transform_inclusive_scan_one_dpl = [](auto && policy, auto & input, auto & output, auto && f) {
		return oneapi::dpl::transform_inclusive_scan(oneapi::dpl::execution::dpcpp_default, input.begin(), input.end(),
		                                             output.begin(), std::plus<>(), f);
	};

} // namespace benchmark_transform_inclusive_scan
