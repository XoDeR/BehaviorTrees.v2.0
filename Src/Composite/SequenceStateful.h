// Copyright (c) 2015 Volodymyr Syvochka
#pragma once
#include "Composite.h"

namespace Bt
{
	// Composite

	// remembers the last state if it was running
	// Success when ALL are successful
	// Failure if ANY behavior failed
	// Running if ANY is running
	class SequenceStateful : public Composite
	{
	public:
		SequenceStateful();
		explicit SequenceStateful(vector<ActionId> children);
		virtual ~SequenceStateful()
		{}
	protected:
		void open(Tick& tick) override;
		Status process(Tick& tick) override;
		void exit(Tick& tick)  override;
	};
} // namespace Bt