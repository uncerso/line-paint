/*
  ==============================================================================

    ObjectBroadcaster.h
    Created: 8 Dec 2017 8:53:13pm
    Author:  uncerso

  ==============================================================================
*/

#pragma once
#include <list>
namespace line_paint{

///
template <class ... T>
class ObjectBroadcaster {

public:
	class ObjectListener {
		friend ObjectBroadcaster;
		virtual void objectListenerCallback(T const & ... obj) = 0;
public:
		virtual ~ObjectListener() = default;
	};

protected:
	///
	void sendObjectMessage(T const & ... obj);

public:

	/// Add listener to send events to
	void addObjectListener(ObjectListener * x);

	virtual ~ObjectBroadcaster() = default;

private:
	std::list<ObjectListener*> listeners;
};

template <class ... T>
void ObjectBroadcaster<T ...>::sendObjectMessage(T const & ... obj) {
	for (auto &x : listeners)
		x->objectListenerCallback(obj ...);
}

template <class ... T>
void ObjectBroadcaster<T ...>::addObjectListener(ObjectListener * x) {
	listeners.push_back(x);
}
}