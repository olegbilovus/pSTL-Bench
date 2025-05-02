#pragma once

#include <oneapi/dpl/algorithm>
#include <oneapi/dpl/execution>

namespace benchmark_includes
{
	const auto includes_one_dpl = [](auto && policy, const auto & input, const auto & subset) {
		return oneapi::dpl::includes(oneapi::dpl::execution::dpcpp_default, input.begin(), input.end(), subset.begin(),
		                             subset.end());
	};
} // namespace benchmark_includes
