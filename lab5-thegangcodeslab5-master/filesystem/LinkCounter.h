#pragma once
#include "LinkCounter.h"
#include "AbstractFile.h"

#include <iostream>

using namespace std;
class ImageFileProxy;
class TextFileProxy;

class LinkCounter {
	friend class ImageFileProxy;
	friend class TextFileProxy;
protected: //general access could facilitate memory leaks
	int count;
	LinkCounter() : count(1) {};
	~LinkCounter() = default;
	void addCount() {
		count++;
	}
	bool subCount() {
		count--;
		if (count == 0) {
			return true; //tells proxy to delete the file and this link counter
		}
		return false;
	}
};
