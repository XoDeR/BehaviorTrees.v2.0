// Copyright (c) 2015 Volodymyr Syvochka
#pragma once
#include "BaseNode.h"

namespace Bt
{
	class Action : public BaseNode
	{
	public:
		Action()
			: BaseNode(Category::Action)
		{

		}
		virtual ~Action()
		{}
	};

} // namespace Bt
