
#pragma once

#include <oneapi/dpl/algorithm>
#include <oneapi/dpl/execution>

namespace benchmark_none_of
{

	const auto none_of_one_dpl = [](auto && policy, const auto & input, auto && condition) {
		return oneapi::dpl::none_of(oneapi::dpl::execution::dpcpp_default, input.begin(), input.end(), condition);
	};

} // namespace benchmark_none_of
