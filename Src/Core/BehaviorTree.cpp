#include "BehaviorTree.h"
#include "BaseNode.h"
#include "Tick.h"
#include "ActionManager.h"

namespace Bt
{
	BehaviorTree::BehaviorTree(ActionManager& actionManager)
		: actionManager(actionManager)
	{

	}

	void BehaviorTree::process(float dt)
	{
		Tick tick(*this, dt);

		actionManager.getActionById(root)->execute(tick);

		// close node from last tick, if needed
		vector<ActionId> lastOpenNodeList(openNodeList.begin(), openNodeList.end());
		std::sort(lastOpenNodeList.begin(), lastOpenNodeList.end());

		vector<ActionId> currentOpenNodeList(tick.openNodeList.begin(), tick.openNodeList.end());
		std::sort(currentOpenNodeList.begin(), currentOpenNodeList.end());

		vector<ActionId> toCloseNodeList(lastOpenNodeList.size() + currentOpenNodeList.size());
		auto it = std::set_difference(lastOpenNodeList.begin(), lastOpenNodeList.end(), currentOpenNodeList.begin(), currentOpenNodeList.end(), toCloseNodeList.begin());
		toCloseNodeList.resize(it - toCloseNodeList.begin());

		// close nodes
		for (auto nodetoClose : toCloseNodeList)
		{
			actionManager.getActionById(nodetoClose)->closeInner(tick);
		}

		// save tree memory
		openNodeList = tick.openNodeList;
		nodeCount = tick.nodeCount;
	}

	bool BehaviorTree::getIsOpen(ActionId nodeId)
	{
		bool result = true;
		auto it = openNodeList.find(nodeId);
		if (it == openNodeList.end())
		{
			result = false;
		}
		return result;
	}

	void BehaviorTree::setIsOpen(ActionId nodeId, bool isOpen)
	{
		if (isOpen == true)
		{
			openNodeList.insert(nodeId);
		}
		else
		{
			openNodeList.erase(nodeId);
		}
	}

	int32_t BehaviorTree::getIterCount(ActionId nodeId)
	{
		int32_t result = -1;
		auto it = nodeIterMap.find(nodeId);
		if (it != nodeIterMap.end())
		{
			result = it->second;
		}
		return result;
	}

	void BehaviorTree::setIterCount(ActionId nodeId, int32_t iterCount)
	{
		nodeIterMap[nodeId] = iterCount;
	}

	int32_t BehaviorTree::getRunningChild(ActionId nodeId)
	{
		int32_t result = -1;
		auto it = runningChildMap.find(nodeId);
		if (it != runningChildMap.end())
		{
			result = it->second;
		}
		return result;
	}

	void BehaviorTree::setRunningChild(ActionId nodeId, int32_t runningChildIndex)
	{
		runningChildMap[nodeId] = runningChildIndex;
	}

	void BehaviorTree::setElapsedTime(ActionId nodeId, float elapsedTime)
	{
		elapsedTimeMap[nodeId] = elapsedTime;
	}

	float BehaviorTree::getElapsedTime(ActionId nodeId)
	{
		float result = -1.0f;
		auto it = elapsedTimeMap.find(nodeId);
		if (it != elapsedTimeMap.end())
		{
			result = it->second;
		}
		return result;
	}

} // namespace Bt