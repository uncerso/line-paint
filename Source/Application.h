/*
  ==============================================================================

    Application.h
    Created: 25 Oct 2017 11:10:51am
    Author:  uncerso

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class MainForm;

class Application : public JUCEApplication {
public:
	Application();
	~Application() = default;

	void initialise(const String &commandLineParameters) override;
	void shutdown() override;
	void systemRequestedQuit() override;
	const String getApplicationName() override;
	const String getApplicationVersion() override;
	bool moreThanOneInstanceAllowed() override;

public:
	MainForm *mainForm;
};
