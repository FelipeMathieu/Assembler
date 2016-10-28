#include "Registers.h"

using namespace std;


Registers::Registers() {
	this->registradores["0011"] = 0;//A
	this->registradores["0100"] = 0;//B
	this->registradores["0101"] = 0;//C
	this->registradores["0110"] = 0;//D

	this->registradoresLog["0011"] = "0";//A
	this->registradoresLog["0100"] = "0";//B
	this->registradoresLog["0101"] = "0";//C
	this->registradoresLog["0110"] = "0";//D

	this->flags["ZF"] = 0;//Zero Flag
	this->flags["CY"] = 0;//Carry Flag
	this->flags["OF"] = 0;//OverFlow Flag
	this->flags["UF"] = 0;//UnderFlow Flag
}


void Registers::setRegisterValue(string Reg, string value, Memoria *m) {
	this->registradores.find(Reg)->second = this->bin2dec((const char *) value.c_str());
	this->registradoresLog.find(Reg)->second = value;
	m->setReg(Reg, value);
}


int Registers::getRegisterValue(string Reg) {
	return this->registradores.find(Reg)->second;
}


string Registers::getRegisterLogValue(string Reg) {
	return this->registradoresLog.find(Reg)->second;
}

void Registers::setRegisterLogValue(string Reg, string value, Memoria *m) {
	this->registradoresLog.find(Reg)->second = value;
	this->registradores.find(Reg)->second = this->bin2dec(value.c_str());
	m->setReg(Reg, value);
}

void Registers::printRegs() {
	cout << "Registradores: " << endl;
	cout << "A: " << this->registradores.find("0011")->second << endl;
	cout << "B: " << this->registradores.find("0100")->second << endl;
	cout << "C: " << this->registradores.find("0101")->second << endl;
	cout << "D: " << this->registradores.find("0110")->second << endl;

	//cout << "Registrador de FLAGS: " << this->registradores.find("0010")->second << endl;
}

void Registers::printRegsLog() {
	cout << "Registradores: " << endl;
	cout << "A: " << this->registradoresLog.find("0011")->second << endl;
	cout << "B: " << this->registradoresLog.find("0100")->second << endl;
	cout << "C: " << this->registradoresLog.find("0101")->second << endl;
	cout << "D: " << this->registradoresLog.find("0110")->second << endl;

	//cout << "Registrador de FLAGS: " << this->registradores.find("0010")->second << endl;
}


void Registers::setZeroFlag(int value) {
	this->flags["ZF"] = value;
}

int Registers::getFlagValue(string reg) {
	return this->flags[reg];
}


void Registers::setCarryFlag(int value) {
	this->flags["CF"] = value;
}


void Registers::setOverFlag(int value) {
	this->flags["OF"] = value;
}


void Registers::setUnderFlag(int value) {
	this->flags["UF"] = value;
}