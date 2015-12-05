// Copyright (c) 2015 Volodymyr Syvochka
#pragma once
#include "BaseData.h"

namespace Bt
{
	struct RunnerData : public BaseData
	{
		RunnerData()
			: BaseData(NodeType::Runner)
		{}
	};
} // namespace Bt