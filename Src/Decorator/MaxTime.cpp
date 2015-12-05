#include "MaxTime.h"
#include "Tick.h"
#include "BehaviorTree.h"
#include "ActionManager.h"

namespace Bt
{
	MaxTime::MaxTime(ActionId child, float maxDelay)
		: Decorator(child)
		, maxDelay(maxDelay)
	{

	}

	void MaxTime::open(Tick& tick)
	{
		tick.tree.setElapsedTime(actionId, 0.0f);
	}

	Status MaxTime::process(Tick& tick)
	{
		float elapsedTime = tick.tree.getElapsedTime(actionId);

		BaseNode* node = tick.tree.actionManager.getActionById(child);
		// CCAssert(node != nullptr)
		Status status = node->execute(tick);
		if (elapsedTime > maxDelay)
		{
			return Status::Failure;
		}

		return status;
	}

} // namespace Bt