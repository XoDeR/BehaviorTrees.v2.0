#include "AiBehaviorModel.h"
#include "NodeManager.h"

#include "BaseData.h"

#include "ConditionData.h"
#include "ActionAtomicData.h"
#include "ActionTimedData.h"
#include "FailerData.h"
#include "FailerWhenEventData.h"
#include "RunnerData.h"
#include "SucceederData.h"
#include "WaitData.h"

#include "InverterData.h"
#include "LimiterData.h"
#include "MaxTimeData.h"
#include "RepeaterData.h"
#include "RepeatUntilFailureData.h"
#include "RepeatUntilSuccessData.h"

#include "SelectorData.h"
#include "SelectorStatefulData.h"
#include "SelectorRandomData.h"
#include "SequenceData.h"
#include "SequenceStatefulData.h"


using namespace pugi;
#include "Util.h"

unordered_map<UnitType, string> AiBehaviorModel::unitTypeAiFileMap =
{
	{ UnitType::SoldierAirborne, "SoldierAirborneBt.xml" },
	{ UnitType::Zeppelin, "ZeppelinBt.xml" },
	{ UnitType::Bomber, "BomberBt.xml" },
	{ UnitType::SoldierArcherLevelOne, "SoldierArcherLevelOneBt.xml" },
	{ UnitType::SoldierArcherLevelTwo, "SoldierArcherLevelTwoBt.xml" },
	{ UnitType::SoldierArcherLevelThree, "SoldierArcherLevelThreeBt.xml" },
	{ UnitType::SoldierWizardLevelOne, "SoldierWizardLevelOneBt.xml" },
	{ UnitType::SoldierWizardLevelTwo, "SoldierWizardLevelTwoBt.xml" },
	{ UnitType::SoldierWizardLevelThree, "SoldierWizardLevelThreeBt.xml" },
	{ UnitType::SoldierDwarfCannonLevelOne, "SoldierDwarfCannonLevelOneBt.xml" },
	{ UnitType::SoldierDwarfCannonLevelTwo, "SoldierDwarfCannonLevelTwoBt.xml" },
	{ UnitType::SoldierDwarfCannonLevelThree, "SoldierDwarfCannonLevelThreeBt.xml" },
	{ UnitType::SoldierDwarfTeamLevelOne, "SoldierDwarfTeamLevelOneBt.xml" },
	{ UnitType::SoldierDwarfTeamLevelTwo, "SoldierDwarfTeamLevelTwoBt.xml" },
	{ UnitType::SoldierDwarfTeamLevelThree, "SoldierDwarfTeamLevelThreeBt.xml" },
	{ UnitType::SoldierWarriorDummyCenter, "SoldierWarriorDummyCenterBt.xml" },
	{ UnitType::SoldierWarriorLevelOne, "SoldierWarriorLevelOneBt.xml" },
	{ UnitType::SoldierWarriorLevelTwo, "SoldierWarriorLevelTwoBt.xml" },
	{ UnitType::SoldierWarriorLevelThree, "SoldierWarriorLevelThreeBt.xml" },
	{ UnitType::EnemyGoblin, "EnemyGoblinBt.xml" },
	{ UnitType::EnemyGoblinFlagBearer, "EnemyGoblinFlagBearerBt.xml" },
	{ UnitType::EnemyHobgoblin, "EnemyHobgoblinBt.xml" },
	{ UnitType::EnemyGoblinSlinger, "EnemyGoblinSlingerBt.xml" },
	{ UnitType::EnemyBerserker, "EnemyBerserkerBt.xml" },
	{ UnitType::EnemyOrc, "EnemyOrcBt.xml" },
	{ UnitType::EnemyOrcChampion, "EnemyOrcChampionBt.xml" },
	{ UnitType::EnemyGargoyle, "EnemyGargoyleBt.xml" },
	{ UnitType::EnemyBeast, "EnemyBeastBt.xml" },
	{ UnitType::EnemyWolf, "EnemyWolfBt.xml" },
	{ UnitType::EnemyShaman, "EnemyShamanBt.xml" },
	{ UnitType::EnemyTroll, "EnemyTrollBt.xml" },
	{ UnitType::EnemyZombie, "EnemyZombieBt.xml" },
	{ UnitType::EnemySkeleton, "EnemySkeletonBt.xml" },
	{ UnitType::EnemySkeletonChampion, "EnemySkeletonChampionBt.xml" },
	{ UnitType::EnemySpider, "EnemySpiderBt.xml" },
	{ UnitType::EnemyNecromancer, "EnemyNecromancerBt.xml" },
	{ UnitType::EnemyNecromancerSkeleton, "EnemyNecromancerSkeletonBt.xml" },
	{ UnitType::EnemyUndeadKnight, "EnemyUndeadKnightBt.xml" },
	{ UnitType::EnemyVampire, "EnemyVampireBt.xml" },
	{ UnitType::EnemyGhost, "EnemyGhostBt.xml" },
	{ UnitType::EnemyBossOne, "EnemyBossOneBt.xml" },
	{ UnitType::EnemyBossTwo, "EnemyBossTwoBt.xml" },
	{ UnitType::EnemyBossThree, "EnemyBossThreeBt.xml" },
	{ UnitType::EnemyBossFour, "EnemyBossFourBt.xml" },
	{ UnitType::EnemyBossFive, "EnemyBossFiveBt.xml" },
};

AiBehaviorModel::AiBehaviorModel()
{
}

AiBehaviorModel::~AiBehaviorModel()
{
}

AiBehaviorModel& AiBehaviorModel::getInstance()
{
	static AiBehaviorModel instance;
	return instance;
}

void AiBehaviorModel::parseAiBehaviorForUnit(UnitType unitType)
{
	using namespace Bt;

	// remove existing data
	auto kv = unitTypeAiDataMap.find(unitType);
	if (kv != unitTypeAiDataMap.end())
	{
		unitTypeAiDataMap.erase(kv);
	}

	AiBehaviorData newAiBehaviorData;

	string fileName = unitTypeAiFileMap[unitType];
	xml_document doc;
	//xml_parse_result result = doc.load_file(FileUtils::getInstance()->fullPathForFilename(fileName).c_str());
	string folder = "../Behaviors/";

	xml_parse_result result = doc.load_file((folder + fileName).c_str());
	xpath_node rootNode = doc.select_single_node("/Behavior");
	xpath_node firstChild = rootNode.node().select_single_node("*");

	xpath_node_set firstChildChildren = firstChild.node().select_nodes("*");

	NodeManager& nodeManager = newAiBehaviorData.nodeManager;

	string nodeName = firstChild.node().name();
	NodeType nodeType = nodeManager.getNodeTypeByString(nodeName);
	NodeId root = parseActionByType(nodeManager, firstChild, nodeType);

	newAiBehaviorData.root = nodeManager.getDataByNode(root);

	// parse children recursively
	parseNode(nodeManager, root, firstChildChildren);

	unitTypeAiDataMap[unitType] = newAiBehaviorData;
}

void AiBehaviorModel::parseNode(Bt::NodeManager& nodeManager, Bt::NodeId parent, pugi::xpath_node_set xmlNodeList)
{
	using namespace Bt;

	if (xmlNodeList.empty() == true)
	{
		return; // no children
	}
	else
	{
		for (auto it = xmlNodeList.begin(); it != xmlNodeList.end(); ++it)
		{
			xpath_node xmlNode = *it;
			string nodeName = xmlNode.node().name();
			NodeType nodeType = nodeManager.getNodeTypeByString(nodeName);
			NodeId child = parseActionByType(nodeManager, xmlNode, nodeType);

			// add child to parent
			nodeManager.setParent(child, parent);
			// childNodeList
			xpath_node_set childXmlNodeList = xmlNode.node().select_nodes("*");

			// parse child
			parseNode(nodeManager, child, childXmlNodeList);
		}
	}
}

Bt::NodeId AiBehaviorModel::parseActionByType(Bt::NodeManager& nodeManager, pugi::xpath_node& node, Bt::NodeType nodeType)
{
	using namespace Bt;

	Bt::NodeId result;

	switch (nodeType)
	{
	case NodeType::ActionAtomic:
		result = parseActionAtomic(nodeManager, node);
		break;
	case NodeType::Condition:
		result = parseCondition(nodeManager, node);
		break;
	case NodeType::ActionTimed:
		result = parseActionTimed(nodeManager, node);
		break;
	case NodeType::Failer:
		result = parseFailer(nodeManager, node);
		break;
	case NodeType::FailerWhenEvent:
		result = parseFailerWhenEvent(nodeManager, node);
		break;
	case NodeType::Runner:
		result = parseRunner(nodeManager, node);
		break;
	case NodeType::Succeeder:
		result = parseSucceeder(nodeManager, node);
		break;
	case NodeType::Wait:
		result = parseWait(nodeManager, node);
		break;
	case NodeType::Inverter:
		result = parseInverter(nodeManager, node);
		break;
	case NodeType::Limiter:
		result = parseLimiter(nodeManager, node);
		break;
	case NodeType::MaxTime:
		result = parseMaxTime(nodeManager, node);
		break;
	case NodeType::Repeater:
		result = parseRepeater(nodeManager, node);
		break;
	case NodeType::RepeatUntilFailure:
		result = parseRepeatUntilFailure(nodeManager, node);
		break;
	case NodeType::RepeatUntilSuccess:
		result = parseRepeatUntilSuccess(nodeManager, node);
		break;
	case NodeType::Selector:
		result = parseSelector(nodeManager, node);
		break;
	case NodeType::SelectorStateful:
		result = parseSelectorStateful(nodeManager, node);
		break;
	case NodeType::SelectorRandom:
		result = parseSelectorRandom(nodeManager, node);
		break;
	case NodeType::Sequence:
		result = parseSequence(nodeManager, node);
		break;
	case NodeType::SequenceStateful:
		result = parseSequenceStateful(nodeManager, node);
		break;
	}

	nodeManager.createGraphNode(result);

	return result;
}

Bt::NodeId AiBehaviorModel::parseActionAtomic(Bt::NodeManager& nodeManager, pugi::xpath_node& node)
{
	using namespace Bt;
	Bt::NodeId result;

	ActionAtomicData* actionAtomicData = new ActionAtomicData();
	if (node.node().attribute("name").empty() == false)
	{
		actionAtomicData->name = node.node().attribute("name").value();
		actionAtomicData->startFunc = actionAtomicData->name;
	}
	result = nodeManager.createActionDataNode(actionAtomicData);

	return result;
}

Bt::NodeId AiBehaviorModel::parseCondition(Bt::NodeManager& nodeManager, pugi::xpath_node& node)
{
	using namespace Bt;
	Bt::NodeId result;

	ConditionData* conditionData = new ConditionData();
	if (node.node().attribute("name").empty() == false)
	{
		conditionData->name = node.node().attribute("name").value();
		conditionData->startFunc = conditionData->name;
	}
	result = nodeManager.createActionDataNode(conditionData);

	return result;
}

Bt::NodeId AiBehaviorModel::parseActionTimed(Bt::NodeManager& nodeManager, pugi::xpath_node& node)
{
	using namespace Bt;
	Bt::NodeId result;

	ActionTimedData* actionTimedData = new ActionTimedData();
	if (node.node().attribute("name").empty() == false)
	{
		actionTimedData->name = node.node().attribute("name").value();
		actionTimedData->startFunc = actionTimedData->name;
	}
	result = nodeManager.createActionDataNode(actionTimedData);

	return result;
}

Bt::NodeId AiBehaviorModel::parseFailer(Bt::NodeManager& nodeManager, pugi::xpath_node& node)
{
	using namespace Bt;
	Bt::NodeId result;

	FailerData* failerData = new FailerData();
	if (node.node().attribute("name").empty() == false)
	{
		failerData->name = node.node().attribute("name").value();
	}
	result = nodeManager.createActionDataNode(failerData);

	return result;
}

Bt::NodeId AiBehaviorModel::parseFailerWhenEvent(Bt::NodeManager& nodeManager, pugi::xpath_node& node)
{
	using namespace Bt;
	Bt::NodeId result;

	FailerWhenEventData* failerWhenEventData = new FailerWhenEventData();
	if (node.node().attribute("name").empty() == false)
	{
		failerWhenEventData->name = node.node().attribute("name").value();
	}
	if (node.node().attribute("event").empty() == false)
	{
		failerWhenEventData->eventStr = node.node().attribute("event").value();
	}
	result = nodeManager.createActionDataNode(failerWhenEventData);

	return result;
}

Bt::NodeId AiBehaviorModel::parseRunner(Bt::NodeManager& nodeManager, pugi::xpath_node& node)
{
	using namespace Bt;
	Bt::NodeId result;

	RunnerData* runnerData = new RunnerData();
	if (node.node().attribute("name").empty() == false)
	{
		runnerData->name = node.node().attribute("name").value();
	}
	result = nodeManager.createActionDataNode(runnerData);

	return result;
}

Bt::NodeId AiBehaviorModel::parseSucceeder(Bt::NodeManager& nodeManager, pugi::xpath_node& node)
{
	using namespace Bt;
	Bt::NodeId result;

	SucceederData* succeederData = new SucceederData();
	if (node.node().attribute("name").empty() == false)
	{
		succeederData->name = node.node().attribute("name").value();
	}
	result = nodeManager.createActionDataNode(succeederData);

	return result;
}

Bt::NodeId AiBehaviorModel::parseWait(Bt::NodeManager& nodeManager, pugi::xpath_node& node)
{
	using namespace Bt;
	Bt::NodeId result;

	WaitData* waitData = new WaitData();
	if (node.node().attribute("name").empty() == false)
	{
		waitData->name = node.node().attribute("name").value();
	}
	if (node.node().attribute("delay").empty() == false)
	{
		waitData->delay = node.node().attribute("delay").as_float();
	}
	result = nodeManager.createActionDataNode(waitData);

	return result;
}

Bt::NodeId AiBehaviorModel::parseInverter(Bt::NodeManager& nodeManager, pugi::xpath_node& node)
{
	using namespace Bt;
	Bt::NodeId result;

	InverterData* inverterData = new InverterData();
	if (node.node().attribute("name").empty() == false)
	{
		inverterData->name = node.node().attribute("name").value();
	}
	result = nodeManager.createActionDataNode(inverterData);

	return result;
}

Bt::NodeId AiBehaviorModel::parseLimiter(Bt::NodeManager& nodeManager, pugi::xpath_node& node)
{
	using namespace Bt;
	Bt::NodeId result;

	LimiterData* limiterData = new LimiterData();
	if (node.node().attribute("name").empty() == false)
	{
		limiterData->name = node.node().attribute("name").value();
	}
	result = nodeManager.createActionDataNode(limiterData);

	return result;
}

Bt::NodeId AiBehaviorModel::parseMaxTime(Bt::NodeManager& nodeManager, pugi::xpath_node& node)
{
	using namespace Bt;
	Bt::NodeId result;

	MaxTimeData* maxTimeData = new MaxTimeData();
	if (node.node().attribute("name").empty() == false)
	{
		maxTimeData->name = node.node().attribute("name").value();
	}
	if (node.node().attribute("maxDelay").empty() == false)
	{
		maxTimeData->maxDelay = node.node().attribute("maxDelay").as_float();
	}

	result = nodeManager.createActionDataNode(maxTimeData);

	return result;
}

Bt::NodeId AiBehaviorModel::parseRepeater(Bt::NodeManager& nodeManager, pugi::xpath_node& node)
{
	using namespace Bt;
	Bt::NodeId result;

	RepeaterData* repeaterData = new RepeaterData();
	if (node.node().attribute("name").empty() == false)
	{
		repeaterData->name = node.node().attribute("name").value();
	}
	if (node.node().attribute("maxLoop").empty() == false)
	{
		repeaterData->maxLoop = node.node().attribute("maxLoop").as_int();
	}
	result = nodeManager.createActionDataNode(repeaterData);

	return result;
}

Bt::NodeId AiBehaviorModel::parseRepeatUntilFailure(Bt::NodeManager& nodeManager, pugi::xpath_node& node)
{
	using namespace Bt;
	Bt::NodeId result;

	RepeatUntilFailureData* repeatUntilFailureData = new RepeatUntilFailureData();
	if (node.node().attribute("name").empty() == false)
	{
		repeatUntilFailureData->name = node.node().attribute("name").value();
	}
	result = nodeManager.createActionDataNode(repeatUntilFailureData);

	return result;
}

Bt::NodeId AiBehaviorModel::parseRepeatUntilSuccess(Bt::NodeManager& nodeManager, pugi::xpath_node& node)
{
	using namespace Bt;
	Bt::NodeId result;

	RepeatUntilSuccessData* repeatUntilSuccessData = new RepeatUntilSuccessData();
	if (node.node().attribute("name").empty() == false)
	{
		repeatUntilSuccessData->name = node.node().attribute("name").value();
	}
	result = nodeManager.createActionDataNode(repeatUntilSuccessData);

	return result;
}

Bt::NodeId AiBehaviorModel::parseSelector(Bt::NodeManager& nodeManager, pugi::xpath_node& node)
{
	using namespace Bt;
	Bt::NodeId result;

	SelectorData* selectorData = new SelectorData();
	if (node.node().attribute("name").empty() == false)
	{
		selectorData->name = node.node().attribute("name").value();
	}
	result = nodeManager.createActionDataNode(selectorData);

	return result;
}

Bt::NodeId AiBehaviorModel::parseSelectorStateful(Bt::NodeManager& nodeManager, pugi::xpath_node& node)
{
	using namespace Bt;
	Bt::NodeId result;

	SelectorStatefulData* selectorStatefulData = new SelectorStatefulData();
	if (node.node().attribute("name").empty() == false)
	{
		selectorStatefulData->name = node.node().attribute("name").value();
	}
	result = nodeManager.createActionDataNode(selectorStatefulData);

	return result;
}

Bt::NodeId AiBehaviorModel::parseSelectorRandom(Bt::NodeManager& nodeManager, pugi::xpath_node& node)
{
	using namespace Bt;
	Bt::NodeId result;

	SelectorRandomData* selectorRandomData = new SelectorRandomData();
	if (node.node().attribute("name").empty() == false)
	{
		selectorRandomData->name = node.node().attribute("name").value();
	}
	result = nodeManager.createActionDataNode(selectorRandomData);

	return result;
}

Bt::NodeId AiBehaviorModel::parseSequence(Bt::NodeManager& nodeManager, pugi::xpath_node& node)
{
	using namespace Bt;
	Bt::NodeId result;

	SequenceData* sequenceData = new SequenceData();
	if (node.node().attribute("name").empty() == false)
	{
		sequenceData->name = node.node().attribute("name").value();
	}
	result = nodeManager.createActionDataNode(sequenceData);

	return result;
}

Bt::NodeId AiBehaviorModel::parseSequenceStateful(Bt::NodeManager& nodeManager, pugi::xpath_node& node)
{
	using namespace Bt;
	Bt::NodeId result;

	SequenceStatefulData* sequenceStatefulData = new SequenceStatefulData();
	if (node.node().attribute("name").empty() == false)
	{
		sequenceStatefulData->name = node.node().attribute("name").value();
	}
	result = nodeManager.createActionDataNode(sequenceStatefulData);

	return result;
}


