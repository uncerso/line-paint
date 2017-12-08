/*
  ==============================================================================

    LineComponent.cpp
    Created: 29 Oct 2017 12:42:43am
    Author:  uncerso

  ==============================================================================
*/

#include "LineComponent.h"
#include "LineSettings.h"

ComponentDragger LineComponent::dragger;
ComponentBoundsConstrainer LineComponent::constrainer;
LineComponent*LineComponent::selected = nullptr;
LineSettings*LineComponent::lineSettings = nullptr;

void LineComponent::selectLineSettings(LineSettings *lineSettings) {
	LineComponent::lineSettings = lineSettings;
	if (lineSettings) lineSettings->update();
}

void LineComponent::selectNullptrIfSelected(LineComponent *object) {
	if (selected == object)
		select(nullptr);
}

LineComponent::~LineComponent() {
	if (selected == this) {
		selected = nullptr;
		if (lineSettings)
			lineSettings->update();
	}
}

void LineComponent::unselect() {
	selected = nullptr;
	repaint();
}

void LineComponent::select(LineComponent *object) {
	if (selected) selected->unselect();
	selected = object;
	if (lineSettings) lineSettings->update();
}

void LineComponent::deleteCurrentLine() {
	if (lineSettings) {
		lineSettings->deleteCurrentLine();
		return;
	}
	if (selected)
		delete selected;
}

LineComponent::LineComponent(int startX, int startY, int endX, int endY, int lineThickness, Colour colour, int lineType, unsigned int dashedValue1, unsigned int dashedValue2)
	: Component("Line")
	, dragMode(false)
	, lineThickness(lineThickness)
	, type(lineType)
	, dashedValue1(dashedValue1)
	, dashedValue2(dashedValue2)
	, colour(colour)
	, deltaBounds((lineThickness + 1) >> 1, (lineThickness + 1) >> 1 )
{
	setWantsKeyboardFocus(false);
	setBufferedToImage(true);
	int minX = std::min(startX, endX);
	int minY = std::min(startY, endY);
	point1 = Point<int>(startX - minX, startY - minY) + deltaBounds;
	point2 = Point<int>(endX - minX, endY - minY) + deltaBounds;
	setBounds(minX - deltaBounds.getX(), minY - deltaBounds.getY(), std::abs(endX - startX) + deltaBounds.getX() * 2, std::abs(endY - startY) + deltaBounds.getY() * 2);
}

LineComponent::LineComponent(int x, int y, int lineThickness, Colour colour, int lineType, unsigned int dashedValue1, unsigned int dashedValue2)
	: Component("Line")
	, dragMode(false)
	, lineThickness(lineThickness)
	, type(lineType)
	, dashedValue1(dashedValue1)
	, dashedValue2(dashedValue2)
	, colour(colour)
	, deltaBounds((lineThickness + 1) >> 1, (lineThickness + 1) >> 1 )
{
	setWantsKeyboardFocus(false);
	setBufferedToImage(true);
	point1 = deltaBounds;
	point2 = deltaBounds;
	setBounds(x - deltaBounds.getX(), y - deltaBounds.getY(), deltaBounds.getX() * 2, deltaBounds.getY() * 2);
	globalFixedPoint = globalMovedPoint = Point<int>(x, y);
	select(this);
	lineSettings->startChange();
}

void LineComponent::paint(Graphics &canvas) {
	if (type & LineType::boundBox)
		canvas.drawRect(0, 0, getWidth(), getHeight());
	canvas.setColour(colour);
	if (type & LineType::dashed) {
		float tmp[] {(float)dashedValue1, (float)dashedValue2};
		canvas.drawDashedLine(Line<float>(point1.toFloat(), point2.toFloat()), tmp, 2, (float)lineThickness);
	}
	else
		canvas.drawLine(point1.getX(), point1.getY(), point2.getX(),  point2.getY(), lineThickness);
	if (type & LineType::rounded) {
		canvas.fillEllipse(point1.getX() - (lineThickness ) / 2, point1.getY() - (lineThickness + 1) / 2, lineThickness, lineThickness);
		canvas.fillEllipse(point2.getX() - (lineThickness ) / 2, point2.getY() - (lineThickness + 1) / 2, lineThickness, lineThickness);
	}

	if (selected == this) {
		canvas.setColour(colour.contrasting(0.5));
		canvas.fillEllipse(point1.getX() - (lineThickness) / 2, point1.getY() - (lineThickness + 1) / 2, lineThickness, lineThickness);
		canvas.fillEllipse(point2.getX() - (lineThickness) / 2, point2.getY() - (lineThickness + 1) / 2, lineThickness, lineThickness);
	}
}

void LineComponent::mouseUp(const MouseEvent &event) {
	lineSettings->endChange();
}

void LineComponent::mouseDown(const MouseEvent &event) {
	select(this);
	lineSettings->startChange();
	repaint();
	if (event.getMouseDownPosition().getDistanceFrom(point1) <= std::max(3.0, lineThickness * 0.6)) {
		globalFixedPoint = getPosition() + point2;
		globalMovedPoint = getPosition() + point1;
		dragMode = false;
		return;
	}
	if (event.getMouseDownPosition().getDistanceFrom(point2) <= std::max(3.0, lineThickness * 0.6)) {
		globalFixedPoint = getPosition()  + point1;
		globalMovedPoint = getPosition()  + point2;
		dragMode = false;
		return;
	}
	dragger.startDraggingComponent(this, event);
	dragMode = true;
}

void LineComponent::mouseDrag(const MouseEvent &event) {
	if (dragMode) {
		dragger.dragComponent(this, event, &constrainer);
		return;
	}
	Point<int> newPoint(globalMovedPoint + Point<int>(event.getDistanceFromDragStartX(), event.getDistanceFromDragStartY()));
	int startX = std::min(globalFixedPoint.getX(), newPoint.getX());
	int startY = std::min(globalFixedPoint.getY(), newPoint.getY());
	int wi = std::abs(globalFixedPoint.getX() - newPoint.getX());
	int hi = std::abs(globalFixedPoint.getY() - newPoint.getY());
	setBounds(startX - deltaBounds.getX(), startY -  deltaBounds.getY(), wi + 2 * deltaBounds.getX(), hi + 2 * deltaBounds.getY());
	point1 = globalFixedPoint - getPosition();
	point2 = newPoint - getPosition();
}

bool LineComponent::hitTest(int x, int y) {
	//Ax + By + C = 0
	int A = point1.getY() - point2.getY();
	int B = point2.getX() - point1.getX();
	int C = point1.getX() * point2.getY() - point1.getY() * point2.getX();
	return std::abs((A * x + B * y + C)) / sqrt((float)(A * A + B * B)) <= std::max(lineThickness * 0.6, 3.0) || (A == 0 && B == 0);
}

void LineComponent::setLineThickness(int lineThickness) {
	this->lineThickness = lineThickness;
	int startX = getPosition().getX() + deltaBounds.getX();
	int startY = getPosition().getY() + deltaBounds.getY();
	int wi = getWidth() - 2 * deltaBounds.getX();
	int hi = getHeight() - 2 * deltaBounds.getY();
	point1 -= deltaBounds;
	point2 -= deltaBounds;
	deltaBounds.setXY((lineThickness + 1) >> 1, (lineThickness + 1) >> 1);
	point1 += deltaBounds;
	point2 += deltaBounds;
	setBounds(startX - deltaBounds.getX(), startY -  deltaBounds.getY(), wi + 2 * deltaBounds.getX(), hi + 2 * deltaBounds.getY());
	repaint();
	if (lineSettings)
		lineSettings->update();
}

void LineComponent::setPos(Point<int> const &p1, Point<int> const &p2) {
	int startX = std::min(p1.getX(), p2.getX());
	int startY = std::min(p1.getY(), p2.getY());
	int wi = std::abs(p1.getX() - p2.getX());
	int hi = std::abs(p1.getY() - p2.getY());
	setBounds(startX - deltaBounds.getX(), startY -  deltaBounds.getY(), wi + 2 * deltaBounds.getX(), hi + 2 * deltaBounds.getY());
	point1 = p1 - getPosition();
	point2 = p2 - getPosition();
	repaint();
	if (lineSettings)
		lineSettings->update();
}

void LineComponent::setDashedValue1(unsigned int value) {
	dashedValue1 = value;
	repaint();
	if (lineSettings)
		lineSettings->update();
}

unsigned int LineComponent::getDashedValue1() const noexcept {
	return dashedValue1;
}

void LineComponent::setDashedValue2(unsigned int value) {
	dashedValue2 = value;
	repaint();
	if (lineSettings)
		lineSettings->update();
}

unsigned int LineComponent::getDashedValue2() const noexcept {
	return dashedValue2;
}

Point<int> LineComponent::getPoint1() const noexcept {
	return point1 + getPosition();
}

Point<int> LineComponent::getPoint2() const noexcept {
	return point2 + getPosition();
}

int LineComponent::getLineThickness() const noexcept {
	return lineThickness;
}

void LineComponent::setColour(Colour colour) {
	this->colour = colour;
	repaint();
	if (lineSettings)
		lineSettings->update();
}

Colour LineComponent::getColour() const noexcept {
	return colour;
}

void LineComponent::setLineType(int type) {
	this->type = type;
	repaint();
	if (lineSettings)
		lineSettings->update();
}

int LineComponent::getLineType() const noexcept {
	return type;
}
