#include"Dicionario.h"

Dicionario::Dicionario(){

	this->instrucoes["MOV1"] = "00001"; //IMEDIATO -> REG
	this->instrucoes["MOV2"] = "00010"; //REG -> REG
	this->instrucoes["MOV3"] = "00011"; //REG -> VAR
	this->instrucoes["MOV4"] = "00100"; //VAR -> REG
	this->instrucoes["MOV5"] = "00101"; //IMEDIATO->VAR
	this->instrucoes["ADD"] = "00110"; //Adiciona o valor do registrador passado com o valor contido no registrador A e armazena o resultado em A
	this->instrucoes["SUB"] = "00111"; //Subtrai o valor do registrador passado do valor contido no registrador A e armazena o resultado em A
	this->instrucoes["MUL"] = "01000"; //Multiplica o valor do registrador passado pelo valor contido no registrador A e armazena o resultado em A
	this->instrucoes["DIV"] = "01001"; //Divide o valor do registrador passado pelo valor contido no registrador A e armazena o resultado em A
	this->instrucoes["NOT"] = "01010"; //Nega bit a bit o valor contido em B
	this->instrucoes["AND"] = "01011"; //AND bit a bit do reg passado como parametro com o valor contido em B
	this->instrucoes["OR"] = "01100"; //OR bit a bit do reg passado como parametro com o valor contido em B
	this->instrucoes["PUSH"] = "01101"; //armazena o valor de cada reg na pilha
	this->instrucoes["POP"] = "01110"; //retira o valor de cada reg da pilha
	this->instrucoes["JMP"] = "01111"; //jump incondicional
	this->instrucoes["JNE"] = "10000"; //jump se a flag NZ estiver com 1 e ZF com 0
	this->instrucoes["JE"] = "10001"; //jump se a flag ZF estiver com 1 e NZ com 0
	this->instrucoes["JZ"] = "10010"; //jump se a flag ZF estiver com 1 e NZ com 0
	this->instrucoes["JNZ"] = "10011"; //jump se a flag NZ estiver com 1 e ZF com 0
	this->instrucoes["CMP"] = "11"; //Compara os dois registradores passados como parâmetros e habilita a flag ZF
	this->instrucoes["VAR"] = "0000000000000000"; //Inicia o bloco de declaração das variaveis
	this->instrucoes["INICIO"] = "0000000000000001"; //Inicia o bloco dos comandos
	this->instrucoes["FIM"] = "0000000000000010"; //Finaliza o bloco dos comandos
	

	this->registradores["MP"] = "0000"; //Memory pointer - posição de memoria do código fonte
	this->registradores["AM"] = "0001"; //Armazena endereço de memória a ser acessado
	this->registradores["FL"] = "0010"; //Armazena valores das flags
	this->registradores["A"] = "0011"; //Reg A
	this->registradores["B"] = "0100"; //Reg B
	this->registradores["C"] = "0101"; //Reg C
	this->registradores["D"] = "0110"; //Reg D
	this->registradores["PILHA"] = "0111"; //PILHA


	this->flags["ZF"] = "1000"; //Zero Flag
	this->flags["NZ"] = "1001"; //Not Zero Flag
	this->flags["UF"] = "1010"; //Underflow Flag
	this->flags["OF"] = "1011"; //Overflow Flag
}