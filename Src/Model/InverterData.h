// Copyright (c) 2015 Volodymyr Syvochka
#pragma once
#include "BaseData.h"

namespace Bt
{
	struct InverterData : public BaseData
	{
		InverterData()
			: BaseData(NodeType::Inverter)
		{}
	};
} // namespace Bt