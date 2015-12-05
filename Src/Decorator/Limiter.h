#pragma once
#include "Decorator.h"

namespace Bt
{
	class Limiter : public Decorator
	{
	public:
		Limiter(ActionId child, int32_t maxLoop);
		void open(Tick& tick);
		Status process(Tick& tick);
	private:
		int32_t maxLoop = 0;
	};

} // namespace Bt

