#pragma once
#include "Decorator.h"

namespace Bt
{
	class RepeatUntilSuccess : public Decorator
	{
	public:
		RepeatUntilSuccess(ActionId child, int32_t maxLoop = -1);
		void open(Tick& tick);
		Status process(Tick& tick);
	private:
		int32_t maxLoop;
	};

} // namespace Bt