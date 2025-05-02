#pragma once

#include <functional>

#include <oneapi/dpl/algorithm>
#include <oneapi/dpl/execution>

#include "pstl/utils/elem_t.h"

namespace benchmark_transform_reduce
{
	const auto transform_reduce_onedpl = [](auto && policy, auto & input, auto && f) {
		return oneapi::dpl::transform_reduce(oneapi::dpl::execution::dpcpp_default, input.begin(), input.end(),
		                                     pstl::elem_t{}, std::plus<>(), f);
	};
} // namespace benchmark_transform_reduce
