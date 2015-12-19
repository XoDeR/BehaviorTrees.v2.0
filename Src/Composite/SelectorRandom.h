// Copyright (c) 2015 Volodymyr Syvochka
#pragma once
#include "Composite.h"

namespace Bt
{
	// stateful on running
	class SelectorRandom : public Composite
	{
	public:
		SelectorRandom();
		explicit SelectorRandom(vector<ActionId> children);
		virtual ~SelectorRandom()
		{}
	protected:
		void open(Tick& tick) override;
		Status process(Tick& tick) override;
		void exit(Tick& tick) override;
	};

} // namespace Bt