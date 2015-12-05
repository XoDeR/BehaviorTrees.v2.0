// Copyright (c) 2015 Volodymyr Syvochka
#pragma once
#include "BtCommon.h"

namespace Bt
{
	const uint32_t ACTION_INDEX_BITS = 24;
	const uint32_t ACTION_INDEX_MASK = (1 << ACTION_INDEX_BITS) - 1;

	const uint32_t ACTION_GENERATION_BITS = 8;
	const uint32_t ACTION_GENERATION_MASK = (1 << ACTION_GENERATION_BITS) - 1;

	struct ActionId
	{
		// default constructor creates an action with invalid id
		// use constructor with parameter to create action
		// valid action is created in ActionManager
		ActionId()
			: id(0)
		{
		}

		explicit ActionId(uint32_t id)
			: id(id)
		{
		}

		friend bool operator<(const ActionId& first, const ActionId& second)
		{
			return first.id < second.id;
		}

		friend bool operator==(const ActionId& first, const ActionId& second)
		{
			return first.id == second.id;
		}

		uint32_t getIndex() const
		{
			return id & ACTION_INDEX_MASK;
		}

		uint32_t getGeneration() const
		{
			return (id >> ACTION_INDEX_BITS) & ACTION_GENERATION_MASK;
		}
		uint32_t id;
	};

} // namespace Bt

struct ActionIdHasher
{
	std::size_t operator()(const Bt::ActionId& k) const
	{
		using std::size_t;
		using std::hash;
		return ((hash<unsigned int>()(k.id)));
	}
};


