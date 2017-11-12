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
	                  Colour colour = Colours::cornflowerblue,
	                  Point<int> const &globalPosPoint1 = Point<int>(),
	                  Point<int> const &globalPosPoint2 = Point<int>()
	                  );
	~LineSettingsState() = default;
	bool isExist() const;
	LineComponent*getPtr() const;
	int getLineThickness() const;
	int getType() const;
	Colour getColour() const;
	Point<int> getGlobalPosPoint1() const;
	Point<int> getGlobalPosPoint2() const;
	bool operator!=(LineSettingsState const &other) const;
private:
	bool exist;
	LineComponent *ptr;
	int lineThickness;
	int type;
	Colour colour;
	Point<int> globalPosPoint1;
	Point<int> globalPosPoint2;
};


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

	void update();
	void selectListener(CentralComponent *centralComponent);

	void startChange();
	void endChange();
	void change();

	LineSettings();
	~LineSettings();

	void deleteCurrentLine();

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

	OwnedArray<TextButton> dashedTypeButtons;

	ColourChangeButton colourButton;

};
