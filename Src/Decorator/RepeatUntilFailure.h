// Copyright (c) 2015 Volodymyr Syvochka
#pragma once
#include "Decorator.h"

namespace Bt
{
	class RepeatUntilFailure : public Decorator
	{
	public:
		explicit RepeatUntilFailure(int32_t maxLoop = -1);
		RepeatUntilFailure(ActionId child, int32_t maxLoop = -1);
		virtual ~RepeatUntilFailure()
		{}
	protected:
		void open(Tick& tick) override;
		Status process(Tick& tick) override;
	private:
		int32_t maxLoop;
	};

} // namespace Bt

