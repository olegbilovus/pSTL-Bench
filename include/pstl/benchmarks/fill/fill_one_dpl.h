#pragma once

#include <oneapi/dpl/algorithm>
#include <oneapi/dpl/execution>

namespace benchmark_fill
{
	const auto fill_one_dpl = [](auto && policy, auto & input, const auto & value) {
		return oneapi::dpl::fill(oneapi::dpl::execution::dpcpp_default, input.begin(), input.end(), value);
	};
} // namespace benchmark_fill
