// Copyright (c) 2015 Volodymyr Syvochka
#include "Tick.h"
#include "BehaviorTree.h"
#include "BaseNode.h"

namespace Bt
{
	Tick::Tick(BehaviorTree& tree, float dt)
		: tree(tree)
		, dt(dt)
	{

	}

	void Tick::enterNode(BaseNode& node)
	{
		nodeCount += 1;

		ActionId actionId = node.getActionId();
		openNodeList.insert(actionId);
	}

	void Tick::openNode(BaseNode& node)
	{

	}

	void Tick::processNode(BaseNode& node)
	{

	}

	void Tick::closeNode(BaseNode& node)
	{
		ActionId actionId = node.getActionId();
		openNodeList.erase(actionId);
	}

	void Tick::exitNode(BaseNode& node)
	{

	}

} // namespace Bt
