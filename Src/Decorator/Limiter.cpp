// Copyright (c) 2015 Volodymyr Syvochka
#include "Limiter.h"
#include "Tick.h"
#include "BehaviorTree.h"
#include "ActionManager.h"

namespace Bt
{
	Limiter::Limiter(ActionId child, int32_t maxLoop)
		: Decorator(child)
		, maxLoop(maxLoop)
	{

	}

	Limiter::Limiter(int32_t maxLoop)
		: maxLoop(maxLoop)
	{

	}

	void Limiter::open(Tick& tick)
	{
		tick.tree.setIterCount(actionId, 0);
	}

	Status Limiter::process(Tick& tick)
	{
		int32_t i = tick.tree.getIterCount(actionId);
		if (i < maxLoop)
		{
			BaseNode* node = tick.tree.actionManager.getActionById(child);
			// CCAssert(node != nullptr)
			Status status = node->execute(tick);

			if (status == Status::Success || status == Status::Failure)
			{
				tick.tree.setIterCount(actionId, i + 1);
				return status;
			}
		}
		return Status::Failure;
	}

} // namespace Bt