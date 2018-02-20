/*
  ==============================================================================

    MainForm.cpp
    Created: 25 Oct 2017 11:13:06am
    Author:  uncerso

  ==============================================================================
*/

#include "MainForm.h"
#include "CentralComponent.h"
namespace line_paint{

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

#ifndef NDEBUG
	unit = new	UnitTestClasses::UnitTestsDemo();
	unit->setName("background");
	unit->setColour(ColourSelector::backgroundColourId, Colours::transparentBlack);
	unit->setSize(DocumentWindow::getTopLevelWindow(0)->getParentWidth() * 0.3, DocumentWindow::getTopLevelWindow(0)->getParentHeight() * 0.5);
	CallOutBox::launchAsynchronously(unit, getScreenBounds(), nullptr);
#endif
#if JUCE_OPENGL
	openGLContext.attachTo(*getTopLevelComponent());
#endif
}

MainForm::~MainForm() {}

void MainForm::closeButtonPressed() {
	JUCEApplication::getInstance()->systemRequestedQuit();
}
}
