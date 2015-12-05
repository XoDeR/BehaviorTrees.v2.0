#pragma once
#include "Action.h"

namespace Bt
{

	class Succeeder : public Action
	{
		virtual ~Succeeder()
		{}

		Status process(Tick& tick)
		{
			return Status::Success;
		}
	};

} // namespace Bt
