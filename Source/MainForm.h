/*
  ==============================================================================

    MainForm.h
    Created: 25 Oct 2017 11:13:06am
    Author:  uncerso

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "UnitTests.hpp"

class CentralComponent;

/// Creates a window and sets its look
class MainForm : public DocumentWindow {
public:
	MainForm();
	~MainForm();

	/// This method is called when the user tries to close the window
	void closeButtonPressed() override;

private:
	CentralComponent *centralComponent;
#if JUCE_OPENGL
	OpenGLContext openGLContext;
#endif
	UnitTestClasses::UnitTestsDemo *unit;
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainForm);
};
