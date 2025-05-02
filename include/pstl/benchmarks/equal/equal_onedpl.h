#pragma once

#include <oneapi/dpl/algorithm>
#include <oneapi/dpl/execution>

namespace benchmark_equal
{
	const auto equal_onedpl = [](auto && policy, const auto & input, auto & output) {
		oneapi::dpl::equal(oneapi::dpl::execution::dpcpp_default, input.begin(), input.end(), output.begin());
	};
} // namespace benchmark_equal
