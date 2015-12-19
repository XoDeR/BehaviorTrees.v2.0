// Copyright (c) 2015 Volodymyr Syvochka
#pragma once
#include "Decorator.h"

namespace Bt
{
	class Inverter : public Decorator
	{
	public:
		Inverter();
		explicit Inverter(ActionId child);
		virtual ~Inverter()
		{}
	protected:
		Status process(Tick& tick);
	};

} // namespace Bt

