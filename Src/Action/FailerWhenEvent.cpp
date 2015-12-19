// Copyright (c) 2015 Volodymyr Syvochka
#include "FailerWhenEvent.h"
#include "Tick.h"
#include "BehaviorTree.h"
#include "ActionManager.h"

namespace Bt
{
	FailerWhenEvent::FailerWhenEvent(EventType eventToFailWith)
		: eventToFailWith(eventToFailWith)
	{

	}

	Status FailerWhenEvent::process(Tick& tick)
	{
		// not implemented because this feature is not used now
		return Status::Failure;
	}

} // namespace Bt