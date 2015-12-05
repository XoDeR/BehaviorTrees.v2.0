#pragma once

#include "BtCommon.h"
#include "ActionId.h"

namespace Bt
{
	class ActionManager;

	class BehaviorTree
	{
	public:
		explicit BehaviorTree(ActionManager& actionManager);
		void process(float dt);
		bool getIsOpen(ActionId nodeId);
		void setIsOpen(ActionId nodeId, bool isOpen);
		int32_t getIterCount(ActionId nodeId);
		void setIterCount(ActionId nodeId, int32_t iterCount);
		int32_t getRunningChild(ActionId nodeId);
		void setRunningChild(ActionId nodeId, int32_t runningChildIndex);
		float getElapsedTime(ActionId nodeId);
		void setElapsedTime(ActionId nodeId, float elapsedTime);

		ActionManager& actionManager;
	private:
		ActionId root = ActionId(); // default id = 0
		// tree memory
		size_t nodeCount = 0;

		unordered_set<ActionId, ActionIdHasher> openNodeList;
		unordered_map<ActionId, int32_t, ActionIdHasher> nodeIterMap;
		unordered_map<ActionId, int32_t, ActionIdHasher> runningChildMap;
		unordered_map<ActionId, float, ActionIdHasher> elapsedTimeMap;
	};

} // namespace Bt