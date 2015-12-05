#pragma once
#include "Composite.h"

namespace Bt
{
	// remembers the last state if it was running
	// Success when ANY is successful
	// Failure if ALL behavior failed
	// Running if ANY is running
	class SelectorStateful : public Composite
	{
	public:
		SelectorStateful(vector<ActionId> children);
		void open(Tick& tick) override;
		Status process(Tick& tick) override;
		void interrupt(Tick& tick) override;
		void close(Tick& tick) override;
	};
} // namespace Bt