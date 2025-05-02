#pragma once

#include <oneapi/dpl/algorithm>
#include <oneapi/dpl/execution>

namespace benchmark_transform
{

	const auto transform_one_dpl = [](auto && policy, auto & input, auto && f) {
		oneapi::dpl::transform(oneapi::dpl::execution::dpcpp_default, input.begin(), input.end(), input.begin(), f);
	};

} // namespace benchmark_transform
