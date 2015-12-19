// Copyright (c) 2015 Volodymyr Syvochka
#pragma once
#include "Decorator.h"

namespace Bt
{
	class Limiter : public Decorator
	{
	public:
		explicit Limiter(int32_t maxLoop);
		Limiter(ActionId child, int32_t maxLoop);
		virtual ~Limiter()
		{}
	protected:
		void open(Tick& tick);
		Status process(Tick& tick);
	private:
		int32_t maxLoop = 0;
	};
} // namespace Bt

