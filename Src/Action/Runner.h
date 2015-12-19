// Copyright (c) 2015 Volodymyr Syvochka
#pragma once
#include "Action.h"

namespace Bt
{
	// timed
	class Runner : public Action
	{
	public:
		virtual ~Runner()
		{}
	protected:
		Status process(Tick& tick) override
		{
			return Status::Running;
		}
	};

} // namespace Bt