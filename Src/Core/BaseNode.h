#pragma once
#include "BtCommon.h"
#include "ActionId.h"

namespace Bt
{
	struct Tick;

	class BaseNode
	{
	public:
		explicit BaseNode(Category category);
		virtual ~BaseNode()
		{}
		Status execute(Tick& tick);
		void enterInner(Tick& tick);
		void openInner(Tick& tick);
		Status processInner(Tick& tick);
		void closeInner(Tick& tick);
		void exitInner(Tick& tick);

		virtual void enter(Tick& tick)
		{}
		virtual void open(Tick& tick)
		{}
		virtual Status process(Tick& tick)
		{
			return Status::Failure;
		}
		virtual void interrupt(Tick& tick)
		{}
		virtual void close(Tick& tick)
		{}
		virtual void exit(Tick& tick)
		{}

		ActionId getActionId();
	protected:
		Category category = Category::None;
		ActionId actionId;
	};

} // namespace Bt
