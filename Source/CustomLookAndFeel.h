/*
  ==============================================================================

    CustomLookAndFeel.h
    Created: 3 Nov 2017 11:51:00pm
    Author:  uncerso

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
namespace line_paint{
/// Almost same as LookAndFeel_V4, but with the ability to change
/// font size
class CustomLookAndFeel
	: public LookAndFeel_V4 {
public:
	CustomLookAndFeel() = default;
	~CustomLookAndFeel() = default;

	Font getLabelFont(Label&) override;
	Font getTextButtonFont(TextButton&, int buttonHeight) override;

	/// Same as respective LookAndFeel_V4 method, but with font font size
	/// changed from constant to variable
	void drawGroupComponentOutline(Graphics &g, int width, int height, const String &text, const Justification &position, GroupComponent &group) override;

	void setFontSize(float fontSize) noexcept;
private:
	float fontSize = 15;
};
}
