#include "Composite.h"

namespace Bt
{
	Composite::Composite(vector<ActionId> children) 
		: BaseNode(Category::Composite)
		, children(children)
	{
		static const size_t maxActions = 16;
		children.reserve(maxActions);
	}

} // namespace Bt