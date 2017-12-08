/*
  ==============================================================================

    Memorize.cpp
    Created: 8 Dec 2017 2:32:32pm
    Author:  uncerso

  ==============================================================================
*/

#include "Memorize.h"
#include "LineSettingsState.h"
#include "LineComponent.h"
#include "stringConstants.h"

void Memorize::handleDo(LineSettingsState const & fst, LineSettingsState const & snd) const {
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
		y->setDashedValue1(snd.getDashedValue1());
		y->setDashedValue2(snd.getDashedValue2());
	}
}

void Memorize::undo() {
	// second -> first
	if (memory.empty()) return;
	handleDo(memory.top()->second, memory.top()->first);
	undosMemory.push(memory.top());
	memory.pop();
}

void Memorize::redo() {
	// first -> second
	if (undosMemory.empty()) return;
	handleDo(undosMemory.top()->first, undosMemory.top()->second);
	memory.push(undosMemory.top());
	undosMemory.pop();
}

void Memorize::addIntoMemory(std::pair<LineSettingsState, LineSettingsState> const & event) {
	while (!undosMemory.empty()) {
		delete undosMemory.top();
		undosMemory.pop();
	}
	auto x = new std::pair<LineSettingsState, LineSettingsState>(event);
	handleDo(x->first, x->second);
	memory.push(x);
}

void Memorize::objectListenerCallback(std::pair<LineSettingsState, LineSettingsState> const & event) {
	addIntoMemory(event);
}

void Memorize::objectListenerCallback(char const & event) {
	if (event == *UNDO) undo();
	if (event == *REDO) redo();
}
