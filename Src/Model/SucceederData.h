// Copyright (c) 2015 Volodymyr Syvochka
#pragma once
#include "BaseData.h"

namespace Bt
{
	struct SucceederData : public BaseData
	{
		SucceederData()
			: BaseData(NodeType::Succeeder)
		{}
	};
} // namespace Bt