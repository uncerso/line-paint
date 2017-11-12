/*
  ==============================================================================

    MainForm.cpp
    Created: 25 Oct 2017 11:13:06am
    Author:  uncerso

  ==============================================================================
*/

#include "MainForm.h"
#include "CentralComponent.h"

MainForm::MainForm() : DocumentWindow(
	        JUCEApplication::getInstance()->getApplicationName(),
	        Colour::fromRGB(97, 90, 117),
	        DocumentWindow::allButtons)
{
	setColour(DocumentWindow::textColourId, Colour::fromRGB(177, 170, 197));
	centreWithSize((int)(getParentWidth() * 0.9), (int)(getParentHeight() * 0.9));
	setResizable(true, false);
	setVisible(true);
	centralComponent = new CentralComponent();
	setContentOwned(centralComponent, false);
	setUsingNativeTitleBar(true);
}

MainForm::~MainForm() {}

void MainForm::closeButtonPressed() {
	JUCEApplication::getInstance()->systemRequestedQuit();
}
