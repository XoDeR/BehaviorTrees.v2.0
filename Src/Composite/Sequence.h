#pragma once
#include "Composite.h"

namespace Bt
{
	class Sequence : public Composite
	{
	public:
		explicit Sequence(vector<ActionId> children);
		Status process(Tick& tick) override;
		void interrupt(Tick& tick) override;
	};

} // namespace Bt
