// Copyright (c) 2015 Volodymyr Syvochka
#pragma once
#include "BaseNode.h"

namespace Bt
{
	class Composite : public BaseNode
	{
	public:
		Composite();
		explicit Composite(vector<ActionId> children);
		virtual ~Composite()
		{}
	protected:
		void setChildren(vector<ActionId> children) override;
	
		vector<ActionId> children;
	};

} // namespace Bt