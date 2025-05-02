#pragma once

#include <oneapi/dpl/algorithm>
#include <oneapi/dpl/execution>

namespace benchmark_copy_if
{
	const auto copy_if_one_dpl = [](auto && policy, const auto & input, auto & output, auto && condition) {
		oneapi::dpl::copy_if(oneapi::dpl::execution::dpcpp_default, input.begin(), input.end(), output.begin(), condition);
	};
} // namespace benchmark_copy_if
