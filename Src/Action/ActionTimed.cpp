#include "ActionTimed.h"

namespace Bt
{
	ActionTimed::ActionTimed(std::function<void()>&& startFunc, std::function<void()>&& interruptFunc)
		: startFunc(std::move(startFunc))
		, interruptFunc(std::move(interruptFunc))
	{

	}

	Status ActionTimed::process()
	{
		Status result = Status::Failure;

		// not started
		if (isStarted == false && isFinished == false)
		{
			// start
			startFunc(); // invoke external function
			isStarted = true;
		}
		// started but not finished == Running
		else if (isStarted == true && isFinished == false)
		{
			result = Status::Running;
		}
		// started and finished successfully
		else if (isStarted == true && isFinished == true)
		{
			result = Status::Success;
			reset();
		}

		return result;
	}

	void ActionTimed::onFinished()
	{
		// this function is invoked
		isFinished = true;
	}

	void ActionTimed::reset()
	{
		isStarted = false;
		isFinished = false;
	}

	void ActionTimed::interrupt()
	{
		// if isRunning
		if (isStarted == true && isFinished == false)
		{
			interruptFunc();
			reset();
		}
	}

} // namespace Bt