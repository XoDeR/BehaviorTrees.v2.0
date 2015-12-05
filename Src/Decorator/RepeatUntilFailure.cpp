#include "RepeatUntilFailure.h"
#include "Tick.h"
#include "BehaviorTree.h"
#include "ActionManager.h"

namespace Bt
{
	RepeatUntilFailure::RepeatUntilFailure(ActionId child, int32_t maxLoop /*= -1*/)
		: Decorator(child)
		, maxLoop(maxLoop)
	{

	}

	void RepeatUntilFailure::open(Tick& tick)
	{
		tick.tree.setIterCount(actionId, 0);
	}

	Status RepeatUntilFailure::process(Tick& tick)
	{
		Status status = Status::Running;

		int32_t i = tick.tree.getIterCount(actionId);
		while (maxLoop < 0 || i < maxLoop)
		{
			BaseNode* node = tick.tree.actionManager.getActionById(child);
			// CCAssert(node != nullptr)
			status = node->execute(tick);
			if (status == Status::Success)
			{
				i += 1;
				tick.tree.setIterCount(actionId, i);
			}
			else
			{
				break;
			}
		}
		return status;
	}

	void RepeatUntilFailure::interrupt(Tick& tick)
	{

	}

} // namespace Bt