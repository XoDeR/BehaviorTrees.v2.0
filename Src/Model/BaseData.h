// Copyright (c) 2015 Volodymyr Syvochka
#pragma once
#include "BtCommon.h"
#include "NodeId.h"
#include "NodeType.h"

namespace Bt
{
	struct BaseData
	{
		BaseData()
			: nodeType(NodeType::None)
		{}
		BaseData(NodeType nodeType)
			: nodeType(nodeType)
		{}
		NodeType nodeType;
		NodeId id;
		string name;
	};
} // namespace Bt