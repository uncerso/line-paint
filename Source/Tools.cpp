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

	setLookAndFeel(&laf);
	undo.setButtonText("undo");
	undo.addListener(this);
	addAndMakeVisible(undo);

	redo.setButtonText("redo");
	redo.addListener(this);
	addAndMakeVisible(redo);

	colourButton.setButtonText("Click to change background colour");
	colourButton.addActionListener(this);
	colourButton.selectColour(colour);
	addAndMakeVisible(colourButton);
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
	undo.setBounds(sliderLeft, proportionOfHeight(0.05f), width >> 1, proportionOfHeight(0.05f) );
	redo.setBounds(sliderLeft + (width >> 1), proportionOfHeight(0.05f), width >> 1, proportionOfHeight(0.05f) );
	colourButton.setBounds(sliderLeft, proportionOfHeight(0.15f), width,  proportionOfHeight(0.05f));
}

void Tools::buttonClicked(Button *button) {
	if (button == &undo) sendActionMessage("U");
	if (button == &redo) sendActionMessage("R");
}
