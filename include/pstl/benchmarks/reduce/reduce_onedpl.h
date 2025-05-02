#pragma once

#include "pstl/utils/elem_t.h"

#include <oneapi/dpl/algorithm>
#include <oneapi/dpl/execution>

namespace benchmark_reduce
{
	const auto reduce_onedpl = [](auto && policy, const auto & input) {
		return oneapi::dpl::reduce(oneapi::dpl::execution::dpcpp_default, input.begin(), input.end(), pstl::elem_t{});
	};
} // namespace benchmark_reduce
