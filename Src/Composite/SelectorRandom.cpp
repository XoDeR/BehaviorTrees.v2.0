// Copyright (c) 2015 Volodymyr Syvochka
#include "SelectorRandom.h"
#include "Tick.h"
#include "BehaviorTree.h"
#include "ActionManager.h"
#include "Random.h"

namespace Bt
{
	SelectorRandom::SelectorRandom(vector<ActionId> children)
		: Composite(children)
	{

	}

	SelectorRandom::SelectorRandom()
	{

	}

	void SelectorRandom::open(Tick& tick)
	{
		size_t randomChildIndex = random((unsigned int)0, children.size() - 1);
		tick.tree.setRunningChild(actionId, randomChildIndex);
	}

	Status SelectorRandom::process(Tick& tick)
	{
		int32_t idx = tick.tree.getRunningChild(actionId);
		CCAssert(idx != -1, "running child should be set in open function");
		BaseNode* node = tick.tree.actionManager.getActionById(children[idx]);
		// CCAssert(node != nullptr)
		Status status = node->execute(tick);
		return status;
	}

	void SelectorRandom::exit(Tick& tick)
	{
		tick.tree.setRunningChild(actionId, -1);
	}

} // namespace Bt
