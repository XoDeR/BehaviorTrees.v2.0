// Copyright (c) 2015 Volodymyr Syvochka
#pragma once
#include "BtCommon.h"
#include "ActionId.h"

#include "BaseNode.h"
#include "ActionEventType.h"

//namespace std
//{
//	template <> struct hash<Bt::ActionId>
//	{
//		size_t operator()(const Bt::ActionId& x) const
//		{
//			return hash<uint32_t>()(x.id);
//		}
//	};
//}

namespace Bt
{
	const uint32_t ACTION_MINIMUM_FREE_INDICES = 1024;

	class ActionManager
	{
	public:
		ActionManager();
		~ActionManager();
		// non-copyable
		// non-movable
		ActionManager(const ActionManager& f) = delete;
		ActionManager(ActionManager&& f) = delete;

		ActionId createActionAtomic(std::function<void()>&& startFunc);
		ActionId createCondition(std::function<bool()>&& startFunc);
		ActionId createActionTimed(std::function<void()>&& startFunc, std::function<void()>&& interruptFunc);
		
		ActionId createFailer();
		ActionId createFailerWhenEvent(EventType eventToFailWith);
		ActionId createRunner();
		ActionId createSucceeder();
		ActionId createWait(float delay);

		ActionId createInverter(ActionId innerAction);
		ActionId createLimiter(ActionId innerAction, int32_t maxLoop);
		ActionId createMaxTime(ActionId innerAction, float maxDelay);
		ActionId createRepeater(ActionId innerAction, int32_t maxLoop = -1);
		ActionId createRepeatUntilFailure(ActionId innerAction, int32_t maxLoop = -1);
		ActionId createRepeatUntilSuccess(ActionId innerAction, int32_t maxLoop = -1);
		
		ActionId createSequence(vector<ActionId> actionList);
		ActionId createSequenceStateful(vector<ActionId> actionList);
		ActionId createSelector(vector<ActionId> actionList);
		ActionId createSelectorStateful(vector<ActionId> actionList);
		ActionId createSelectorRandom(vector<ActionId> actionList);

		BaseNode* getActionById(ActionId actionId);

		ActionId createActionId();
		void removeAllActions();
		bool isActive(ActionId actionId);
		unordered_set<ActionId, ActionIdHasher> getActiveActions();
		void scheduleActionRemove(ActionId actionId);
		void removeEntitiesScheduledToRemove();
	private:
		ActionId getNewActionId();
		void removeAction(ActionId actionId);

		vector<uint8_t> generation;
		deque<uint32_t> freeIndices;

		unordered_set<ActionId, ActionIdHasher> actionIdList;
		static const ActionId invalidActionId; // id == 0
		vector<ActionId> actionToRemoveList;

		unordered_map<ActionId, BaseNode*, ActionIdHasher> actionIdMap;
	};

} // namespace Bt