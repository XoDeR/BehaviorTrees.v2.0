// Copyright (c) 2015 Volodymyr Syvochka
#pragma once
#include "BtCommon.h"
#include "ActionId.h"

#include "BaseNode.h"
#include "ActionEventType.h"
#include "Entity.h"

class World;

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
	class BaseData;

	const uint32_t ACTION_MINIMUM_FREE_INDICES = 1024;

	class ActionManager
	{
	public:
		ActionManager(World& world, Entity e);
		~ActionManager();
		// non-copyable
		// non-movable
		ActionManager(const ActionManager& f) = delete;
		ActionManager(ActionManager&& f) = delete;

		ActionId createActionWithData(const Bt::BaseData& baseData);

		ActionId createActionAtomic(std::function<void()>&& startFunc);
		ActionId createCondition(std::function<bool()>&& startFunc);
		ActionId createActionTimed(std::function<void()>&& startFunc, std::function<void()>&& interruptFunc);
		ActionId createActionTimed();
		
		ActionId createFailer();
		ActionId createFailerWhenEvent(EventType eventToFailWith);
		ActionId createRunner();
		ActionId createSucceeder();
		ActionId createWait(float delay);

		// decorators
		ActionId createInverter(ActionId innerAction);
		ActionId createInverter();
		ActionId createLimiter(ActionId innerAction, int32_t maxLoop);
		ActionId createLimiter(int32_t maxLoop);
		ActionId createMaxTime(ActionId innerAction, float maxDelay);
		ActionId createMaxTime(float maxDelay);
		ActionId createRepeater(ActionId innerAction, int32_t maxLoop = -1);
		ActionId createRepeater(int32_t maxLoop = -1);
		ActionId createRepeatUntilFailure(ActionId innerAction, int32_t maxLoop = -1);
		ActionId createRepeatUntilFailure(int32_t maxLoop = -1);
		ActionId createRepeatUntilSuccess(ActionId innerAction, int32_t maxLoop = -1);
		ActionId createRepeatUntilSuccess(int32_t maxLoop = -1);
		
		// composites
		ActionId createSequence(vector<ActionId> actionList);
		ActionId createSequence();
		ActionId createSequenceStateful(vector<ActionId> actionList);
		ActionId createSequenceStateful();
		ActionId createSelector(vector<ActionId> actionList);
		ActionId createSelector();
		ActionId createSelectorStateful(vector<ActionId> actionList);
		ActionId createSelectorStateful();
		ActionId createSelectorRandom(vector<ActionId> actionList);
		ActionId createSelectorRandom();

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

		// owner
		unordered_map<ActionId, unique_ptr<BaseNode>, ActionIdHasher> actionIdMap;

		World& world;
		Entity e;
	};

} // namespace Bt