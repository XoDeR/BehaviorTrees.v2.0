#pragma once
#include "Composite.h"

namespace Bt
{

	class Selector : public Composite
	{
	public:
		explicit Selector(vector<ActionId> children);
		Status process(Tick& tick);
	};

} // namespace Bt