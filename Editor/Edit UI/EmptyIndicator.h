#ifndef _emptyindicator
#define _emptyindicator
#include "WorldUI.h"

class EmptyIndicator : public WorldUI
{
public:
	EmptyIndicator() = default;
	EmptyIndicator(const EmptyIndicator&) = delete;
	EmptyIndicator operator=(const EmptyIndicator&) = delete;
	~EmptyIndicator() = default;

	void Display(float, const Vect&) override {} //empty

};

#endif _emptyindicator
#pragma once
