#include "ActionManager.h"
//#include "ccMacros.h" // for CCAssert
#include "ActionAtomic.h"
#include "ActionTimed.h"
#include "Condition.h"
#include "Failer.h"
#include "FailerWhenEvent.h"
#include "Runner.h"
#include "Succeeder.h"
#include "Wait.h"
#include "Inverter.h"
#include "Limiter.h"
#include "MaxTime.h"
#include "Repeater.h"
#include "RepeatUntilFailure.h"
#include "RepeatUntilSuccess.h"
#include "Sequence.h"
#include "SequenceStateful.h"
#include "Selector.h"
#include "SelectorStateful.h"
#include "SelectorRandom.h"

namespace Bt
{
	const ActionId ActionManager::invalidActionId = ActionId();

	ActionManager::ActionManager()
	{

	}

	ActionManager::~ActionManager()
	{
		removeAllActions();
	}

	ActionId ActionManager::createActionId()
	{
		ActionId actionId = getNewActionId();
		// ensure invalid id is not used
		if (actionId == invalidActionId)
		{
			actionId = getNewActionId();
		}
		actionIdList.insert(actionId);
		return actionId;
	}

	ActionId ActionManager::getNewActionId()
	{
		uint32_t actionId;
		if (freeIndices.size() > ACTION_MINIMUM_FREE_INDICES)
		{
			actionId = freeIndices.front();
			freeIndices.pop_front();
		}
		else
		{
			generation.push_back(0);
			actionId = generation.size() - 1;
			//CCAssert(actionId < (1 << ACTION_INDEX_BITS), "Action Index exceeded limit");
		}
		return ActionId(actionId);
	}

	bool ActionManager::isActive(ActionId actionId)
	{
		//CCAssert(actionId != invalidActionId, "Attempt to use entity with invalid id");
		return generation[actionId.getIndex()] == actionId.getGeneration();
	}

	void ActionManager::removeAction(ActionId actionId)
	{
		if (actionId.id != 0 && isActive(actionId) == true)
		{
			// interrupt dependent actions if any
			BaseNode* node = getActionById(actionId);
			// CCAssert(node != nullptr)
			////node->interrupt(actionId);

			const uint32_t actionIndex = actionId.getIndex();
			++generation[actionIndex];
			freeIndices.push_back(actionIndex);

			actionIdList.erase(actionId);

			// remove from these as well
			//actionIdMap


		}
	}

	void ActionManager::removeAllActions()
	{
		for (ActionId actionId : actionIdList)
		{
			removeAction(actionId);
		}
	}

	unordered_set<ActionId, ActionIdHasher> ActionManager::getActiveActions()
	{
		return actionIdList;
	}

	void ActionManager::scheduleActionRemove(ActionId actionId)
	{
		actionToRemoveList.push_back(actionId);
	}

	void ActionManager::removeEntitiesScheduledToRemove()
	{
		if (actionToRemoveList.empty() == false)
		{
			vector<ActionId> actionToRemoveListCopy(actionToRemoveList); // for case some entity will be scheduled to remove after this entity removal (in component destructor)
			for (auto actionId : actionToRemoveListCopy)
			{
				removeAction(actionId);
			}
			if (actionToRemoveList.size() > actionToRemoveListCopy.size())
			{
				// new remove added
				actionToRemoveList.erase(actionToRemoveList.begin(), actionToRemoveList.begin() + actionToRemoveListCopy.size());
			}
			else
			{
				actionToRemoveList.clear();
			}
		}
	}

	BaseNode* ActionManager::getActionById(ActionId actionId)
	{
		BaseNode* result = nullptr;
		auto it = actionIdMap.find(actionId);
		if (it != actionIdMap.end())
		{
			result = it->second;
		}
		return result;
	}

	ActionId ActionManager::createActionAtomic(std::function<void()>&& startFunc)
	{
		ActionId actionId = createActionId();
		ActionAtomic* actionAtomic = new ActionAtomic(std::move(startFunc));
		actionIdMap[actionId] = actionAtomic;
		return actionId;
	}

	ActionId ActionManager::createCondition(std::function<bool()>&& startFunc)
	{
		ActionId actionId = createActionId();
		Condition* condition = new Condition(std::move(startFunc));
		actionIdMap[actionId] = condition;
		return actionId;
	}

	ActionId ActionManager::createActionTimed(std::function<void()>&& startFunc, std::function<void()>&& interruptFunc)
	{
		ActionId actionId = createActionId();
		ActionTimed* actionTimed = new ActionTimed(std::move(startFunc), std::move(interruptFunc));
		actionIdMap[actionId] = actionTimed;
		return actionId;
	}

	ActionId ActionManager::createFailer()
	{
		ActionId actionId = createActionId();
		Failer* failer = new Failer();
		actionIdMap[actionId] = failer;
		return actionId;
	}

	ActionId ActionManager::createFailerWhenEvent(EventType eventToFailWith)
	{
		ActionId actionId = createActionId();
		FailerWhenEvent* failerWhenEvent = new FailerWhenEvent(eventToFailWith);
		actionIdMap[actionId] = failerWhenEvent;
		return actionId;
	}

	ActionId ActionManager::createRunner()
	{
		ActionId actionId = createActionId();
		Runner* runner = new Runner();
		actionIdMap[actionId] = runner;
		return actionId;
	}

	ActionId ActionManager::createSucceeder()
	{
		ActionId actionId = createActionId();
		Succeeder* succeeder = new Succeeder();
		actionIdMap[actionId] = succeeder;
		return actionId;
	}

	ActionId ActionManager::createWait(float delay)
	{
		ActionId actionId = createActionId();
		Wait* wait = new Wait(delay);
		actionIdMap[actionId] = wait;
		return actionId;
	}

	ActionId ActionManager::createInverter(ActionId innerAction)
	{
		ActionId actionId = createActionId();
		Inverter* inverter = new Inverter(innerAction);
		actionIdMap[actionId] = inverter;
		return actionId;
	}

	ActionId ActionManager::createLimiter(ActionId innerAction, int32_t maxLoop)
	{
		ActionId actionId = createActionId();
		Limiter* limiter = new Limiter(innerAction, maxLoop);
		actionIdMap[actionId] = limiter;
		return actionId;
	}

	ActionId ActionManager::createMaxTime(ActionId innerAction, float maxDelay)
	{
		ActionId actionId = createActionId();
		MaxTime* maxTime = new MaxTime(innerAction, maxDelay);
		actionIdMap[actionId] = maxTime;
		return actionId;
	}

	ActionId ActionManager::createRepeater(ActionId innerAction, int32_t maxLoop /*= -1*/)
	{
		ActionId actionId = createActionId();
		Repeater* repeater = new Repeater(innerAction, maxLoop);
		actionIdMap[actionId] = repeater;
		return actionId;
	}

	ActionId ActionManager::createRepeatUntilFailure(ActionId innerAction, int32_t maxLoop /*= -1*/)
	{
		ActionId actionId = createActionId();
		RepeatUntilFailure* repeatUntilFailure = new RepeatUntilFailure(innerAction, maxLoop);
		actionIdMap[actionId] = repeatUntilFailure;
		return actionId;
	}

	ActionId ActionManager::createRepeatUntilSuccess(ActionId innerAction, int32_t maxLoop /*= -1*/)
	{
		ActionId actionId = createActionId();
		RepeatUntilSuccess* repeatUntilSuccess = new RepeatUntilSuccess(innerAction, maxLoop);
		actionIdMap[actionId] = repeatUntilSuccess;
		return actionId;
	}

	ActionId ActionManager::createSequence(vector<ActionId> actionList)
	{
		ActionId actionId = createActionId();
		Sequence* sequence = new Sequence(actionList);
		actionIdMap[actionId] = sequence;
		return actionId;
	}

	ActionId ActionManager::createSelector(vector<ActionId> actionList)
	{
		ActionId actionId = createActionId();
		Selector* selector = new Selector(actionList);
		actionIdMap[actionId] = selector;
		return actionId;
	}

	ActionId ActionManager::createSequenceStateful(vector<ActionId> actionList)
	{
		ActionId actionId = createActionId();
		SequenceStateful* sequenceStateful = new SequenceStateful(actionList);
		actionIdMap[actionId] = sequenceStateful;
		return actionId;
	}

	ActionId ActionManager::createSelectorStateful(vector<ActionId> actionList)
	{
		ActionId actionId = createActionId();
		SelectorStateful* selectorStateful = new SelectorStateful(actionList);
		actionIdMap[actionId] = selectorStateful;
		return actionId;
	}

	Bt::ActionId ActionManager::createSelectorRandom(vector<ActionId> actionList)
	{
		ActionId actionId = createActionId();
		SelectorRandom* selectorRandom = new SelectorRandom(actionList);
		actionIdMap[actionId] = selectorRandom;
		return actionId;
	}

} // namespace Bt