#include"busInt.h"

busInt::busInt() {
}

void busInt::setDataBus(string value) {
	this->data = value;
}

void busInt::clearBus() {
	this->data = "";
}

void busInt::printBusInt() {
	cout << "BusInt: " << this->data << endl;
}