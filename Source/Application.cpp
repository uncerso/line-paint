/*
  ==============================================================================

    Application.cpp
    Created: 25 Oct 2017 11:10:51am
    Author:  uncerso

  ==============================================================================
*/

#include "Application.h"
#include "MainForm.h"

Application::Application()
	: mainForm(nullptr)
{}

void Application::initialise(const String &commandLineParameters) {
	mainForm = new MainForm();
}

void Application::shutdown() {
	if (mainForm) delete mainForm;
}

void Application::systemRequestedQuit() {
	quit();
}

const String Application::getApplicationName() {
	return "line paint";
}

const String Application::getApplicationVersion() {
	return ProjectInfo::versionString;
}

bool Application::moreThanOneInstanceAllowed() {
	return true;
}
