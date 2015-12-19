// Copyright (c) 2015 Volodymyr Syvochka
#pragma once
#include "BaseNode.h"

namespace Bt
{
	class Decorator : public BaseNode
	{
	public:
		// default constructor used for 2 steps construction only
		Decorator()
			: BaseNode(Category::Decorator)
		{}
		explicit Decorator(ActionId child)
			: BaseNode(Category::Decorator)
			, child(child)
		{}
		virtual ~Decorator()
		{}
	protected:
		virtual void setChild(ActionId child) override 
		{
			this->child = child;
		}
	
		ActionId child;
	};
} // namespace Bt

