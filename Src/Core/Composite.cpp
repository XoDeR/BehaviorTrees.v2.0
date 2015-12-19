// Copyright (c) 2015 Volodymyr Syvochka
#include "Composite.h"
#include "Tick.h"
#include "BehaviorTree.h"

namespace Bt
{
	Composite::Composite(vector<ActionId> children) 
		: BaseNode(Category::Composite)
		, children(children)
	{
		static const size_t maxActions = 16;
		children.reserve(maxActions);
	}

	Composite::Composite()
		: BaseNode(Category::Composite)
	{

	}

	void Composite::setChildren(vector<ActionId> children)
	{
		this->children = children;
	}

} // namespace Bt