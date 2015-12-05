#include "Sequence.h"
#include "Tick.h"
#include "BehaviorTree.h"
#include "ActionManager.h"

namespace Bt
{
	Sequence::Sequence(vector<ActionId> children)
		: Composite(children)
	{

	}

	Status Sequence::process(Tick& tick)
	{
		for (auto actionId : children)
		{
			BaseNode* node = tick.tree.actionManager.getActionById(actionId);
			Status status = node->execute(tick);
			if (status != Status::Success)
			{
				return status;
			}
		}
		return Status::Success;
	}

	void Sequence::interrupt(Tick& tick)
	{
		// todo
	}

} // namespace Bt
