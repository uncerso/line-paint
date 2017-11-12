/*
  ==============================================================================

    MainForm.h
    Created: 25 Oct 2017 11:13:06am
    Author:  uncerso

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class CentralComponent;

class MainForm : public DocumentWindow {
public:
	MainForm();
	~MainForm();

	void closeButtonPressed() override;

private:
	CentralComponent *centralComponent;
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainForm);
};
