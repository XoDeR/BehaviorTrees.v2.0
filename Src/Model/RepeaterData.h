// Copyright (c) 2015 Volodymyr Syvochka
#pragma once
#include "BaseData.h"

namespace Bt
{
	struct RepeaterData : public BaseData
	{
		RepeaterData()
			: BaseData(NodeType::Repeater)
		{}
		NodeId innerAction;
		int32_t maxLoop = -1;
	};
} // namespace Bt