// Copyright (c) 2015 Volodymyr Syvochka
#include "Selector.h"
#include "Tick.h"
#include "BehaviorTree.h"
#include "ActionManager.h"

namespace Bt
{
	Selector::Selector(vector<ActionId> children)
		: Composite(children)
	{

	}

	Selector::Selector()
	{

	}

	Status Selector::process(Tick& tick)
	{
		Status result = Status::Failure;
		for (auto actionId : children)
		{
			BaseNode* node = tick.tree.actionManager.getActionById(actionId);
			Status status = node->execute(tick);
			if (status != Status::Failure)
			{
				result = status;
				break;
			}
		}
		return result;
	}

} // namespace Bt
