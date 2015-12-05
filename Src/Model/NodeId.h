// Copyright (c) 2015 Volodymyr Syvochka
#pragma once
#include "BtCommon.h"

namespace Bt
{
	const uint32_t NODE_INDEX_BITS = 24;
	const uint32_t NODE_INDEX_MASK = (1 << NODE_INDEX_BITS) - 1;

	const uint32_t NODE_GENERATION_BITS = 8;
	const uint32_t NODE_GENERATION_MASK = (1 << NODE_GENERATION_BITS) - 1;

	struct NodeId
	{
		// default constructor creates an action with invalid id
		// use constructor with parameter to create action
		// valid action is created in ActionManager
		NodeId()
			: id(0)
		{
		}

		explicit NodeId(uint32_t id)
			: id(id)
		{
		}

		friend bool operator<(const NodeId& first, const NodeId& second)
		{
			return first.id < second.id;
		}

		friend bool operator==(const NodeId& first, const NodeId& second)
		{
			return first.id == second.id;
		}

		uint32_t getIndex() const
		{
			return id & NODE_INDEX_MASK;
		}

		uint32_t getGeneration() const
		{
			return (id >> NODE_INDEX_BITS) & NODE_GENERATION_MASK;
		}
		uint32_t id;
	};

} // namespace Bt

struct NodeIdHasher
{
	std::size_t operator()(const Bt::NodeId& k) const
	{
		using std::size_t;
		using std::hash;
		return ((hash<unsigned int>()(k.id)));
	}
};


