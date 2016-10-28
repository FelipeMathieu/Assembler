#pragma once

#include <queue>
#include <iostream>
#include "Memoria.h"
#include "adressDataBus.h"
#include "Interpretador.h"

using namespace std;

class instructQueue
{
private:
	deque <string> itQueue;
	int controllerQueue = 0;

public:
	instructQueue();
	~instructQueue();
	bool setQueue(Interpretador *it, adressDataBus *aDB, Memoria *m);
	string getFirst() {
		string aux = this->itQueue.front();
		this->itQueue.pop_front();
		this->itQueue.push_back("");
		return aux;
	};
	void setControllerQueue(int i) {
		this->controllerQueue = i;
	};
	int queueSize() {
		return this->itQueue.size();
	};
	int getControllerQueue() {
		return this->controllerQueue;
	}
	bool isEmpty();
};

