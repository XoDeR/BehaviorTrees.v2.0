// Copyright (c) 2015 Volodymyr Syvochka
#pragma once
#include "Composite.h"

namespace Bt
{
	class Sequence : public Composite
	{
	public:
		Sequence();
		explicit Sequence(vector<ActionId> children);
		virtual ~Sequence()
		{}
	protected:
		Status process(Tick& tick) override;
	};

} // namespace Bt
