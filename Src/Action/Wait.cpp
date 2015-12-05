#include "Wait.h"
#include "Tick.h"
#include "BehaviorTree.h"
#include "ActionManager.h"

namespace Bt
{
	Wait::Wait(float delay) 
		: endTime(delay)
	{

	}

	void Wait::open(Tick& tick)
	{
		tick.tree.setElapsedTime(actionId, 0.0f);
	}

	Status Wait::process(Tick& tick)
	{
		float elapsedTime = tick.tree.getElapsedTime(actionId);
		if (elapsedTime > endTime)
		{
			return Status::Success;
		}
		return Status::Running;
	}

} // namespace Bt
