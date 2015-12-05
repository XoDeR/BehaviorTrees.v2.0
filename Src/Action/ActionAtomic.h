// Copyright (c) 2015 Volodymyr Syvochka
#pragma once
#include "BtCommon.h"
#include "Action.h"

namespace Bt
{
	class ActionAtomic : public Action
	{
	public:
		explicit ActionAtomic(std::function<void()>&& startFunc);
		virtual ~ActionAtomic()
		{}
		Status process();
		std::function<void()> startFunc;
	};

} // namespace Bt