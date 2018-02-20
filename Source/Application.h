/*
  ==============================================================================

    Application.h
    Created: 25 Oct 2017 11:10:51am
    Author:  uncerso

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
namespace line_paint{

class MainForm;

/// Defines application settings
class Application : public JUCEApplication {
public:
	Application();
	~Application() = default;

	/// Called when the application starts
	void initialise(const String &commandLineParameters) override;
	/// Called when the application shutdowns
	void shutdown() override;
	/// Called when the operating system trying to close the application
	void systemRequestedQuit() override;
	///	Returns the application's name
	const String getApplicationName() override;
	///	Returns the application's version number
	const String getApplicationVersion() override;
	/// Checks whether multiple instances of the app are allowed
	bool moreThanOneInstanceAllowed() override;

private:
	MainForm *mainForm;
};
}
