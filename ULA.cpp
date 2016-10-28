#include "ULA.h"

ULA::ULA()
{
}

ULA::~ULA()
{
}

void ULA::setTempReg1(string element) {
	this->temporaryReg1 = element;
}

void ULA::setTempReg2(string element) {
	this->temporaryReg2 = element;
}

void ULA::add(string reg, string value, Memoria *m, Registers *r) {
	int y = r->getRegisterValue(reg);
	y += 1;
	r->setRegisterValue(reg, this->DecToBin(y), m);
	cout << "ADD" << endl;
}

void ULA::sub(string reg, string value, Memoria *m, Registers *r) {
	int y = r->getRegisterValue(reg);
	if (y > 0) {
		y -= 1;
	}
	else {
		y = 0;
	}
	r->setRegisterValue(reg, this->DecToBin(y), m);
	cout << "SUB" << endl;
}

void ULA::mul(string reg, Memoria *m, Registers *r) {
	int x = this->bin2dec(this->temporaryReg1.c_str());
	int y = this->bin2dec(this->temporaryReg2.c_str());

	r->setRegisterValue(reg, this->DecToBin(x*y), m);
	cout << "MUL" << endl;
}

void ULA::div(string reg, Memoria *m, Registers *r){
	int x = this->bin2dec(this->temporaryReg1.c_str());
	int y = this->bin2dec(this->temporaryReg2.c_str());

	if (y == 0) {
		x = 0;
		cout << "Erro. Divisao por 0, registrador assumira valor 0." << endl;
	}
	else {
		x = x / y;
	}

	r->setRegisterValue(reg, this->DecToBin(x), m);
	cout << "DIV" << endl;
}

void ULA::not(string reg, Memoria *m, Registers *r) {
	string x = this->temporaryReg1;
	string y = "";

	for (int i = 0; i < x.size(); i++) {
		if (x.at(i) == '0') {
			y.append("1");
		}
		else {
			y.append("0");
		}
	}

	r->setRegisterLogValue(reg, y, m);
	cout << "NOT" << endl;
}

void ULA::or(string reg, Memoria *m, Registers *r) {
	string x = this->temporaryReg1;
	string y = this->temporaryReg2;
	string a = "";

	int size = 0;

	if (x.size() > y.size()) {
		size = x.size();
		for (int i = 0; i < size - y.size(); i++) {
			a.append("0");
		}
		a.append(y);
		y = "";
		for (int i = 0; i < size; i++) {
			if (x.at(i) == '1' || a.at(i) == '1') {
				y.append("1");
			}
			else {
				y.append("0");
			}
		}

		r->setRegisterLogValue(reg, y, m);
		cout << "OR" << endl;
	}
	else {
		size = y.size();
		for (int i = 0; i < size - x.size(); i++) {
			a.append("0");
		}
		a.append(x);
		x = "";
		for (int i = 0; i < size; i++) {
			if (y.at(i) == '1' || a.at(i) == '1') {
				x.append("1");
			}
			else {
				x.append("0");
			}
		}

		r->setRegisterLogValue(reg, x, m);
		cout << "OR" << endl;
	}
}

void ULA::and(string reg, Memoria *m, Registers *r) {
	string x = this->temporaryReg1;
	string y = this->temporaryReg2;
	string a = "";

	int size = 0;

	if (x.size() > y.size()) {
		size = x.size();
		for (int i = 0; i < size - y.size(); i++) {
			a.append("0");
		}
		a.append(y);
		y = "";
		for (int i = 0; i < size; i++) {
			if (x.at(i) == '1' && a.at(i) == '1') {
				y.append("1");
			}
			else {
				y.append("0");
			}
		}

		r->setRegisterLogValue(reg, y, m);
		cout << "OR" << endl;
	}
	else {
		size = y.size();
		for (int i = 0; i < size - x.size(); i++) {
			a.append("0");
		}
		a.append(x);
		x = "";
		for (int i = 0; i < size; i++) {
			if (y.at(i) == '1' || a.at(i) == '1') {
				x.append("1");
			}
			else {
				x.append("0");
			}
		}

		r->setRegisterLogValue(reg, x, m);
		cout << "OR" << endl;
	}
}