/*
  ==============================================================================

    ColourChangeButton.cpp
    Created: 10 Nov 2017 9:48:57am
    Author:  uncerso

  ==============================================================================
*/

#include "ColourChangeButton.h"
#include "stringConstants.h"
#include <string>

ColourChangeButton::ColourChangeButton(const String &s)
	: TextButton(s)
{}

void ColourChangeButton::selectColour(Colour const &colour) {
	setColour(TextButton::buttonColourId, colour);
	setColour(TextButton::textColourOffId, colour.contrasting(1));
}

void ColourChangeButton::clicked() {
	sendActionMessage(String((char *)&createColourSelector));         // create
	CustomColourSelector *colourSelector = new CustomColourSelector(this);
	colourSelector->setName("background");
	colourSelector->setCurrentColour(findColour(TextButton::buttonColourId));
	colourSelector->addChangeListener(this);
	colourSelector->setColour(ColourSelector::backgroundColourId, Colours::transparentBlack);
	colourSelector->setSize(DocumentWindow::getTopLevelWindow(0)->getParentWidth() * 0.2, DocumentWindow::getTopLevelWindow(0)->getParentHeight() * 0.4);
	CallOutBox::launchAsynchronously(colourSelector, getScreenBounds(), nullptr);
}

void ColourChangeButton::changeListenerCallback(ChangeBroadcaster* source) {
	if (ColourSelector * cs = dynamic_cast<ColourSelector*>(source)) {
		setColour(TextButton::buttonColourId, cs->getCurrentColour());
		setColour(TextButton::textColourOffId, cs->getCurrentColour().contrasting(1));
		sendActionMessage((char *)&changeColourButton);         // change
	};
}

void ColourChangeButton::deadOfColourSelector() const noexcept {
	sendActionMessage(String((char *)&removeColourSelector));         // remove
}
