#include "Decoder.h"

Decoder::Decoder()
{
}

Decoder::~Decoder()
{
}

string Decoder::DecToBin(int number)
{
	if (number == 0) return "0";
	if (number == 1) return "1";

	if (number % 2 == 0)
		return DecToBin(number / 2) + "0";
	else
		return DecToBin(number / 2) + "1";
}

void Decoder::decodeElement(string iq, Memoria *m, busInt *busI, Registers *Reg, ULA *ula) {
	this->value = iq;

	if (this->value.substr(0, 5) == "00001") {//MOV1 IMEDIATO -> REG

		int i = 0;
		string a = "";

		busI->printBusInt();
		Reg->printRegs();
		i = this->bin2dec(this->value.substr(9, 7).c_str());
		a = this->DecToBin(i);
		busI->setDataBus(a);
		busI->printBusInt();
		Reg->setRegisterValue(this->value.substr(5, 4), busI->getDataBus(), m);
		busI->clearBus();
		busI->printBusInt();
		Reg->printRegs();

		return;
	}

	if (this->value.substr(0, 5) == "00010") {//MOV2 REG -> REG

		busI->printBusInt();
		Reg->printRegs();
		busI->setDataBus(this->DecToBin(Reg->getRegisterValue(this->value.substr(5, 4))));
		busI->printBusInt();
		Reg->setRegisterValue(this->value.substr(12, 4), busI->getDataBus(), m);
		busI->clearBus();
		busI->printBusInt();
		Reg->printRegs();

		return;
	}

	if (this->value.substr(0, 5) == "00011") {//MOV3 REG -> VAR

		busI->printBusInt();
		Reg->printRegs();
		busI->setDataBus(this->DecToBin(Reg->getRegisterValue(this->value.substr(5, 4))));
		busI->printBusInt();
		m->setValue(this->value.substr(9, 7), busI->getDataBus());
		busI->clearBus();
		busI->printBusInt();
		Reg->printRegs();

		return;
	}

	if (this->value.substr(0, 5) == "00100") {//MOV4 VAR -> REG

		int i = 15;
		string a = "";

		busI->printBusInt();
		Reg->printRegs();
		while (i > 0) {
			a = this->value.at(i) + a;
			if (!m->isReserved(a)) {
				busI->setDataBus(m->getValue(a));
				break;
			}
			i -= 1;
		}
		a = "";
		//busI->setDataBus(m->getValue(this->value.substr(5, 7)));
		busI->printBusInt();
		Reg->setRegisterValue(this->value.substr(5, 4), busI->getDataBus(), m);
		busI->clearBus();
		busI->printBusInt();
		Reg->printRegs();

		return;
	}

	if (this->value.substr(0, 5) == "00101") {//MOV5 - IMEDIATO -> VARIAVEL

		busI->printBusInt();
		Reg->printRegs();
		busI->setDataBus(this->value.substr(5, 4));
		busI->printBusInt();
		m->setValue(this->value.substr(9, 7), busI->getDataBus());
		busI->clearBus();
		busI->printBusInt();
		Reg->printRegs();

		return;
	}

	if (this->value.substr(0, 5) == "00110") {//ADD

		busI->printBusInt();
		Reg->printRegs();
		busI->setDataBus(this->DecToBin(Reg->getRegisterValue(this->value.substr(12, 4))));
		busI->printBusInt();

		ula->add(this->value.substr(12, 4), busI->getDataBus(), m, Reg);
		busI->clearBus();

		busI->printBusInt();
		Reg->printRegs();
		return;
	}

	if (this->value.substr(0, 5) == "00111") {//SUB

		busI->printBusInt();
		Reg->printRegs();
		busI->setDataBus(this->DecToBin(Reg->getRegisterValue(this->value.substr(12, 4))));
		busI->printBusInt();

		ula->sub(this->value.substr(12, 4), busI->getDataBus(), m, Reg);
		busI->clearBus();

		busI->printBusInt();
		Reg->printRegs();
		return;
	}

	if (this->value.substr(0, 5) == "01000") {//MUL

		busI->printBusInt();
		Reg->printRegs();
		busI->setDataBus(this->DecToBin(Reg->getRegisterValue(this->value.substr(5, 4))));
		busI->printBusInt();

		ula->setTempReg1(busI->getDataBus());
		busI->clearBus();

		busI->printBusInt();

		busI->setDataBus(this->DecToBin(Reg->getRegisterValue(this->value.substr(12, 4))));
		busI->printBusInt();

		ula->setTempReg2(busI->getDataBus());
		busI->clearBus();

		ula->mul(this->value.substr(5, 4), m, Reg);

		busI->printBusInt();
		Reg->printRegs();

		return;
	}

	if (this->value.substr(0, 5) == "01001") {//DIV

		busI->printBusInt();
		Reg->printRegs();
		busI->setDataBus(this->DecToBin(Reg->getRegisterValue(this->value.substr(5, 4))));
		busI->printBusInt();

		ula->setTempReg1(busI->getDataBus());
		busI->clearBus();

		busI->printBusInt();

		busI->setDataBus(this->DecToBin(Reg->getRegisterValue(this->value.substr(12, 4))));
		busI->printBusInt();

		ula->setTempReg2(busI->getDataBus());
		busI->clearBus();

		ula->div(this->value.substr(5, 4), m, Reg);

		busI->printBusInt();
		Reg->printRegs();

		return;
	}

	if (this->value.substr(0, 5) == "01010") {//NOT

		busI->printBusInt();
		Reg->printRegs();
		busI->setDataBus(Reg->getRegisterLogValue(this->value.substr(12, 4)));
		busI->printBusInt();

		ula->setTempReg1(busI->getDataBus());
		busI->clearBus();

		busI->printBusInt();

		Reg->printRegsLog();

		ula->not(this->value.substr(12, 4), m, Reg);

		busI->printBusInt();
		Reg->printRegsLog();

		return;
	}

	if (this->value.substr(0, 5) == "01011") {//AND

		busI->printBusInt();
		Reg->printRegs();
		busI->setDataBus(Reg->getRegisterLogValue(this->value.substr(5, 4)));
		busI->printBusInt();

		ula->setTempReg1(busI->getDataBus());
		busI->clearBus();

		busI->printBusInt();

		busI->setDataBus(Reg->getRegisterLogValue(this->value.substr(12, 4)));
		busI->printBusInt();

		ula->setTempReg2(busI->getDataBus());
		busI->clearBus();

		busI->printBusInt();
		Reg->printRegsLog();

		ula->and(this->value.substr(5, 4), m, Reg);

		busI->printBusInt();
		Reg->printRegsLog();

		return;
	}

	if (this->value.substr(0, 5) == "01100") {//OR

		busI->printBusInt();
		Reg->printRegs();
		busI->setDataBus(Reg->getRegisterLogValue(this->value.substr(5, 4)));
		busI->printBusInt();

		ula->setTempReg1(busI->getDataBus());
		busI->clearBus();

		busI->printBusInt();

		busI->setDataBus(Reg->getRegisterLogValue(this->value.substr(12, 4)));
		busI->printBusInt();

		ula->setTempReg2(busI->getDataBus());
		busI->clearBus();

		busI->printBusInt();
		Reg->printRegsLog();

		ula->or(this->value.substr(5, 4), m, Reg);

		busI->printBusInt();
		Reg->printRegsLog();

		return;
	}

	if (this->value.substr(0, 5) == "01101") {//PUSH

		return;
	}

	if (this->value.substr(0, 5) == "01110") {//POP

		return;
	}

	if (this->value.substr(0, 5) == "01111") {//JMP

		return;
	}

	if (this->value.substr(0, 5) == "10000") {//JNE

		return;
	}

	if (this->value.substr(0, 5) == "10001") {//JE

		return;
	}

	if (this->value.substr(0, 5) == "10010") {//JZ

		return;
	}

	if (this->value.substr(0, 5) == "10011") {//JNZ

		return;
	}

	if (this->value.substr(0, 2) == "11") {//CMP

		busI->printBusInt();
		Reg->printRegs();
		busI->setDataBus(this->DecToBin(Reg->getRegisterValue(this->value.substr(2, 4))));
		busI->printBusInt();

		ula->setTempReg1(busI->getDataBus());
		busI->clearBus();

		busI->printBusInt();

		busI->setDataBus(this->DecToBin(Reg->getRegisterValue(this->value.substr(12, 4))));
		busI->printBusInt();

		ula->setTempReg2(busI->getDataBus());
		busI->clearBus();

		/*if (ula->sutracao() < 0){
		Reg->setZeroFlag(1);
		}
		else{
		Reg->setZeroFlag(0);
		}*/
		return;
	}
}