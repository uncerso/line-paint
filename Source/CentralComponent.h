/*
  ==============================================================================

    CentralComponent.h
    Created: 25 Oct 2017 11:11:53am
    Author:  uncerso

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include <list>
#include <stack>
//#include "LineSettings.h"

class LineComponent;
class Tools;
class LineSettings;
class LineSettingsState;

class CentralComponent
	: public Component
	, public KeyListener
	, public ActionListener
{
public:
	CentralComponent();
	~CentralComponent();
	void paint(Graphics &canvas) override;
	void resized() override;

	bool keyPressed(const KeyPress &key, Component *c ) override;

	void mouseDown(const MouseEvent &event) override;
	void mouseDrag(const MouseEvent &event) override;

	void lineSettingsListener(const std::pair<LineSettingsState, LineSettingsState> &event);

	void actionListenerCallback(const String &s) override;

	void undo();
	void redo();
private:

	void handleDo(LineSettingsState const & fst, LineSettingsState const & snd);
	void addIntoTheMemory(const std::pair<LineSettingsState, LineSettingsState> &event);
	LookAndFeel_V4 laf;
	Colour backgroundColour;
	TabbedComponent *tabs;
	Tools *tools;
	LineSettings *lineSettings;
	std::list<LineComponent*> lines;
	std::stack<std::pair<LineSettingsState, LineSettingsState>*> memory;
	std::stack<std::pair<LineSettingsState, LineSettingsState>*> undosMemory;

};