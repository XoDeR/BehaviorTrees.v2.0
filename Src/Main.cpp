#include "BehaviorTree.h"
#include "ActionManager.h"
#include "NodeManager.h"
#include "AiBehaviorModel.h"

#include <iostream>

void main()
{
	using namespace Bt;
	ActionManager actionManager;
	BehaviorTree behaviorTree(actionManager);

	AiBehaviorModel::getInstance().parseAiBehaviorForUnit(UnitType::EnemyNecromancer);
	// output data
	AiBehaviorData& aiBehaviorData = AiBehaviorModel::getInstance().unitTypeAiDataMap[UnitType::EnemyNecromancer];
	BaseData* root = aiBehaviorData.root;

	using namespace std;
	cout << "root = " << root->name << "\n"; 

	vector<NodeId> children = aiBehaviorData.nodeManager.getChildren(root->id);
	for (NodeId child : children)
	{
		BaseData* childData = aiBehaviorData.nodeManager.getDataByNode(child);
		cout << "child = " << childData->name << "\n";
	}

	int aa = 0;
	cin >> aa;
}