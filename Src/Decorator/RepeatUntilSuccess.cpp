#include "RepeatUntilSuccess.h"
#include "Tick.h"
#include "BehaviorTree.h"
#include "ActionManager.h"

namespace Bt
{
	RepeatUntilSuccess::RepeatUntilSuccess(ActionId child, int32_t maxLoop /*= -1*/)
		: Decorator(child)
		, maxLoop(maxLoop)
	{

	}

	void RepeatUntilSuccess::open(Tick& tick)
	{
		tick.tree.setIterCount(actionId, 0);
	}

	Status RepeatUntilSuccess::process(Tick& tick)
	{
		Status status = Status::Running;

		int32_t i = tick.tree.getIterCount(actionId);
		while (maxLoop < 0 || i < maxLoop)
		{
			BaseNode* node = tick.tree.actionManager.getActionById(child);
			// CCAssert(node != nullptr)
			status = node->execute(tick);
			if (status == Status::Failure)
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

} // namespace Bt