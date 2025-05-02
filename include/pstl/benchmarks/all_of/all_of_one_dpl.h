#pragma once

#include <oneapi/dpl/algorithm>
#include <oneapi/dpl/execution>

namespace benchmark_all_of
{
	const auto all_of_one_dpl = [](auto && policy, const auto & input, auto && condition) {
		return oneapi::dpl::all_of(oneapi::dpl::execution::dpcpp_default, input.begin(), input.end(), condition);
	};
} // namespace benchmark_all_of
