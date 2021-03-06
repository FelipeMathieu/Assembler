#include "instructQueue.h"

instructQueue::instructQueue()
{
	this->itQueue = *new deque<string>(4);
	this->controllerQueue = 0;
}

instructQueue::~instructQueue()
{
}

bool instructQueue::setQueue(Interpretador *it, adressDataBus *aDB, Memoria *m) {
	int i = 0;
	string memory = "", element = "";
	while (i < this->itQueue.size()) {
		if (it->getCodeOrder().size() > this->controllerQueue) {
			element = it->getCodeOrder().at(this->controllerQueue);
			memory = m->getMemoryAdress(element);
			if (aDB->sendAdress(memory, m)) {
				this->itQueue.at(i) = aDB->getDataBus();
				this->controllerQueue += 1;
			}
			else {
				return false;
				break;
			}
		}
		else {
			return false;
			break;
		}
		memory = "";
		element = "";
		i += 1;
	}
	return true;
}

bool instructQueue::isEmpty() {
	int i = 0;
	for (int j = 0; j < this->itQueue.size(); j++) {
		if (this->itQueue.at(j) == "") {
			i += 1;
		}
	}

	if (i >= this->itQueue.size()) {
		return true;
	}
	else {
		return false;
	}
}