// Copyright (c) 2015 Volodymyr Syvochka
#pragma once
#include "BaseData.h"

namespace Bt
{
	struct RepeatUntilSuccessData : public BaseData
	{
		RepeatUntilSuccessData()
			: BaseData(NodeType::RepeatUntilSuccess)
		{}
		NodeId innerAction;
		int32_t maxLoop = -1;
	};
} // namespace Bt