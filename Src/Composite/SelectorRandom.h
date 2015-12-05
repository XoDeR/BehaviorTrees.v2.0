#pragma once
#include "Composite.h"

namespace Bt
{
	// stateful on running
	class SelectorRandom : public Composite
	{
	public:
		explicit SelectorRandom(vector<ActionId> children);
		void open(Tick& tick) override;
		Status process(Tick& tick) override;
		void interrupt(Tick& tick) override;
		void close(Tick& tick) override;
	};

} // namespace Bt