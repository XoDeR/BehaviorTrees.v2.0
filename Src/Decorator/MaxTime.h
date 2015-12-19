// Copyright (c) 2015 Volodymyr Syvochka
#pragma once
#include "Decorator.h"

namespace Bt
{
	class MaxTime : public Decorator
	{
	public:
		explicit MaxTime(float maxDelay);
		MaxTime(ActionId child, float maxDelay);
		virtual ~MaxTime()
		{}
	protected:
		void open(Tick& tick);
		Status process(Tick& tick);
	private:
		float maxDelay;
	};

} // namespace Bt