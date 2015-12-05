// Copyright (c) 2015 Volodymyr Syvochka
#pragma once
#include "BaseData.h"

namespace Bt
{
	struct ConditionData : public BaseData
	{
		ConditionData()
			: BaseData(NodeType::Condition)
		{}
		string startFunc;
	};
} // namespace Bt

