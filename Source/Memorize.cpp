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
		if (!y) return;
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

class MemorizeTests
	: public UnitTest
{
public:
	MemorizeTests()
		: UnitTest("undo/redo", "Memory")
	{}

	void undoTest() {
		Memorize mem;
		expect(mem.memory.empty(), "Failed init of the memory.");
		expect(mem.undosMemory.empty(), "Failed init of the memory.");
		mem.addIntoMemory(std::make_pair(LineSettingsState(true,nullptr),LineSettingsState(true,nullptr)));
		expect(mem.undosMemory.empty(), "Failed adding into the memory.");
		expectEquals((int)mem.memory.size(), 1, "Failed adding into the memory.");
		mem.addIntoMemory(std::make_pair(LineSettingsState(true,nullptr),LineSettingsState(true,nullptr)));
		expect(mem.undosMemory.empty(), "Failed adding into the memory.");
		expectEquals((int)mem.memory.size(), 2, "Failed adding into the memory.");
		mem.undo();
		expectEquals((int)mem.undosMemory.size(),1, "Failed undo.");
		expectEquals((int)mem.memory.size(), 1, "Failed undo.");
		mem.undo();
		expectEquals((int)mem.undosMemory.size(), 2, "Failed undo.");
		expect(mem.memory.empty(), "Failed undo.");
	}
	void redoTest() {
		Memorize mem;		
		mem.addIntoMemory(std::make_pair(LineSettingsState(true,nullptr),LineSettingsState(true,nullptr)));
		mem.addIntoMemory(std::make_pair(LineSettingsState(true,nullptr),LineSettingsState(true,nullptr)));
		mem.undo();
		mem.undo();
		mem.redo();
		expectEquals((int)mem.memory.size(), 1, "Failed redo.");
		expectEquals((int)mem.undosMemory.size(),1, "Failed redo.");
		mem.redo();
		expect(mem.undosMemory.empty(), "Failed redo.");
		expectEquals((int)mem.memory.size(), 2, "Failed redo.");
	}

	void runTest() override {
		beginTest("undo");
		undoTest();
		beginTest("redo");		
		redoTest();
	}

};

static MemorizeTests MemorizeUnitTests; 
