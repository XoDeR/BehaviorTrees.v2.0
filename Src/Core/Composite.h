#pragma once
#include "BaseNode.h"

namespace Bt
{
	class Composite : public BaseNode
	{
	public:
		explicit Composite(vector<ActionId> children);
	protected:
		vector<ActionId> children;
	};

} // namespace Bt