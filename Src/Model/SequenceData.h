// Copyright (c) 2015 Volodymyr Syvochka
#pragma once
#include "BaseData.h"

namespace Bt
{
	struct SequenceData : public BaseData
	{
		SequenceData()
			: BaseData(NodeType::Sequence)
		{}
		vector<NodeId> actionList;
	};
} // namespace Bt