#include "SequenceStateful.h"
#include "Tick.h"
#include "BehaviorTree.h"
#include "ActionManager.h"

namespace Bt
{
	SequenceStateful::SequenceStateful(vector<ActionId> children)
		: Composite(children)
	{

	}

	void SequenceStateful::open(Tick& tick)
	{
		tick.tree.setRunningChild(actionId, 0);
	}

	Status SequenceStateful::process(Tick& tick)
	{
		size_t idx = tick.tree.getRunningChild(actionId);

		for (size_t i = idx; i < children.size(); ++i)
		{
			BaseNode* node = tick.tree.actionManager.getActionById(children[i]);
			Status status = node->execute(tick);

			if (status != Status::Success)
			{
				if (status == Status::Running)
				{
					tick.tree.setRunningChild(actionId, i);
				}
				return status;
			}
		}

		return Status::Success;
	}

	void SequenceStateful::interrupt(Tick& tick)
	{
		size_t idx = tick.tree.getRunningChild(actionId);
		// CCAssert(idx != -1, "");
		BaseNode* node = tick.tree.actionManager.getActionById(children[idx]);
		node->interrupt(tick);
	}

} // namespace Bt