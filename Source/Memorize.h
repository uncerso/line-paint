/*
  ==============================================================================

    Memorize.h
    Created: 8 Dec 2017 2:32:32pm
    Author:  uncerso

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include <stack>
#include "ObjectBroadcaster.h"

class LineSettingsState;

class Memorize
	: public ObjectBroadcaster<std::pair<LineSettingsState, LineSettingsState> >::ObjectListener
	, public ObjectBroadcaster<char>::ObjectListener
{
public:
	void addIntoMemory(std::pair<LineSettingsState, LineSettingsState> const & event);
private:
	void objectListenerCallback(std::pair<LineSettingsState, LineSettingsState> const & event) override;
	void objectListenerCallback(char const & event) override;
	void handleDo(LineSettingsState const & fst, LineSettingsState const & snd) const;
	void undo();
	void redo();
	std::stack<std::pair<LineSettingsState, LineSettingsState>*> memory;
	std::stack<std::pair<LineSettingsState, LineSettingsState>*> undosMemory;
};
