// Copyright (c) 2015 Volodymyr Syvochka
#pragma once
#include "Decorator.h"

namespace Bt
{
	class RepeatUntilSuccess : public Decorator
	{
	public:
		explicit RepeatUntilSuccess(int32_t maxLoop = -1);
		RepeatUntilSuccess(ActionId child, int32_t maxLoop = -1);
		virtual ~RepeatUntilSuccess()
		{}
	protected:
		void open(Tick& tick);
		Status process(Tick& tick);
	private:
		int32_t maxLoop;
	};

} // namespace Bt