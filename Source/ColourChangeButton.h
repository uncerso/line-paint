/*
  ==============================================================================

    ColourChangeButton.h
    Created: 10 Nov 2017 9:48:57am
    Author:  uncerso

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class ColourChangeButton
	: public TextButton
	, public ActionBroadcaster
	, public ChangeListener
{
	class CustomColourSelector
		: public ColourSelector
	{
		ColourChangeButton *ptrForSendMessageAboutDied;
public:
		CustomColourSelector(ColourChangeButton *ptr)
			: ptrForSendMessageAboutDied(ptr) { }

		~CustomColourSelector() {
			ptrForSendMessageAboutDied->deadOfColourSelector();
		}

	};

public:
	ColourChangeButton(const String &s = "Click to change colour...")
		: TextButton(s)
	{}

	void selectColour(Colour const &colour) {
		setColour(TextButton::buttonColourId, colour);
		setColour(TextButton::textColourOffId, colour.contrasting(1));
	}

	void clicked() override {
		sendActionMessage("C"); // create
		CustomColourSelector *colourSelector = new CustomColourSelector(this);
		colourSelector->setName("background");
		colourSelector->setCurrentColour(findColour(TextButton::buttonColourId));
		colourSelector->addChangeListener(this);
		colourSelector->setColour(ColourSelector::backgroundColourId, Colours::transparentBlack);
		colourSelector->setSize(DocumentWindow::getTopLevelWindow(0)->getParentWidth() * 0.2, DocumentWindow::getTopLevelWindow(0)->getParentHeight() * 0.4);
		CallOutBox::launchAsynchronously(colourSelector, getScreenBounds(), nullptr);
	}

	void changeListenerCallback(ChangeBroadcaster* source) override {
		if (ColourSelector * cs = dynamic_cast<ColourSelector*>(source)) {
			setColour(TextButton::buttonColourId, cs->getCurrentColour());
			setColour(TextButton::textColourOffId, cs->getCurrentColour().contrasting(1));
			sendActionMessage("H"); // change
		};
	}

	void deadOfColourSelector() {
		sendActionMessage("R"); // remove
	}

};
