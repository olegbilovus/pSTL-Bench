#pragma once

#include <oneapi/dpl/algorithm>
#include <oneapi/dpl/execution>

namespace benchmark_generate
{
	const auto generate_one_dpl = [](auto && policy, auto & input, auto && generator) {
		return oneapi::dpl::generate(oneapi::dpl::execution::dpcpp_default, input.begin(), input.end(), generator);
	};
} // namespace benchmark_generate
