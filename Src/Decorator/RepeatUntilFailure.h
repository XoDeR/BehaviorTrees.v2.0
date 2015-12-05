#pragma once
#include "Decorator.h"

namespace Bt
{
	class RepeatUntilFailure : public Decorator
	{
	public:
		RepeatUntilFailure(ActionId child, int32_t maxLoop = -1);
		void open(Tick& tick) override;
		Status process(Tick& tick) override;
		void interrupt(Tick& tick) override;
	private:
		int32_t maxLoop;
	};

} // namespace Bt

