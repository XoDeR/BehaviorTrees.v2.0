#include "SelectorStateful.h"
#include "Tick.h"
#include "BehaviorTree.h"
#include "Tick.h"
#include "BehaviorTree.h"
#include "ActionManager.h"

namespace Bt
{
	SelectorStateful::SelectorStateful(vector<ActionId> children)
		: Composite(children)
	{
	}

	Status SelectorStateful::process(Tick& tick)
	{
		size_t idx = tick.tree.getRunningChild(actionId);
		// CCAssert(idx != -1);

		for (size_t i = idx; i < children.size(); ++i)
		{
			BaseNode* node = tick.tree.actionManager.getActionById(children[i]);
			// CCAssert(node != nullptr)
			Status status = node->execute(tick);
			if (status != Status::Failure)
			{
				if (status == Status::Running)
				{
					tick.tree.setRunningChild(actionId, i);
					return status;
				}
			}
		}
		return Status::Failure;
	}

	void SelectorStateful::interrupt(Tick& tick)
	{
		int32_t idx = tick.tree.getRunningChild(actionId);

		if (idx != -1)
		{
			BaseNode* node = tick.tree.actionManager.getActionById(children[idx]);
			// CCAssert(node != nullptr)
			node->interrupt(tick);
		}

		tick.tree.setRunningChild(actionId, -1);
	}

	void SelectorStateful::open(Tick& tick)
	{
		tick.tree.setRunningChild(actionId, 0);
	}

	void SelectorStateful::close(Tick& tick)
	{
		tick.tree.setRunningChild(actionId, -1);
	}

} // namespace Bt