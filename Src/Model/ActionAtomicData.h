// Copyright (c) 2015 Volodymyr Syvochka
#pragma once
#include "BaseData.h"

namespace Bt
{
	struct ActionAtomicData : public BaseData
	{
		ActionAtomicData()
			: BaseData(NodeType::ActionAtomic)
		{}
		string startFunc;
	};
} // namespace Bt