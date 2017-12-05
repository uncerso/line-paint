/*
  ==============================================================================

    LineComponent.h
    Created: 29 Oct 2017 12:42:43am
    Author:  uncerso

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class LineSettings;

/// Lines themselves
class LineComponent
	: public Component
{
	friend LineSettings;
public:
	LineComponent(int startX, int startY, int endX, int endY, int lineThickness = 3, Colour colour = Colour::fromRGB(0, 0, 0), int lineType = LineType::solid | LineType::rounded, unsigned int dashedValue1 = 8, unsigned int dashedValue2 = 8);
	LineComponent(int x, int y, int lineThickness = 3, Colour colour = Colour::fromRGB(0, 0, 0), int lineType = LineType::solid | LineType::rounded, unsigned int dashedValue1 = 8, unsigned int dashedValue2 = 8);
	~LineComponent();

	void paint(Graphics &canvas) override;


	void mouseDown(const MouseEvent &event) override;
	void mouseUp(const MouseEvent &event) override;
	void mouseDrag(const MouseEvent &event) override;
	bool hitTest(int x, int y) override;

	/// Selects a line
	static void select(LineComponent *object);
	/// Unselects a line
	static void selectNullptrIfSelected(LineComponent *object);

	/// Sets line thickness
	void setLineThickness(int lineThickness);
	int getLineThickness();

	/// Sets line colour
	void setColour(Colour colour);
	Colour getColour();

	/// Sets line type (according to LineType enum)
	void setLineType(int type);
	int getLineType();

	/// Set dashes' lenght
	void setDashedValue1(unsigned int value);
	unsigned int getDashedValue1();

	/// Set dashes' gap size
	void setDashedValue2(unsigned int value);
	unsigned int getDashedValue2();

	/// Set line's ends coodrinates
	void setPos(Point<int> const &p1, Point<int> const &p2);
	Point<int> getPoint1();
	Point<int> getPoint2();

	enum LineType {
		solid = 0,
		dashed = 1,
		rounded = 2,
		boundBox = 4
	};

	/// Select setting object to manage all lines
	static void selectLineSettings(LineSettings *lineSettings);

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
