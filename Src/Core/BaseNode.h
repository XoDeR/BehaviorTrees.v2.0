// Copyright (c) 2015 Volodymyr Syvochka
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
		ActionId getActionId();
		void interruptNode(Tick& tick);
	private:
		void enterInner(Tick& tick);
		void openInner(Tick& tick);
		Status processInner(Tick& tick);
		void interruptInner(Tick& tick);
		void closeInner(Tick& tick);
		void exitInner(Tick& tick);
	protected:
		// used by decorator subclass
		virtual void setChild(ActionId child)
		{}
		// used by composite subclass
		virtual void setChildren(vector<ActionId> children)
		{}
		virtual void enter(Tick& tick)
		{}
		virtual void open(Tick& tick)
		{}
		// should be overridden by any descendant
		virtual Status process(Tick& tick) = 0;
		// should be overridden just for timed leaf nodes
		// interrupt function == close when action is not finished
		// timed actions and actions with children -- decorators and composites that can contain timed actions
		// should override interrupt function
		// atomic actions and conditions use this default implementation
		// from close function timed action inner interrupt function should be called
		virtual void interrupt(Tick& tick)
		{}
		// timed actions and actions with children -- decorators and composites that can contain timed actions
		// should override interrupt function
		virtual void close(Tick& tick)
		{}
		// if action has some inner state it should override exit function
		// restore inner state (if any) to initial there
		virtual void exit(Tick& tick)
		{}
		Category category = Category::None;
		ActionId actionId;
	};

} // namespace Bt
