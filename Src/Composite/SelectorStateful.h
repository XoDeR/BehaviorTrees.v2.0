// Copyright (c) 2015 Volodymyr Syvochka
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
		SelectorStateful();
		explicit SelectorStateful(vector<ActionId> children);
		virtual ~SelectorStateful()
		{}
	protected:
		void open(Tick& tick) override;
		Status process(Tick& tick) override;
		void exit(Tick& tick) override;
	};
} // namespace Bt