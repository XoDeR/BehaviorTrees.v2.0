// Copyright (c) 2015 Volodymyr Syvochka
#pragma once
#include "BaseData.h"

namespace Bt
{
	struct MaxTimeData : public BaseData
	{
		MaxTimeData()
			: BaseData(NodeType::MaxTime)
		{}
		float maxDelay;
	};
} // namespace Bt