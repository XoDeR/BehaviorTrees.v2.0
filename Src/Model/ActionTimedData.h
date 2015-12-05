// Copyright (c) 2015 Volodymyr Syvochka
#pragma once
#include "BaseData.h"

namespace Bt
{
	struct ActionTimedData : public BaseData
	{
		ActionTimedData()
			: BaseData(NodeType::ActionTimed)
		{}
		string startFunc;
	};
} // namespace Bt
