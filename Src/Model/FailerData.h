// Copyright (c) 2015 Volodymyr Syvochka
#pragma once
#include "BaseData.h"

namespace Bt
{
	struct FailerData : public BaseData
	{
		FailerData()
			: BaseData(NodeType::Failer)
		{}
	};
} // namespace Bt