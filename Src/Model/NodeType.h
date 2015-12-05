// Copyright (c) 2015 Volodymyr Syvochka
#pragma once

namespace Bt
{
	enum class NodeType
	{
		None,

		ActionAtomic,
		Condition,
		ActionTimed,
		Failer,
		FailerWhenEvent,
		Runner,
		Succeeder,
		Wait,

		Inverter,
		Limiter,
		MaxTime,
		Repeater,
		RepeatUntilFailure,
		RepeatUntilSuccess,

		Selector,
		SelectorStateful,
		SelectorRandom,
		Sequence,
		SequenceStateful,
	};

} // namespace Bt