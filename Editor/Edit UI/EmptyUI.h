#ifndef _emptyUI
#define _emptyUI
#include "GroupUI.h"
class EmptyUI : public GroupUI
{
public:
	EmptyUI() {
		this->selectedIndicator = this->emptyIndicator;
	}
	EmptyUI(const EmptyUI&) = delete;
	EmptyUI operator=(const EmptyUI&) = delete;
	~EmptyUI() = default;

	void UpdateUI(float , const Vect&) override {} //empty

	void DrawUI() override {} //empty
};

#endif _emptyUI
#pragma once
