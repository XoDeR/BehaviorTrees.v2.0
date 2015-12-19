// Copyright (c) 2015 Volodymyr Syvochka
#pragma once
#include "BtCommon.h"
#include "Action.h"

namespace Bt
{
	// timed action:
	// 1. can be started
	// 2. reports when it is finished via callback
	// 3. can be interrupted anytime on demand (stopped without finishing)
	class ActionTimed : public Action
	{
	public:
		ActionTimed();
		ActionTimed(std::function<void()>&& startFunc, std::function<void()>&& interruptFunc);
		virtual ~ActionTimed()
		{}
		void setStartFunction(std::function<void()>&& startFunc);
		void setInterruptFunction(std::function<void()>&& interruptFunc);
		void onFinished();
		
		std::function<void()> startFunc;
		std::function<void()> interruptFunc;
		std::function<void()> onFinishedCallbackFunc;
		std::function<void()>* getOnFinishedCallback();
		bool isFinished = false;
	protected:
		void open(Tick& tick) override;
		Status process(Tick& tick) override;
		void interrupt(Tick& tick) override;
		void exit(Tick& tick) override;
	};

} // namespace Bt