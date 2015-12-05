#pragma once
#include "Action.h"

namespace Bt
{

	class Runner : public Action
	{
		virtual ~Runner()
		{}

		Status process(Tick& tick)
		{
			return Status::Running;
		}
	};

} // namespace Bt