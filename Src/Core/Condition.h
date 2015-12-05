#pragma once
#include "BaseNode.h"

namespace Bt
{
	class Condition : public BaseNode
	{
	public:
		Condition(std::function<bool()>&& startFunc);
		Status process();
		std::function<bool()> startFunc;
	};

} // namespace Bt