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
		return Status::Failure;
	}

} // namespace Bt