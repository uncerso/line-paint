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

class LineComponent
	: public Component
{
	friend LineSettings;
public:
	LineComponent(int startX, int startY, int endX, int endY, int lineThickness = 3, Colour colour = Colour::fromRGB(0, 0, 0), int lineType = LineType::solid | LineType::rounded);
	LineComponent(int x, int y, int lineThickness = 3, Colour colour = Colour::fromRGB(0, 0, 0), int lineType = LineType::solid | LineType::rounded);
	~LineComponent();

	void paint(Graphics &canvas) override;

	void mouseMove(const MouseEvent &events) override {
		repaint();
	}

	void mouseDown(const MouseEvent &event) override;
	void mouseUp(const MouseEvent &event) override;
	void mouseDrag(const MouseEvent &event) override;
	bool hitTest(int x, int y) override;

	static void select(LineComponent *object);
	static void selectNullptrIfSelected(LineComponent *object);

	void setLineThickness(int lineThickness);
	int getLineThickness();

	void setColour(Colour colour);
	Colour getColour();

	void setLineType(int type);
	int getLineType();

	void setPos(Point<int> const &p1, Point<int> const &p2);
	Point<int> getPoint1();
	Point<int> getPoint2();

	enum LineType {
		solid = 0,
		dashed = 1,
		rounded = 2,
		boundBox = 4
	};

	static void selectLineSettings(LineSettings *lineSettings);

private:
	void unselect();

	bool dragMode;
	int lineThickness;
	int type;
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
