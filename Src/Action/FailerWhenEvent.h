#pragma once
#include "Action.h"
#include "ActionEventType.h"

namespace Bt
{
	class FailerWhenEvent : public Action
	{
	public:
		explicit FailerWhenEvent(EventType eventToFailWith);
		virtual ~FailerWhenEvent()
		{}
		Status process(Tick& tick) override;
	private:
		EventType eventToFailWith;
	};
} // namespace Bt
