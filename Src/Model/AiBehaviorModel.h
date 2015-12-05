// Copyright (c) 2015 Volodymyr Syvochka
#pragma once
#include "BtCommon.h"
#include "UnitType.h"
#include "NodeId.h"
#include "NodeType.h"

#include "AiBehaviorData.h"

#include "pugixml.hpp"

namespace Bt
{
	class NodeManager;
}

struct NodeSet
{
	vector<Bt::NodeId> nodeIdList;
	pugi::xpath_node_set xmlNodeList;
};

class AiBehaviorModel
{
public:
	static AiBehaviorModel& getInstance();

	void parseAiBehaviorForUnit(UnitType unitType);

	void parseNode(Bt::NodeManager& nodeManager, Bt::NodeId parent, pugi::xpath_node_set xmlNodeList);

	Bt::NodeId parseActionByType(Bt::NodeManager& nodeManager, pugi::xpath_node& node, Bt::NodeType nodeType);

	Bt::NodeId parseActionAtomic(Bt::NodeManager& nodeManager, pugi::xpath_node& node);
	Bt::NodeId parseCondition(Bt::NodeManager& nodeManager, pugi::xpath_node& node);
	Bt::NodeId parseActionTimed(Bt::NodeManager& nodeManager, pugi::xpath_node& node);
	Bt::NodeId parseFailer(Bt::NodeManager& nodeManager, pugi::xpath_node& node);
	Bt::NodeId parseFailerWhenEvent(Bt::NodeManager& nodeManager, pugi::xpath_node& node);
	Bt::NodeId parseRunner(Bt::NodeManager& nodeManager, pugi::xpath_node& node);
	Bt::NodeId parseSucceeder(Bt::NodeManager& nodeManager, pugi::xpath_node& node);
	Bt::NodeId parseWait(Bt::NodeManager& nodeManager, pugi::xpath_node& node);
	Bt::NodeId parseInverter(Bt::NodeManager& nodeManager, pugi::xpath_node& node);
	Bt::NodeId parseLimiter(Bt::NodeManager& nodeManager, pugi::xpath_node& node);
	Bt::NodeId parseMaxTime(Bt::NodeManager& nodeManager, pugi::xpath_node& node);
	Bt::NodeId parseRepeater(Bt::NodeManager& nodeManager, pugi::xpath_node& node);
	Bt::NodeId parseRepeatUntilFailure(Bt::NodeManager& nodeManager, pugi::xpath_node& node);
	Bt::NodeId parseRepeatUntilSuccess(Bt::NodeManager& nodeManager, pugi::xpath_node& node);
	Bt::NodeId parseSelector(Bt::NodeManager& nodeManager, pugi::xpath_node& node);
	Bt::NodeId parseSelectorStateful(Bt::NodeManager& nodeManager, pugi::xpath_node& node);
	Bt::NodeId parseSelectorRandom(Bt::NodeManager& nodeManager, pugi::xpath_node& node);
	Bt::NodeId parseSequence(Bt::NodeManager& nodeManager, pugi::xpath_node& node);
	Bt::NodeId parseSequenceStateful(Bt::NodeManager& nodeManager, pugi::xpath_node& node);
private:
	AiBehaviorModel();
	~AiBehaviorModel();
	AiBehaviorModel(const AiBehaviorModel& rhs) = delete;
	AiBehaviorModel& operator=(const AiBehaviorModel& rhs) = delete;
	AiBehaviorModel(AiBehaviorModel&& rhs) = delete;
	AiBehaviorModel& operator=(AiBehaviorModel&& rhs) = delete;
public:
	unordered_map<UnitType, Bt::AiBehaviorData> unitTypeAiDataMap;
	static unordered_map<UnitType, string> unitTypeAiFileMap;
};
