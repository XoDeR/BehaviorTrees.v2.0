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
	};
} // namespace Bt