// Copyright (c) 2015 Volodymyr Syvochka
#pragma once

#include "BtCommon.h"
#include "ActionId.h"

namespace Bt
{
	class BehaviorTree;
	class BaseNode;

	// Tick object is passed as parameter to the nodes during the traversal
	// Is used to access and modify tree's memory
	// Also is used to store the open node after the tick signal to let keep track and close the node when needed
	struct Tick
	{
		Tick(BehaviorTree& tree, float dt);
		void enterNode(BaseNode& node);
		void openNode(BaseNode& node);
		void processNode(BaseNode& node);
		void closeNode(BaseNode& node);
		void exitNode(BaseNode& node);
		BehaviorTree& tree;
		unordered_set<ActionId, ActionIdHasher> openNodeList;
		float dt = 0.0f;
		size_t nodeCount = 0;
	};

} // namespace Bt