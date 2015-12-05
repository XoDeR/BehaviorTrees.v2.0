// Copyright (c) 2015 Volodymyr Syvochka
#pragma once
#include "BaseData.h"

namespace Bt
{
	struct WaitData : public BaseData
	{
		WaitData()
			: BaseData(NodeType::Wait)
		{}
		float delay = 0.0f;
	};
} // namespace Bt