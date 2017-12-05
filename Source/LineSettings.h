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
class CustomSlider
	: public Slider
	, public ActionBroadcaster
{
public:
	void mouseDown(const MouseEvent &event) override {
		sendActionMessage("D"); // down
		Slider::mouseDown(event);
	}

	void mouseUp(const MouseEvent &event) override {
		sendActionMessage("U"); // up
		Slider::mouseUp(event);
	}

};

class LineComponent;
class LineSettings;
class CentralComponent;

class LineSettingsState {
	friend LineSettings;
public:
	LineSettingsState(bool del = false,
	                  LineComponent *ptr = nullptr,
	                  int lineThickness = 0,
	                  int type = 0,
	                  Colour colour = Colour::fromRGB(45, 91, 129),
	                  Point<int> const &globalPosPoint1 = Point<int>(),
	                  Point<int> const &globalPosPoint2 = Point<int>(),
	                  unsigned int dashedValue1 = 8,
	                  unsigned int dashedValue2 = 8
	                  );
	~LineSettingsState() = default;

	/// Indicates whether the line is shown
	bool isExist() const;
	LineComponent*getPtr() const;
	int getLineThickness() const;
	int getType() const;
	Colour getColour() const;
	Point<int> getGlobalPosPoint1() const;
	Point<int> getGlobalPosPoint2() const;
	bool operator!=(LineSettingsState const &other) const;
	unsigned int getDashedValue1() const;
	unsigned int getDashedValue2() const;
private:
	bool exist;
	LineComponent *ptr;
	int lineThickness;
	int type;
	Colour colour;
	Point<int> globalPosPoint1;
	Point<int> globalPosPoint2;
	unsigned int dashedValue1;
	unsigned int dashedValue2;
};

/// Manage line changes
class LineSettings
	: public Component
	, public Slider::Listener
	, public Button::Listener
	, public ActionListener
{
public:

	void paint(Graphics &canvas) override;
	void resized() override;
	void sliderValueChanged(Slider *slider) override;
	void buttonClicked(Button *button) override;

	void actionListenerCallback(const String &s) override;

	/// Update information about currently selected line
	void update();

	/// Selects listener to send events to
	void selectListener(CentralComponent *centralComponent);

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

	CentralComponent *centralComponent;

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
