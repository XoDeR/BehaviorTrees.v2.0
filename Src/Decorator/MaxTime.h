#pragma once
#include "Decorator.h"

namespace Bt
{
	class MaxTime : public Decorator
	{
	public:
		MaxTime(ActionId child, float maxDelay);
		void open(Tick& tick);
		Status process(Tick& tick);
	private:
		float maxDelay;
	};

} // namespace Bt