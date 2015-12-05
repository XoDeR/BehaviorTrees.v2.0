// Copyright (c) 2015 Volodymyr Syvochka
#pragma once
#include "BtCommon.h"
#include "NodeId.h"
#include "NodeGraph.h"
#include "NodeType.h"

namespace Bt
{
	struct BaseData;
	
	struct ConditionData;
	struct ActionAtomicData;
	struct ActionTimedData;
	struct FailerData;
	struct FailerWhenEventData;
	struct RunnerData;
	struct SucceederData;
	struct WaitData;

	struct InverterData;
	struct LimiterData;
	struct MaxTimeData;
	struct RepeaterData;
	struct RepeatUntilFailureData;
	struct RepeatUntilSuccessData;

	struct SelectorData;
	struct SelectorStatefulData;
	struct SelectorRandomData;
	struct SequenceData;
	struct SequenceStatefulData;

	const uint32_t NODE_MINIMUM_FREE_INDICES = 1024;

	class NodeManager
	{
	public:
		NodeManager();
		~NodeManager();
		// non-copyable
		// non-movable
		NodeManager(const NodeManager& f) = delete;
		NodeManager(NodeManager&& f) = delete;

		NodeId createActionDataNode(BaseData* baseData);
		NodeId createNodeId();
		void removeAllNodes();
		bool isActive(NodeId nodeId);
		unordered_set<NodeId, NodeIdHasher> getActiveNodes();
		void scheduleNodeRemove(NodeId nodeId);
		void removeNodesScheduledToRemove();

		void createGraphNode(NodeId nodeId);
		void setParent(NodeId child, NodeId parent);
		vector<NodeId> getChildren(NodeId parent);

		NodeType getNodeTypeByString(string nodeTypeStr);

		BaseData* getDataByNode(NodeId nodeId);
	private:
		NodeId getNewNodeId();
		void removeNode(NodeId nodeId);

		vector<uint8_t> generation;
		deque<uint32_t> freeIndices;

		unordered_set<NodeId, NodeIdHasher> nodeIdList;
		static const NodeId invalidNodeId; // id == 0
		vector<NodeId> nodeToRemoveList;

		unordered_map<NodeId, BaseData*, NodeIdHasher> nodeIdMap;

		NodeGraph nodeGraph;
	};

} // namespace Bt