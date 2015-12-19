// Copyright (c) 2015 Volodymyr Syvochka
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

	SelectorStateful::SelectorStateful()
	{

	}

	void SelectorStateful::open(Tick& tick)
	{
		tick.tree.setRunningChild(actionId, 0);
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

	void SelectorStateful::exit(Tick& tick)
	{
		tick.tree.setRunningChild(actionId, -1);
	}

} // namespace Bt