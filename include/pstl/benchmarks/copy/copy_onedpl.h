#pragma once

#include <oneapi/dpl/algorithm>
#include <oneapi/dpl/execution>

namespace benchmark_copy
{
	const auto copy_onedpl = [](auto && policy, const auto & input, auto & output) {
		oneapi::dpl::copy(oneapi::dpl::execution::dpcpp_default, input.begin(), input.end(), output.begin());
	};
} // namespace benchmark_copy
