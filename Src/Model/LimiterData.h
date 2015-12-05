// Copyright (c) 2015 Volodymyr Syvochka
#pragma once
#include "BaseData.h"

namespace Bt
{
	struct LimiterData : public BaseData
	{
		LimiterData()
			: BaseData(NodeType::Limiter)
		{}
	};
} // namespace Bt