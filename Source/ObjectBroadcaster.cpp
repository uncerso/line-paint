/*
  ==============================================================================

    ObjectBroadcaster.cpp
    Created: 23 Dec 2017 5:35:26pm
    Author:  uncerso

  ==============================================================================
*/

#include "ObjectBroadcaster.h"
#include "../JuceLibraryCode/JuceHeader.h"
namespace line_paint{
#ifndef NDEBUG

class ObjectBroadcasterTests
	: public UnitTest
	, ObjectBroadcaster<int>
	, ObjectBroadcaster<int>::ObjectListener
{
public:
	ObjectBroadcasterTests()
		: UnitTest("Object broadcaster", "Broadcasters")
		, obj(0)
	{
		addObjectListener(this);		
	}

	void test() {
		obj = 0;
		sendObjectMessage(5);
		expectEquals(obj, 5, "Failed sending.");
		sendObjectMessage(7);
		expectEquals(obj, 7, "Failed sending.");
		sendObjectMessage(13);
		expectEquals(obj, 13, "Failed sending.");

	}

	void runTest() override {
		beginTest("Sending and receiving the object");
		test();
	}
private:
	int obj;
	void objectListenerCallback(int const & object) override{
		obj = object;
	}
};

static ObjectBroadcasterTests ObjectBroadcasterUnitTests; 
#endif
}
