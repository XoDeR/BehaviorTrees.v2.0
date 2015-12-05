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

	Status SelectorRandom::process(Tick& tick)
	{
		size_t idx = tick.tree.getRunningChild(actionId);
		// CCAssert(idx != -1);

		BaseNode* node = tick.tree.actionManager.getActionById(children[idx]);
		// CCAssert(node != nullptr)
		Status status = node->execute(tick);
		return status;
	}

	void SelectorRandom::open(Tick& tick)
	{
		size_t randomChildIndex = random((unsigned int)0, children.size() - 1);
		tick.tree.setRunningChild(actionId, randomChildIndex);
	}

	void SelectorRandom::close(Tick& tick)
	{
		tick.tree.setRunningChild(actionId, -1);
	}

	void SelectorRandom::interrupt(Tick& tick)
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

} // namespace Bt
