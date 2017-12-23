/*
  ==============================================================================

    CentralComponent.cpp
    Created: 25 Oct 2017 11:11:53am
    Author:  uncerso

  ==============================================================================
*/

#include "CentralComponent.h"
#include "LineComponent.h"
#include "Tools.h"
#include "LineSettings.h"
#include "Memorize.h"
#include "stringConstants.h"

CentralComponent::CentralComponent()
	: Component("Central Component")
	, lastLine(nullptr)
{
	setWantsKeyboardFocus(true);
	laf.setColourScheme(LookAndFeel_V4::getLightColourScheme());
	setLookAndFeel(&laf);
	backgroundColour = laf.getCurrentColourScheme().getUIColour(juce::LookAndFeel_V4::ColourScheme::UIColour::windowBackground);
	tabs = new TabbedComponent(TabbedButtonBar::TabsAtRight);
	tools = new Tools(backgroundColour);
	lineSettings = new LineSettings();
	memorize = new Memorize();
	lineSettings->addObjectListener(memorize);
	tools->addObjectListener(memorize);
	tools->addObjectListener(this);
	addKeyListener(tools);
	LookAndFeel_V4::getDarkColourScheme().getUIColour(juce::LookAndFeel_V4::ColourScheme::UIColour::windowBackground);
	LineComponent::selectLineSettings(lineSettings);
	tabs->addTab("Tools", LookAndFeel_V4::getDarkColourScheme().getUIColour(juce::LookAndFeel_V4::ColourScheme::UIColour::windowBackground), tools, false);
	tabs->addTab("Settings", LookAndFeel_V4::getMidnightColourScheme().getUIColour(juce::LookAndFeel_V4::ColourScheme::UIColour::windowBackground), lineSettings, false);
	addAndMakeVisible(tabs);
	tabs->setAlwaysOnTop(true);
}

CentralComponent::~CentralComponent() {
	setLookAndFeel(nullptr);
	LineComponent::selectLineSettings(nullptr);
	delete tools;
	delete lineSettings;
	deleteAllChildren();
}

void CentralComponent::paint(Graphics &canvas) {
	canvas.fillAll(backgroundColour);
}

void CentralComponent::mouseDown(const MouseEvent &event) {
	if (event.mods == ModifierKeys::rightButtonModifier) {
		LineComponent::select(nullptr);
		return;
	}
	LineSettingsState const & state(lineSettings->getDefaultState());
	lastLine = new LineComponent(event.getMouseDownX(), event.getMouseDownY(), state.getLineThickness(), state.getColour(), state.getType(), state.getDashedValue1(), state.getDashedValue2());
	addAndMakeVisible(lastLine);
	addIntoTheMemory(std::make_pair(LineSettingsState(false, lastLine), LineSettingsState(true, lastLine)));
}

void CentralComponent::mouseDrag(const MouseEvent &event) {
	if (event.mods == ModifierKeys::leftButtonModifier)
		lastLine->mouseDrag(event);
}

void CentralComponent::resized() {
	tabs->setBounds(getWidth() * 0.7, 0, getWidth() * 0.3, getHeight());
	tabs->setTabBarDepth(proportionOfHeight(0.03f));
}

void CentralComponent::lineSettingsListener(const std::pair<LineSettingsState, LineSettingsState> &event) {
	addIntoTheMemory(event);
}

void CentralComponent::objectListenerCallback(char const & c){
	if (c == changeColourButton) {
		backgroundColour = tools->getColour();
		repaint();
	}
}

void CentralComponent::addIntoTheMemory(const std::pair<LineSettingsState, LineSettingsState> &event) {
	memorize->addIntoMemory(event);
}
