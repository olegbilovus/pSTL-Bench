#pragma once

#include <oneapi/dpl/algorithm>
#include <oneapi/dpl/execution>

namespace benchmark_inplace_merge
{
	const auto inplace_merge_one_dpl = [](auto && policy, auto begin, auto middle, auto end) {
		return oneapi::dpl::inplace_merge(oneapi::dpl::execution::dpcpp_default, begin, middle, end);
	};
} // namespace benchmark_inplace_merge
