#include "NodeManager.h"
//#include "ccMacros.h" // for CCAssert
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

namespace Bt
{
	const NodeId NodeManager::invalidNodeId = NodeId();

	NodeManager::NodeManager()
	{

	}

	NodeManager::~NodeManager()
	{
		removeAllNodes();
	}

	Bt::NodeId NodeManager::createActionDataNode(BaseData* baseData)
	{
		NodeId newNodeId = createNodeId();
		baseData->id = newNodeId;
		nodeIdMap[newNodeId] = baseData;

		return newNodeId;
	}

	NodeId NodeManager::createNodeId()
	{
		NodeId nodeId = getNewNodeId();
		// ensure invalid id is not used
		if (nodeId == invalidNodeId)
		{
			nodeId = getNewNodeId();
		}
		nodeIdList.insert(nodeId);
		return nodeId;
	}

	NodeId NodeManager::getNewNodeId()
	{
		uint32_t nodeId;
		if (freeIndices.size() > NODE_MINIMUM_FREE_INDICES)
		{
			nodeId = freeIndices.front();
			freeIndices.pop_front();
		}
		else
		{
			generation.push_back(0);
			nodeId = generation.size() - 1;
			//CCAssert(nodeId < (1 << NODE_INDEX_BITS), "Node Index exceeded limit");
		}
		return NodeId(nodeId);
	}

	bool NodeManager::isActive(NodeId nodeId)
	{
		//CCAssert(nodeId != invalidNodeId, "Attempt to use entity with invalid id");
		return generation[nodeId.getIndex()] == nodeId.getGeneration();
	}

	void NodeManager::removeNode(NodeId nodeId)
	{
		if (nodeId.id != 0 && isActive(nodeId) == true)
		{
			const uint32_t actionIndex = nodeId.getIndex();
			++generation[actionIndex];
			freeIndices.push_back(actionIndex);

			nodeIdList.erase(nodeId);
			nodeIdMap.erase(nodeId);
		}
	}

	void NodeManager::removeAllNodes()
	{
		vector<NodeId> toDelete(nodeIdList.begin(), nodeIdList.end());
		for (auto rIt = toDelete.rbegin(); rIt != toDelete.rend(); ++rIt)
		{
			removeNode(*rIt);
		}
	}

	unordered_set<NodeId, NodeIdHasher> NodeManager::getActiveNodes()
	{
		return nodeIdList;
	}

	void NodeManager::scheduleNodeRemove(NodeId nodeId)
	{
		nodeToRemoveList.push_back(nodeId);
	}

	void NodeManager::removeNodesScheduledToRemove()
	{
		if (nodeToRemoveList.empty() == false)
		{
			vector<NodeId> nodeToRemoveListCopy(nodeToRemoveList); // for case some entity will be scheduled to remove after this entity removal (in component destructor)
			for (auto nodeId : nodeToRemoveListCopy)
			{
				removeNode(nodeId);
			}
			if (nodeToRemoveList.size() > nodeToRemoveListCopy.size())
			{
				// new remove added
				nodeToRemoveList.erase(nodeToRemoveList.begin(), nodeToRemoveList.begin() + nodeToRemoveListCopy.size());
			}
			else
			{
				nodeToRemoveList.clear();
			}
		}
	}

	void NodeManager::createGraphNode(NodeId nodeId)
	{
		nodeGraph.createGraphNode(nodeId);
	}

	void NodeManager::setParent(NodeId child, NodeId parent)
	{
		nodeGraph.setParent(child, parent);
	}

	vector<NodeId> NodeManager::getChildren(NodeId parent)
	{
		return nodeGraph.getChildren(parent);
	}

	NodeType NodeManager::getNodeTypeByString(string nodeTypeStr)
	{
		NodeType result = NodeType::None;

		static unordered_map<string, NodeType> stringToNodeTypeMap = 
		{
			{ "ActionAtomic", NodeType::ActionAtomic },
			{ "Condition", NodeType::Condition },
			{ "ActionTimed", NodeType::ActionTimed },
			{ "Failer", NodeType::Failer },
			{ "FailerWhenEvent", NodeType::FailerWhenEvent },
			{ "Runner", NodeType::Runner },
			{ "Succeeder", NodeType::Succeeder },
			{ "Wait", NodeType::Wait },

			{ "Inverter", NodeType::Inverter },
			{ "Limiter", NodeType::Limiter },
			{ "MaxTime", NodeType::MaxTime },
			{ "Repeater", NodeType::Repeater },
			{ "RepeatUntilFailure", NodeType::RepeatUntilFailure },
			{ "RepeatUntilSuccess", NodeType::RepeatUntilSuccess },

			{ "Selector", NodeType::Selector },
			{ "SelectorStateful", NodeType::SelectorStateful },
			{ "SelectorRandom", NodeType::SelectorRandom },
			{ "Sequence", NodeType::Sequence },
			{ "SequenceStateful", NodeType::SequenceStateful },
		};

		result = stringToNodeTypeMap[nodeTypeStr];

		return result;
	}

	BaseData* NodeManager::getDataByNode(NodeId nodeId)
	{
		BaseData* result = nullptr;

		auto it = nodeIdMap.find(nodeId);
		if (it != nodeIdMap.end())
		{
			result = it->second;
		}
		return result;
	}

} // namespace Bt