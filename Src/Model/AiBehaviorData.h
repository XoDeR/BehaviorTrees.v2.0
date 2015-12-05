// Copyright (c) 2015 Volodymyr Syvochka
#pragma once
#include "BtCommon.h"
#include "NodeManager.h"
#include "BaseData.h"

namespace Bt
{
	struct AiBehaviorData
	{
		NodeManager nodeManager;
		BaseData* root = nullptr;
	};
} // namespace Bt