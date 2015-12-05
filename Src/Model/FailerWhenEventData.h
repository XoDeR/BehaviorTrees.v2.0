// Copyright (c) 2015 Volodymyr Syvochka
#pragma once
#include "BaseData.h"

namespace Bt
{
	struct FailerWhenEventData : public BaseData
	{
		FailerWhenEventData()
			: BaseData(NodeType::FailerWhenEvent)
		{}
		string eventStr;
	};
} // namespace Bt