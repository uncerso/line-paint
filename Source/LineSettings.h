/*
  ==============================================================================

    Toolbar.h
    Created: 28 Oct 2017 9:38:07pm
    Author:  uncerso

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "CustomLookAndFeel.h"
#include "ColourChangeButton.h"
#include "stringConstants.h"
#include "LineSettingsState.h"
#include "ObjectBroadcaster.h"

class CustomSlider
	: public Slider
	, public ObjectBroadcaster<char>
{
public:
	void mouseDown(const MouseEvent &event) override {
		sendObjectMessage(mouseDownOnTheSlider); // down
		Slider::mouseDown(event);
	}

	void mouseUp(const MouseEvent &event) override {
		Slider::mouseUp(event);
		sendObjectMessage(mouseUpOnTheSlider); // up
	}

};

class LineComponent;

/// Manage line changes
class LineSettings
	: public Component
	, public Slider::Listener
	, public Button::Listener
	, public ActionListener
	, public ObjectBroadcaster<std::pair<LineSettingsState, LineSettingsState> >
	, public ObjectBroadcaster<char>::ObjectListener
{

	void paint(Graphics &canvas) override;
	void resized() override;
	void sliderValueChanged(Slider *slider) override;
	void buttonClicked(Button *button) override;

	void actionListenerCallback(const String &s) override;
	void objectListenerCallback(char const & event) override;
public:

	/// Update information about currently selected line
	void update();

	/// Remembers line information before it started changing
	void startChange();

	/// Remembers line information after the change, creates an event
	/// about the change and sends it to the listener
	void endChange();

	LineSettings();
	~LineSettings();

	/// Deletes currently selected line
	void deleteCurrentLine();

	/// Returns default line settings
	LineSettingsState const & getDefaultState() const;

private:
	void handleButtonClick(Button *button);

	LineSettingsState defaultSettings;
	LineSettingsState startSettingChange;
	CustomLookAndFeel laf;

	CustomSlider lineThickness;
	Label lineThicknessLabel;

	GroupComponent gpType;
	TextButton roundedType;
	TextButton boundBoxType;
	TextButton deleteLine;

	GroupComponent gpDashedSettings;
	OwnedArray<CustomSlider> dashedSettings;

	OwnedArray<TextButton> dashedTypeButtons;

	ColourChangeButton colourButton;

};
