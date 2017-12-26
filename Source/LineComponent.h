/*
  ==============================================================================

    LineComponent.h
    Created: 29 Oct 2017 12:42:43am
    Author:  uncerso

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
namespace line_paint{

class LineSettings;

/// Lines themselves
class LineComponent
	: public Component
{
	friend LineSettings;
public:
	enum LineType {
		solid = 0,
		dashed = 1,
		rounded = 2,
		boundBox = 4
	};

	LineComponent(int startX, int startY, int endX, int endY, int lineThickness = 3, Colour colour = Colour::fromRGB(0, 0, 0), int lineType = LineType::solid | LineType::rounded, unsigned int dashedValue1 = 8, unsigned int dashedValue2 = 8);
	LineComponent(int x, int y, int lineThickness = 3, Colour colour = Colour::fromRGB(0, 0, 0), int lineType = LineType::solid | LineType::rounded, unsigned int dashedValue1 = 8, unsigned int dashedValue2 = 8);
	~LineComponent();
private:
	void paint(Graphics &canvas) override;

	void mouseDown(const MouseEvent &event) override;
	void mouseUp(const MouseEvent &event) override;
	bool hitTest(int x, int y) override;
public:
	void mouseDrag(const MouseEvent &event) override;

	/// Selects a line
	static void select(LineComponent *object);
	/// Unselects a line
	static void selectNullptrIfSelected(LineComponent *object);

	/// Sets line thickness
	void setLineThickness(int lineThickness);
	int getLineThickness() const noexcept;

	/// Sets line colour
	void setColour(Colour colour);
	Colour getColour() const noexcept;

	/// Sets line type (according to LineType enum)
	void setLineType(int type);
	int getLineType() const noexcept;

	/// Set dashes' lenght
	void setDashedValue1(unsigned int value);
	unsigned int getDashedValue1() const noexcept;

	/// Set dashes' gap size
	void setDashedValue2(unsigned int value);
	unsigned int getDashedValue2() const noexcept;

	/// Set line's ends coodrinates
	void setPos(Point<int> const &p1, Point<int> const &p2);
	Point<int> getPoint1() const noexcept;
	Point<int> getPoint2() const noexcept;

	/// Select setting object to manage all lines
	static void selectLineSettings(LineSettings *lineSettings);
	static void deleteCurrentLine();

private:
	void unselect();

	bool dragMode;
	int lineThickness;
	int type;
	unsigned int dashedValue1;
	unsigned int dashedValue2;
	Colour colour;
	Point<int> deltaBounds;
	Point<int> globalFixedPoint;
	Point<int> globalMovedPoint;
	Point<int> point1;
	Point<int> point2;
	static ComponentDragger dragger;
	static ComponentBoundsConstrainer constrainer;
	static LineComponent *selected;
	static LineSettings *lineSettings;
};
}