/*
  ==============================================================================

    LineSettingsState.h
    Created: 8 Dec 2017 4:30:44pm
    Author:  uncerso

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
namespace line_paint{
class LineSettings;
class LineComponent;

class LineSettingsState {
	friend LineSettings;
public:
	LineSettingsState(bool del = false,
	                  LineComponent *ptr = nullptr,
	                  int lineThickness = 0,
	                  int type = 0,
	                  Colour colour = Colour::fromRGB(45, 91, 129),
	                  Point<int> const &globalPosPoint1 = Point<int>(),
	                  Point<int> const &globalPosPoint2 = Point<int>(),
	                  unsigned int dashedValue1 = 8,
	                  unsigned int dashedValue2 = 8
	                  );
	~LineSettingsState() = default;

	/// Indicates whether the line is shown
	bool isExist() const noexcept;
	LineComponent*getPtr() const noexcept;
	int getLineThickness() const noexcept;
	int getType() const noexcept;
	Colour getColour() const noexcept;
	Point<int> getGlobalPosPoint1() const noexcept;
	Point<int> getGlobalPosPoint2() const noexcept;
	bool operator!=(LineSettingsState const &other) const noexcept;
	unsigned int getDashedValue1() const noexcept;
	unsigned int getDashedValue2() const noexcept;
private:
	bool exist;
	LineComponent *ptr;
	int lineThickness;
	int type;
	Colour colour;
	Point<int> globalPosPoint1;
	Point<int> globalPosPoint2;
	unsigned int dashedValue1;
	unsigned int dashedValue2;
};
}
