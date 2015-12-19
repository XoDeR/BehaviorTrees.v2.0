// Copyright (c) 2015 Volodymyr Syvochka
#include "Inverter.h"
#include "Tick.h"
#include "BehaviorTree.h"
#include "ActionManager.h"

namespace Bt
{
	Inverter::Inverter(ActionId child)
		: Decorator(child)
	{

	}

	Inverter::Inverter()
	{
	}

	Status Inverter::process(Tick& tick)
	{
		BaseNode* node = tick.tree.actionManager.getActionById(child);
		// CCAssert(node != nullptr)
		Status status = node->execute(tick);
		if (status == Status::Success)
		{
			status = Status::Failure;
		}
		else if (status == Status::Failure)
		{
			status = Status::Success;
		}
		return status;
	}
} // namespace Bt
