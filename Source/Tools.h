/*
  ==============================================================================

    Tools.h
    Created: 1 Nov 2017 2:25:17pm
    Author:  uncerso

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "CustomLookAndFeel.h"
#include "ColourChangeButton.h"
#include "ObjectBroadcaster.h"

class CentralComponent;

/// Manages undo/redo and backgroung colour change events
class Tools
	: public Component
	, public Button::Listener
	, public ActionListener
	, public KeyListener
	, public ActionBroadcaster
	, public ObjectBroadcaster<char>
{

	void paint(Graphics &canvas) override;
	void resized() override;
	void buttonClicked(Button *button) override;
	bool keyPressed(const KeyPress &key, Component *c ) override;
	void undo();
	void redo();
public:
	/// Returns selected background colour
	Colour getColour() noexcept;
	void actionListenerCallback(const String &s) override;

	Tools(Colour const &colour);
	~Tools();
private:
	CustomLookAndFeel laf;
	TextButton undoButton;
	TextButton redoButton;

	ColourChangeButton colourButton;
	Colour colour;

	GroupComponent gpHotkeys;
	Label hotkeysLabelKeys;
	Label hotkeysLabelInfo;
};
