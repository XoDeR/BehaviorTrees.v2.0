// Copyright (c) 2015 Volodymyr Syvochka
#pragma once
#include "BaseData.h"

namespace Bt
{
	struct SelectorStatefulData : public BaseData
	{
		SelectorStatefulData()
			: BaseData(NodeType::SelectorStateful)
		{}
		vector<NodeId> actionList;
	};
} // namespace Bt