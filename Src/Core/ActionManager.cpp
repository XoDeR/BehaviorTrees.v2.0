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

#include "BaseData.h"
#include "World.h"
#include "UnitFnRegistry.h"

#include "FailerWhenEventData.h"
#include "WaitData.h"
#include "LimiterData.h"
#include "MaxTimeData.h"
#include "RepeaterData.h"
#include "RepeatUntilFailureData.h"
#include "RepeatUntilSuccessData.h"

namespace Bt
{
	const ActionId ActionManager::invalidActionId = ActionId();

	ActionManager::ActionManager(World& world, Entity e)
		: world(world)
		, e(e)
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
			result = it->second.get();
		}
		return result;
	}

	ActionId ActionManager::createActionAtomic(std::function<void()>&& startFunc)
	{
		ActionId actionId = createActionId();
		unique_ptr<ActionAtomic> actionAtomic(new ActionAtomic(std::move(startFunc)));
		actionIdMap[actionId] = std::move(actionAtomic);
		return actionId;
	}

	ActionId ActionManager::createCondition(std::function<bool()>&& startFunc)
	{
		ActionId actionId = createActionId();
		unique_ptr<Condition> condition(new Condition(std::move(startFunc)));
		actionIdMap[actionId] = std::move(condition);
		return actionId;
	}

	ActionId ActionManager::createActionTimed(std::function<void()>&& startFunc, std::function<void()>&& interruptFunc)
	{
		ActionId actionId = createActionId();
		unique_ptr<ActionTimed> actionTimed(new ActionTimed(std::move(startFunc), std::move(interruptFunc)));
		actionIdMap[actionId] = std::move(actionTimed);
		return actionId;
	}

	ActionId ActionManager::createActionTimed()
	{
		ActionId actionId = createActionId();
		unique_ptr<ActionTimed> actionTimed(new ActionTimed());
		actionIdMap[actionId] = std::move(actionTimed);
		return actionId;
	}

	ActionId ActionManager::createFailer()
	{
		ActionId actionId = createActionId();
		unique_ptr<Failer> failer(new Failer());
		actionIdMap[actionId] = std::move(failer);
		return actionId;
	}

	ActionId ActionManager::createFailerWhenEvent(EventType eventToFailWith)
	{
		ActionId actionId = createActionId();
		unique_ptr<FailerWhenEvent> failerWhenEvent(new FailerWhenEvent(eventToFailWith));
		actionIdMap[actionId] = std::move(failerWhenEvent);
		return actionId;
	}

	ActionId ActionManager::createRunner()
	{
		ActionId actionId = createActionId();
		unique_ptr<Runner> runner(new Runner());
		actionIdMap[actionId] = std::move(runner);
		return actionId;
	}

	ActionId ActionManager::createSucceeder()
	{
		ActionId actionId = createActionId();
		unique_ptr<Succeeder> succeeder(new Succeeder());
		actionIdMap[actionId] = std::move(succeeder);
		return actionId;
	}

	ActionId ActionManager::createWait(float delay)
	{
		ActionId actionId = createActionId();
		unique_ptr<Wait> wait(new Wait(delay));
		actionIdMap[actionId] = std::move(wait);
		return actionId;
	}

	ActionId ActionManager::createInverter(ActionId innerAction)
	{
		ActionId actionId = createActionId();
		unique_ptr<Inverter> inverter(new Inverter(innerAction));
		actionIdMap[actionId] = std::move(inverter);
		return actionId;
	}

	ActionId ActionManager::createInverter()
	{
		ActionId actionId = createActionId();
		unique_ptr<Inverter> inverter(new Inverter());
		actionIdMap[actionId] = std::move(inverter);
		return actionId;
	}

	ActionId ActionManager::createLimiter(ActionId innerAction, int32_t maxLoop)
	{
		ActionId actionId = createActionId();
		unique_ptr<Limiter> limiter(new Limiter(innerAction, maxLoop));
		actionIdMap[actionId] = std::move(limiter);
		return actionId;
	}

	ActionId ActionManager::createLimiter(int32_t maxLoop)
	{
		ActionId actionId = createActionId();
		unique_ptr<Limiter> limiter(new Limiter(maxLoop));
		actionIdMap[actionId] = std::move(limiter);
		return actionId;
	}

	ActionId ActionManager::createMaxTime(ActionId innerAction, float maxDelay)
	{
		ActionId actionId = createActionId();
		unique_ptr<MaxTime> maxTime(new MaxTime(innerAction, maxDelay));
		actionIdMap[actionId] = std::move(maxTime);
		return actionId;
	}

	ActionId ActionManager::createMaxTime(float maxDelay)
	{
		ActionId actionId = createActionId();
		unique_ptr<MaxTime> maxTime(new MaxTime(maxDelay));
		actionIdMap[actionId] = std::move(maxTime);
		return actionId;
	}

	ActionId ActionManager::createRepeater(ActionId innerAction, int32_t maxLoop /*= -1*/)
	{
		ActionId actionId = createActionId();
		unique_ptr<Repeater> repeater(new Repeater(innerAction, maxLoop));
		actionIdMap[actionId] = std::move(repeater);
		return actionId;
	}

	ActionId ActionManager::createRepeater(int32_t maxLoop /*= -1*/)
	{
		ActionId actionId = createActionId();
		unique_ptr<Repeater> repeater(new Repeater(maxLoop));
		actionIdMap[actionId] = std::move(repeater);
		return actionId;
	}

	ActionId ActionManager::createRepeatUntilFailure(ActionId innerAction, int32_t maxLoop /*= -1*/)
	{
		ActionId actionId = createActionId();
		unique_ptr<RepeatUntilFailure> repeatUntilFailure(new RepeatUntilFailure(innerAction, maxLoop));
		actionIdMap[actionId] = std::move(repeatUntilFailure);
		return actionId;
	}

	ActionId ActionManager::createRepeatUntilFailure(int32_t maxLoop /*= -1*/)
	{
		ActionId actionId = createActionId();
		unique_ptr<RepeatUntilFailure> repeatUntilFailure(new RepeatUntilFailure(maxLoop));
		actionIdMap[actionId] = std::move(repeatUntilFailure);
		return actionId;
	}

	ActionId ActionManager::createRepeatUntilSuccess(ActionId innerAction, int32_t maxLoop /*= -1*/)
	{
		ActionId actionId = createActionId();
		unique_ptr<RepeatUntilSuccess> repeatUntilSuccess(new RepeatUntilSuccess(innerAction, maxLoop));
		actionIdMap[actionId] = std::move(repeatUntilSuccess);
		return actionId;
	}

	ActionId ActionManager::createRepeatUntilSuccess(int32_t maxLoop /*= -1*/)
	{
		ActionId actionId = createActionId();
		unique_ptr<RepeatUntilSuccess> repeatUntilSuccess(new RepeatUntilSuccess(maxLoop));
		actionIdMap[actionId] = std::move(repeatUntilSuccess);
		return actionId;
	}

	ActionId ActionManager::createSequence(vector<ActionId> actionList)
	{
		ActionId actionId = createActionId();
		unique_ptr<Sequence> sequence(new Sequence(actionList));
		actionIdMap[actionId] = std::move(sequence);
		return actionId;
	}

	ActionId ActionManager::createSequence()
	{
		ActionId actionId = createActionId();
		unique_ptr<Sequence> sequence(new Sequence());
		actionIdMap[actionId] = std::move(sequence);
		return actionId;
	}

	ActionId ActionManager::createSelector(vector<ActionId> actionList)
	{
		ActionId actionId = createActionId();
		unique_ptr<Selector> selector(new Selector(actionList));
		actionIdMap[actionId] = std::move(selector);
		return actionId;
	}

	ActionId ActionManager::createSelector()
	{
		ActionId actionId = createActionId();
		unique_ptr<Selector> selector(new Selector());
		actionIdMap[actionId] = std::move(selector);
		return actionId;
	}

	ActionId ActionManager::createSequenceStateful(vector<ActionId> actionList)
	{
		ActionId actionId = createActionId();
		unique_ptr<SequenceStateful> sequenceStateful(new SequenceStateful(actionList));
		actionIdMap[actionId] = std::move(sequenceStateful);
		return actionId;
	}

	ActionId ActionManager::createSequenceStateful()
	{
		ActionId actionId = createActionId();
		unique_ptr<SequenceStateful> sequenceStateful(new SequenceStateful());
		actionIdMap[actionId] = std::move(sequenceStateful);
		return actionId;
	}

	ActionId ActionManager::createSelectorStateful(vector<ActionId> actionList)
	{
		ActionId actionId = createActionId();
		unique_ptr<SelectorStateful> selectorStateful(new SelectorStateful(actionList));
		actionIdMap[actionId] = std::move(selectorStateful);
		return actionId;
	}

	ActionId ActionManager::createSelectorStateful()
	{
		ActionId actionId = createActionId();
		unique_ptr<SelectorStateful> selectorStateful(new SelectorStateful());
		actionIdMap[actionId] = std::move(selectorStateful);
		return actionId;
	}

	Bt::ActionId ActionManager::createSelectorRandom(vector<ActionId> actionList)
	{
		ActionId actionId = createActionId();
		unique_ptr<SelectorRandom> selectorRandom(new SelectorRandom(actionList));
		actionIdMap[actionId] = std::move(selectorRandom);
		return actionId;
	}

	Bt::ActionId ActionManager::createSelectorRandom()
	{
		ActionId actionId = createActionId();
		unique_ptr<SelectorRandom> selectorRandom(new SelectorRandom());
		actionIdMap[actionId] = std::move(selectorRandom);
		return actionId;
	}

	Bt::ActionId ActionManager::createActionWithData(const Bt::BaseData& baseData)
	{
		using namespace Bt;

		ActionId result;

		switch (baseData.nodeType)
		{
		case NodeType::ActionAtomic:
		{
			StringId64 stringId(baseData.name.c_str());
			result = createActionAtomic(std::move(UnitFnRegistry::getActionAtomicFunction(world, e, stringId)));
		}
		break;
		case NodeType::Condition:
		{
			StringId64 stringId(baseData.name.c_str());
			result = createCondition(std::move(UnitFnRegistry::getConditionFunction(world, e, stringId)));
		}
		break;
		case NodeType::ActionTimed:
		{
			result = createActionTimed();
			ActionTimed* actionTimed = static_cast<ActionTimed*>(getActionById(result));
			std::function<void()>* onFinished = actionTimed->getOnFinishedCallback();
			StringId64 stringId(baseData.name.c_str());
			actionTimed->setStartFunction(std::move(UnitFnRegistry::getActionTimedStartFunction(world, e, stringId, *onFinished)));
			actionTimed->setInterruptFunction(std::move(UnitFnRegistry::getActionTimedInterruptFunction(world, e, stringId)));
		}
		break;
		case NodeType::Failer:
		{
			result = createFailer();
		}
		break;
		case NodeType::FailerWhenEvent:
		{
			const FailerWhenEventData* failerWhenEventData = static_cast<const FailerWhenEventData*>(&baseData);
			// event support not implemented yet
			// eventToFailWith = getEventTypeFromString(failerWhenEventData->eventStr);
			EventType eventToFailWith = EventType::None;
			result = createFailerWhenEvent(eventToFailWith);
		}
		break;
		case NodeType::Runner:
		{
			result = createRunner();
		}
		break;
		case NodeType::Succeeder:
		{
			result = createSucceeder();
		}
		break;
		case NodeType::Wait:
		{
			const WaitData* waitData = static_cast<const WaitData*>(&baseData);
			result = createWait(waitData->delay);
		}
		break;
		case NodeType::Inverter:
		{
			result = createInverter();
		}
		break;
		case NodeType::Limiter:
		{
			const LimiterData* limiterData = static_cast<const LimiterData*>(&baseData);
			result = createLimiter(limiterData->maxLoop);
		}
		break;
		case NodeType::MaxTime:
		{
			const MaxTimeData* maxTimeData = static_cast<const MaxTimeData*>(&baseData);
			result = createMaxTime(maxTimeData->maxDelay);
		}
		break;
		case NodeType::Repeater:
		{
			const RepeaterData* repeaterData = static_cast<const RepeaterData*>(&baseData);
			result = createRepeater(repeaterData->maxLoop);
		}
		break;
		case NodeType::RepeatUntilFailure:
		{
			const RepeatUntilFailureData* repeatUntilFailureData = static_cast<const RepeatUntilFailureData*>(&baseData);
			result = createRepeatUntilFailure(repeatUntilFailureData->maxLoop);
		}
		break;
		case NodeType::RepeatUntilSuccess:
		{
			const RepeatUntilSuccessData* repeatUntilSuccessData = static_cast<const RepeatUntilSuccessData*>(&baseData);
			result = createRepeatUntilSuccess(repeatUntilSuccessData->maxLoop);
		}
		break;
		case NodeType::Selector:
		{
			result = createSelector();
		}
		break;
		case NodeType::SelectorStateful:
		{
			result = createSelectorStateful();
		}
		break;
		case NodeType::SelectorRandom:
		{
			result = createSelectorRandom();
		}
		break;
		case NodeType::Sequence:
		{
			result = createSequence();
		}
		break;
		case NodeType::SequenceStateful:
		{
			result = createSequenceStateful();
		}
		break;
		default:
		{
			CCAssert(false, "");
		}
		}

		return result;
	}

} // namespace Bt