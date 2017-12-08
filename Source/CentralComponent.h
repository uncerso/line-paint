/*
  ==============================================================================

    CentralComponent.h
    Created: 25 Oct 2017 11:11:53am
    Author:  uncerso

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
// #include <list>
//#include "LineSettings.h"

class LineComponent;
class Tools;
class LineSettings;
class LineSettingsState;
class Memorize;

/// Application logic
class CentralComponent
	: public Component
	, public ActionListener
{
public:
	CentralComponent();
	~CentralComponent();
private:
	void paint(Graphics &canvas) override;
	void resized() override;

	void mouseDown(const MouseEvent &event) override;
	void mouseDrag(const MouseEvent &event) override;
public:

	/// Gets events from LineSettings (I know this is an antipattern)
	void lineSettingsListener(const std::pair<LineSettingsState, LineSettingsState> &event);

	void actionListenerCallback(const String &s) override;

	/// Undo
	void undo();
	/// Redo
	void redo();
private:

	void handleDo(LineSettingsState const & fst, LineSettingsState const & snd);
	void addIntoTheMemory(const std::pair<LineSettingsState, LineSettingsState> &event);
	LookAndFeel_V4 laf;
	Colour backgroundColour;
	TabbedComponent *tabs;
	Tools *tools;
	LineSettings *lineSettings;
	Memorize *memorize;
	LineComponent* lastLine;

};
