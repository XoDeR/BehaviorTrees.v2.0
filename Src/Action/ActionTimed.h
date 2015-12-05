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
		ActionTimed(std::function<void()>&& startFunc, std::function<void()>&& interruptFunc);
		virtual ~ActionTimed()
		{}
		Status process();
		void interrupt();
		void onFinished();
		void reset();
		std::function<void()> startFunc;
		std::function<void()> interruptFunc;
		std::function<void()> onFinishedCallbackFunc;
		std::function<void()>* getOnFinishedCallback();
		bool isStarted = false;
		bool isFinished = false;
	};

} // namespace Bt