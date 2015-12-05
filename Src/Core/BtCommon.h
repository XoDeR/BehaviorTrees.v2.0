#pragma once

#include <vector>
#include <deque>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <algorithm> // std::remove
#include <cstdint> // uint32_t
#include <functional>
#include <memory>

using std::vector;
using std::deque;
using std::string;
using std::unordered_set;
using std::unordered_map;
using std::unique_ptr;

namespace Bt
{
	enum class Status
	{
		Success,
		Failure,
		Running,
	};

	enum class Category
	{
		None,
		Composite,
		Decorator,
		Action,
		Condition,
	};
} // namespace Bt