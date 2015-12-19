#pragma once
#include "BaseNode.h"

namespace Bt
{
	class Condition : public BaseNode
	{
	public:
		Condition(std::function<bool()>&& startFunc);
		virtual ~Condition()
		{}
	protected:
		Status process(Tick& tick) override;
		std::function<bool()> startFunc;
	};

} // namespace Bt