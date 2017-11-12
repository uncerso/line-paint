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

CentralComponent::CentralComponent()
	: Component("Central Component")
{
	setWantsKeyboardFocus(true);
	laf.setColourScheme(LookAndFeel_V4::getLightColourScheme());
	setLookAndFeel(&laf);
	backgroundColour = laf.getCurrentColourScheme().getUIColour(juce::LookAndFeel_V4::ColourScheme::UIColour::windowBackground);
	tabs = new TabbedComponent(TabbedButtonBar::TabsAtRight);
	tools = new Tools(backgroundColour);
	lineSettings = new LineSettings();
	lineSettings->selectListener(this);
	tools->addActionListener(this);
	LookAndFeel_V4::getDarkColourScheme().getUIColour(juce::LookAndFeel_V4::ColourScheme::UIColour::windowBackground);
	LineComponent::selectLineSettings(lineSettings);
	tabs->addTab("Tools", LookAndFeel_V4::getDarkColourScheme().getUIColour(juce::LookAndFeel_V4::ColourScheme::UIColour::windowBackground), tools, true);
	tabs->addTab("Settings", LookAndFeel_V4::getMidnightColourScheme().getUIColour(juce::LookAndFeel_V4::ColourScheme::UIColour::windowBackground), lineSettings, true);
	addKeyListener(this);
	addAndMakeVisible(tabs);
}

CentralComponent::~CentralComponent() {
	setLookAndFeel(nullptr);
	LineComponent::selectLineSettings(nullptr);
	delete tools;
	delete lineSettings;
	deleteAllChildren();
}

void CentralComponent::paint(Graphics &canvas) {
	//canvas.fillAll(Colour::fromRGB(rand() % 256, rand() % 256, rand() % 256));
	//canvas.fillAll(Colour::fromRGB(255, 255, 255));
	//canvas.fillAll(laf.getCurrentColourScheme().getUIColour(juce::LookAndFeel_V4::ColourScheme::UIColour::windowBackground));
	canvas.fillAll(backgroundColour);
}

void CentralComponent::mouseDown(const MouseEvent &event) {
	if (event.mods == ModifierKeys::rightButtonModifier) {
		LineComponent::select(nullptr);
		return;
	}
	LineSettingsState const & state(lineSettings->getDefaultState());
	lines.push_back(new LineComponent(event.getMouseDownX(), event.getMouseDownY(), state.getLineThickness(), state.getColour(), state.getType()));
	addAndMakeVisible(lines.back());
	addIntoTheMemory(std::make_pair(LineSettingsState(false, lines.back()), LineSettingsState(true, lines.back())));
}

void CentralComponent::mouseDrag(const MouseEvent &event) {
	if (event.mods == ModifierKeys::leftButtonModifier)
		lines.back()->mouseDrag(event);
}

void CentralComponent::resized() {
	tabs->setBounds(getWidth() * 0.7, 0, getWidth() * 0.3, getHeight());
	tabs->setTabBarDepth(proportionOfHeight(0.03f));
}

void CentralComponent::handleDo(LineSettingsState const & fst, LineSettingsState const & snd) {
	if (!fst.isExist() && snd.isExist())
		fst.getPtr()->setVisible(true);
	else
	if (fst.isExist() && !snd.isExist()) {
		fst.getPtr()->setVisible(false);
		LineComponent::selectNullptrIfSelected(fst.getPtr());
	}
	else{
		auto y = snd.getPtr();
		y->setPos(snd.getGlobalPosPoint1(), snd.getGlobalPosPoint2());
		y->setLineThickness(snd.getLineThickness());
		y->setLineType(snd.getType());
		y->setColour(snd.getColour());
	}
}

void CentralComponent::undo() {
	// second -> first
	if (memory.empty()) return;
	handleDo(memory.top()->second, memory.top()->first);
	undosMemory.push(memory.top());
	memory.pop();
	lineSettings->update();
}

void CentralComponent::redo() {
	// first -> second
	if (undosMemory.empty()) return;
	handleDo(undosMemory.top()->first, undosMemory.top()->second);
	memory.push(undosMemory.top());
	undosMemory.pop();
	lineSettings->update();
}

void CentralComponent::lineSettingsListener(const std::pair<LineSettingsState, LineSettingsState> &event) {
	addIntoTheMemory(event);
}

void CentralComponent::actionListenerCallback(const String &s) {
	switch (s[0]) {
	case 'U':
		undo();
		break;
	case 'R':
		redo();
		break;
	case 'H':
		backgroundColour = tools->getColour();
		repaint();
		break;
	default:
		break;
	}
}

void CentralComponent::addIntoTheMemory(const std::pair<LineSettingsState, LineSettingsState> &event) {
	while (!undosMemory.empty()) {
		delete undosMemory.top();
		undosMemory.pop();
	}
	auto x = new std::pair<LineSettingsState, LineSettingsState>(event);
	handleDo(x->first, x->second);
	memory.push(x);
}

bool CentralComponent::keyPressed(const KeyPress &key, Component *c) {
	if (key.getModifiers().isCtrlDown() && (key.getKeyCode() == 'Z')) {
		redo();
		return true;
	}

	if (key.getModifiers().isCtrlDown()  && (key.getKeyCode() == 'z')) {
		undo();
		return true;
	}
	// if (key.getModifiers().isCtrlDown() && (((key.getKeyCode() == 'z') && key.getModifiers().isShiftDown() ) || (key.getKeyCode() == 'Z'))) {
	//      redo();
	//      return true;
	// }
	//
	// if (key.getModifiers().isCtrlDown()  && (key.getKeyCode() == 'z')) {
	//      undo();
	//      return true;
	// }
	return false;
}
