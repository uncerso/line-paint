/*
  ==============================================================================

    Tools.cpp
    Created: 1 Nov 2017 2:25:17pm
    Author:  uncerso

  ==============================================================================
*/

#include "Tools.h"
#include "LineComponent.h"
#include "CentralComponent.h"

Tools::Tools(Colour const &colour)
	: Component("Tools")
{
	setWantsKeyboardFocus(true);
	setLookAndFeel(&laf);
	undoButton.setButtonText("undo");
	undoButton.addListener(this);
	addAndMakeVisible(undoButton);

	redoButton.setButtonText("redo");
	redoButton.addListener(this);
	addAndMakeVisible(redoButton);

	colourButton.setButtonText("Click to change background colour");
	colourButton.addActionListener(this);
	colourButton.selectColour(colour);
	addAndMakeVisible(colourButton);
	addKeyListener(this);
}

Tools::~Tools() {
	setLookAndFeel(nullptr);
	//deleteAllChildren();
}

void Tools::paint(Graphics &canvas) {
	canvas.fillAll(laf.getCurrentColourScheme().getUIColour(juce::LookAndFeel_V4::ColourScheme::UIColour::windowBackground));
}

Colour Tools::getColour() noexcept {
	return colour;
}

void Tools::actionListenerCallback(const String &s) {
	if (s[0] == 'H') {
		colour = colourButton.findColour(TextButton::buttonColourId);
		sendActionMessage(s);
	}
}

void Tools::resized() {
	int sliderLeft = proportionOfWidth(0.1f);
	int width = proportionOfWidth(0.8f);
	laf.setFontSize(proportionOfHeight(0.02f));
	undoButton.setBounds(sliderLeft, proportionOfHeight(0.05f), width >> 1, proportionOfHeight(0.05f) );
	redoButton.setBounds(sliderLeft + (width >> 1), proportionOfHeight(0.05f), width >> 1, proportionOfHeight(0.05f) );
	colourButton.setBounds(sliderLeft, proportionOfHeight(0.15f), width,  proportionOfHeight(0.05f));
}

void Tools::buttonClicked(Button *button) {
	if (button == &undoButton) undo();
	if (button == &redoButton) redo();
}

void Tools::undo() const noexcept {
	sendActionMessage("U");
}

void Tools::redo() const noexcept {
	sendActionMessage("R");
}

bool Tools::keyPressed(const KeyPress &key, Component *c) {
	if (key.getModifiers().isCtrlDown() && ((key.getKeyCode() == 'Z') || (key.getKeyCode() == 'z'))) {
		if (key.getModifiers().isShiftDown())
			redo();
		else
			undo();
		return true;
	}
	if (key.getKeyCode() == key.deleteKey) {
		LineComponent::deleteCurrentLine();
		return true;
	}
	if (key.getKeyCode() == key.escapeKey) {
		LineComponent::select(nullptr);
		return true;
	}
	return false;
}
