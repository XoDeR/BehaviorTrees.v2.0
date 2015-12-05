// Copyright (c) 2015 Volodymyr Syvochka
#pragma once
#include "BaseData.h"

namespace Bt
{
	struct SelectorData : public BaseData
	{
		SelectorData()
			: BaseData(NodeType::Selector)
		{}
		vector<NodeId> actionList;
	};
} // namespace Bt