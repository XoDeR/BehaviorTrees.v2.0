#pragma once
#include "Action.h"

namespace Bt
{

	class Failer : public Action
	{
		virtual ~Failer()
		{}

		Status process(Tick& tick) override
		{
			return Status::Failure;
		}
	};

} // namespace Bt
