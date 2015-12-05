#pragma once
#include "Decorator.h"

namespace Bt
{
	class Repeater : public Decorator
	{
	public:
		Repeater(ActionId child, int32_t maxLoop = -1);
		void open(Tick& tick);
		Status process(Tick& tick);
		void interrupt(Tick& tick) override;
	private:
		int32_t maxLoop;
	};

} // namespace Bt