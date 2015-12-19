// Copyright (c) 2015 Volodymyr Syvochka
#pragma once
#include "BaseData.h"

namespace Bt
{
	struct RepeatUntilFailureData : public BaseData
	{
		RepeatUntilFailureData()
			: BaseData(NodeType::RepeatUntilFailure)
		{}
		NodeId innerAction;
		int32_t maxLoop = -1;
	};
} // namespace Bt