#pragma once

#include <oneapi/dpl/algorithm>
#include <oneapi/dpl/execution>

namespace benchmark_any_of
{

	const auto any_of_onedpl = [](auto && policy, const auto & input, auto && condition) {
		return oneapi::dpl::any_of(oneapi::dpl::execution::dpcpp_default, input.begin(), input.end(), condition);
	};

} // namespace benchmark_any_of
