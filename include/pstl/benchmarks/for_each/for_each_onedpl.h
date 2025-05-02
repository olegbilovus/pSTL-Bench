#pragma once

#include <oneapi/dpl/algorithm>
#include <oneapi/dpl/execution>

namespace benchmark_for_each
{
	const auto for_each_onedpl = [](auto && policy, auto & input, auto && f) {
		oneapi::dpl::for_each(oneapi::dpl::execution::dpcpp_default, input.begin(), input.end(), f);
	};

} // namespace benchmark_for_each
