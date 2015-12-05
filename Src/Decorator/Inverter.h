#pragma once
#include "Decorator.h"

namespace Bt
{

	class Inverter : public Decorator
	{
	public:
		Inverter(ActionId child);
		Status process(Tick& tick);
	};

} // namespace Bt

