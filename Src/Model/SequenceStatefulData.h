// Copyright (c) 2015 Volodymyr Syvochka
#pragma once
#include "BaseData.h"

namespace Bt
{
	struct SequenceStatefulData : public BaseData
	{
		SequenceStatefulData()
			: BaseData(NodeType::SelectorStateful)
		{}
		vector<NodeId> actionList;
	};
} // namespace Bt

