#include "Repeater.h"
#include "Tick.h"
#include "BehaviorTree.h"
#include "ActionManager.h"

namespace Bt
{
	Repeater::Repeater(ActionId child, int32_t maxLoop /*= -1*/)
		: Decorator(child)
		, maxLoop(maxLoop)
	{

	}

	void Repeater::open(Tick& tick)
	{
		tick.tree.setIterCount(actionId, 0);
	}

	Status Repeater::process(Tick& tick)
	{
		int32_t i = tick.tree.getIterCount(actionId);
		// CCAssert(i != -1);
		Status status = Status::Success;
		while (maxLoop < 0 || i < maxLoop)
		{
			BaseNode* node = tick.tree.actionManager.getActionById(child);
			// CCAssert(node != nullptr)
			status = node->execute(tick);
			if (status == Status::Success || status == Status::Failure)
			{
				i += 1;
			}
			else
			{
				break;
			}
		}
		tick.tree.setIterCount(actionId, i);
		return status;
	}

	void Repeater::interrupt(Tick& tick)
	{

	}

} // namespace Bt