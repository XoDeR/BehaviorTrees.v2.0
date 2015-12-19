#pragma once
#include "Action.h"

namespace Bt
{

	class Failer : public Action
	{
	public:
		virtual ~Failer()
		{}

		Status process(Tick& tick) override
		{
			return Status::Failure;
		}
	};

} // namespace Bt
