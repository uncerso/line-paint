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

class CentralComponent;

/// Manages undo/redo and backgroung colour change events
class Tools
	: public Component
	, public Button::Listener
	, public ActionBroadcaster
	, public ActionListener
	, public KeyListener
{

	void paint(Graphics &canvas) override;
	void resized() override;
	void buttonClicked(Button *button) override;
	bool keyPressed(const KeyPress &key, Component *c ) override;
	void undo() const noexcept;
	void redo() const noexcept;
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
};
