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
	ColourChangeButton(const String &s = "Click to change colour...");

	void selectColour(Colour const &colour);

	void clicked() override;

	void changeListenerCallback(ChangeBroadcaster* source) override;

	void deadOfColourSelector();

};
