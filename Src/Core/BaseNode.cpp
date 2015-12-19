// Copyright (c) 2015 Volodymyr Syvochka
#include "BaseNode.h"
#include "Tick.h"
#include "BehaviorTree.h"

namespace Bt
{
	// public, interface
	BaseNode::BaseNode(Category category) 
		: category(category)
	{
	}

	Status BaseNode::execute(Tick& tick)
	{
		enterInner(tick);

		if (tick.tree.getIsOpen(actionId) == false)
		{
			openInner(tick);

			Status status = processInner(tick);

			if (status != Status::Running)
			{
				// action finished
				closeInner(tick);
				exitInner(tick);
				return status;
			}
		}
	}

	void BaseNode::interruptNode(Tick& tick)
	{
		interruptInner(tick);
		exitInner(tick);
	}

	ActionId BaseNode::getActionId()
	{
		return actionId;
	}

	// private final
	void BaseNode::enterInner(Tick& tick)
	{
		tick.enterNode(*this);
		this->enter(tick);
	}

	void BaseNode::openInner(Tick& tick)
	{
		tick.openNode(*this);
		tick.tree.setIsOpen(actionId, true);
		this->open(tick);
	}

	Status BaseNode::processInner(Tick& tick)
	{
		tick.processNode(*this);
		return this->process(tick);
	}

	void BaseNode::interruptInner(Tick& tick)
	{
		// virtual function call
		tick.closeNode(*this);
		tick.tree.setIsOpen(actionId, false);
		this->interrupt(tick);
	}

	void BaseNode::closeInner(Tick& tick)
	{
		tick.closeNode(*this);
		tick.tree.setIsOpen(actionId, false);
		this->close(tick);
	}

	void BaseNode::exitInner(Tick& tick)
	{
		tick.exitNode(*this);
		this->exit(tick);
	}
} // namespace Bt