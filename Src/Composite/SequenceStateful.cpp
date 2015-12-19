// Copyright (c) 2015 Volodymyr Syvochka
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

	SequenceStateful::SequenceStateful()
	{

	}

	void SequenceStateful::open(Tick& tick)
	{
		tick.tree.setRunningChild(actionId, 0);
	}

	Status SequenceStateful::process(Tick& tick)
	{
		Status result =  Status::Success;

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
				break;
			}
		}

		return result;
	}

	void SequenceStateful::exit(Tick& tick)
	{
		tick.tree.setRunningChild(actionId, -1);
	}

} // namespace Bt