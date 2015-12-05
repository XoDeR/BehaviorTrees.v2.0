#include "Condition.h"

namespace Bt
{
	Condition::Condition(std::function<bool()>&& startFunc)
		: BaseNode(Category::Condition)
		, startFunc(std::move(startFunc))
	{

	}

	Status Condition::process()
	{
		Status result = Status::Failure;
		bool cond = startFunc();
		if (cond == true)
		{
			result = Status::Success;
		}
		return result;
	}

} // namespace Bt