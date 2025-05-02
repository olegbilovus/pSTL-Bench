#pragma once

#include <oneapi/dpl/algorithm>
#include <oneapi/dpl/execution>

namespace benchmark_copy_n
{
	const auto copy_n_onedpl = [](auto && policy, const auto & input, const auto & n, auto & output) {
		oneapi::dpl::copy_n(oneapi::dpl::execution::dpcpp_default, input.begin(), n, output.begin());
	};
} // namespace benchmark_copy_n
