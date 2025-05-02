#pragma once

#include <functional>
#include <utility>

#include <oneapi/dpl/algorithm>
#include <oneapi/dpl/execution>

#include "pstl/utils/elem_t.h"

namespace benchmark_transform_exclusive_scan
{
	const auto transform_exclusive_scan_one_dpl = [](auto && policy, auto & input, auto & output, auto && f) {
		return oneapi::dpl::transform_exclusive_scan(oneapi::dpl::execution::dpcpp_default, input.begin(), input.end(),
		                                             output.begin(), pstl::elem_t{}, std::plus<>(), f);
	};
} // namespace benchmark_transform_exclusive_scan
