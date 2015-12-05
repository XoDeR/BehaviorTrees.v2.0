#include "ActionAtomic.h"

namespace Bt
{
	ActionAtomic::ActionAtomic(std::function<void()>&& startFunc)
		: startFunc(std::move(startFunc))
	{
	}

	Status ActionAtomic::process()
	{
		startFunc();
		return Status::Success;
	}
} // namespace Bt
