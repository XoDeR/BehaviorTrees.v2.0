// Copyright (c) 2015 Volodymyr Syvochka
#pragma once
#include "Decorator.h"

namespace Bt
{
	class Repeater : public Decorator
	{
	public:
		explicit Repeater(int32_t maxLoop = -1);
		Repeater(ActionId child, int32_t maxLoop = -1);
		virtual ~Repeater()
		{}
	protected:
		void open(Tick& tick);
		Status process(Tick& tick);
	private:
		int32_t maxLoop;
	};

} // namespace Bt