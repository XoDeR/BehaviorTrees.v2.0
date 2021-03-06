// Copyright (c) 2015 Volodymyr Syvochka
#pragma once
#include "Action.h"

namespace Bt
{
	// timed
	class Wait : public Action
	{
	public:
		explicit Wait(float delay);
		virtual ~Wait()
		{}
		void open(Tick& tick);
		Status process(Tick& tick);
	private:
		float endTime = 0.0f;
	};

} // namespace Bt
