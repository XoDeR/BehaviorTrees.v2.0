// Copyright (c) 2015 Volodymyr Syvochka
#pragma once
#include "BaseData.h"

namespace Bt
{
	struct SelectorRandomData : public BaseData
	{
		SelectorRandomData()
			: BaseData(NodeType::SelectorRandom)
		{}
		vector<NodeId> actionList;
	};
} // namespace Bt