// Copyright (c) 2015 Volodymyr Syvochka
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

	Sequence::Sequence()
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

} // namespace Bt
