/*
  ==============================================================================

    LineSettingsState.cpp
    Created: 8 Dec 2017 4:30:44pm
    Author:  uncerso

  ==============================================================================
*/

#include "LineSettingsState.h"

//==============================================================================
LineSettingsState::LineSettingsState(bool exist, LineComponent *ptr, int lineThickness, int type, Colour colour, Point<int> const &globalPosPoint1, Point<int> const &globalPosPoint2, unsigned int dashedValue1, unsigned int dashedValue2)
	: exist(exist)
	, ptr(ptr)
	, lineThickness(lineThickness)
	, type(type)
	, colour(colour)
	, globalPosPoint1(globalPosPoint1)
	, globalPosPoint2(globalPosPoint2)
	, dashedValue1(dashedValue1)
	, dashedValue2(dashedValue2)
{}

bool LineSettingsState::operator!=(LineSettingsState const &other) const noexcept {
	return globalPosPoint1 != other.globalPosPoint1 ||
	       globalPosPoint2 != other.globalPosPoint2 ||
	       exist != other.exist ||
	       ptr != other.ptr ||
	       lineThickness != other.lineThickness ||
	       type != other.type ||
	       colour != other.colour ||
	       dashedValue1 != other.dashedValue1 ||
	       dashedValue2 != other.dashedValue2;
}

bool LineSettingsState::isExist()  const noexcept {
	return exist;
}

LineComponent* LineSettingsState::getPtr() const noexcept {
	return ptr;
}

int LineSettingsState::getLineThickness() const noexcept {
	return lineThickness;
}

int LineSettingsState::getType() const noexcept {
	return type;
}

Colour LineSettingsState::getColour() const noexcept {
	return colour;
}

Point<int> LineSettingsState::getGlobalPosPoint1() const noexcept {
	return globalPosPoint1;
}

Point<int> LineSettingsState::getGlobalPosPoint2() const noexcept {
	return globalPosPoint2;
}

unsigned int LineSettingsState::getDashedValue1() const noexcept {
	return dashedValue1;
}

unsigned int LineSettingsState::getDashedValue2() const noexcept {
	return dashedValue2;
}
