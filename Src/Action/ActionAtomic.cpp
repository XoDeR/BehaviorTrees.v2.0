// Copyright (c) 2015 Volodymyr Syvochka
#include "ActionAtomic.h"

namespace Bt
{
	ActionAtomic::ActionAtomic(std::function<void()>&& startFunc)
		: startFunc(std::move(startFunc))
	{
	}

	Status ActionAtomic::process(Tick& tick)
	{
		startFunc();
		return Status::Success;
	}
} // namespace Bt
