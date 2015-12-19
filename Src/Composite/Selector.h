// Copyright (c) 2015 Volodymyr Syvochka
#pragma once
#include "Composite.h"

namespace Bt
{
	class Selector : public Composite
	{
	public:
		Selector();
		explicit Selector(vector<ActionId> children);
		virtual ~Selector()
		{}
	protected:
		Status process(Tick& tick);
	};

} // namespace Bt