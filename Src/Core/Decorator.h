#pragma once
#include "BaseNode.h"

namespace Bt
{
	class Decorator : public BaseNode
	{
	public:
		Decorator(ActionId child)
			: BaseNode(Category::Decorator)
			, child(child)
		{}
	protected:
		ActionId child;
	};
} // namespace Bt

