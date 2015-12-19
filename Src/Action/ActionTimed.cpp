// Copyright (c) 2015 Volodymyr Syvochka
#include "ActionTimed.h"
#include "Tick.h"
#include "BehaviorTree.h"

namespace Bt
{
	ActionTimed::ActionTimed(std::function<void()>&& startFunc, std::function<void()>&& interruptFunc)
		: startFunc(std::move(startFunc))
		, interruptFunc(std::move(interruptFunc))
	{

	}

	ActionTimed::ActionTimed()
	{
	}

	void ActionTimed::onFinished()
	{
		// this function is invoked
		isFinished = true;
	}

	void ActionTimed::setStartFunction(std::function<void()>&& startFunc)
	{
		this->startFunc = std::move(startFunc);
	}

	void ActionTimed::setInterruptFunction(std::function<void()>&& interruptFunc)
	{
		this->interruptFunc = std::move(interruptFunc);
	}

	std::function<void()>* ActionTimed::getOnFinishedCallback()
	{
		return &onFinishedCallbackFunc;
	}

	void ActionTimed::open(Tick& tick)
	{
		isFinished = false;
		// start
		startFunc(); // invoke external function
	}

	Status ActionTimed::process(Tick& tick)
	{
		Status result = Status::Running;
		if (isFinished == true)
		{
			result = Status::Success;
		}
		return result;
	}

	void ActionTimed::interrupt(Tick& tick)
	{
		interruptFunc(); // invoke external function
	}

	void ActionTimed::exit(Tick& tick)
	{
		isFinished = false;
	}

} // namespace Bt