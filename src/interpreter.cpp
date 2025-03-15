#include "interpreter.h"

Interpreter::Interpreter() {
	memset(opCodes, 0, sizeof(opCodes));
}

Interpreter::Interpreter(string filename) {
	this->readROM(filename);
}

u8 Interpreter::readOpCode(ifstream& fs) {
	char byte;
	u8 result = 0x00;

	if (!fs.get(byte)) 
		throw std::runtime_error("INTERPRETER: COULD NOT READ BYTE FROM FILE STREAM");

	result = static_cast<u8>(byte);
	
	return result;
}

void Interpreter::readROM(string filename) {
	std::ifstream inFile("../ROM/" + filename, std::ios::binary);

	if (!inFile)
		throw std::runtime_error("INTERPRETER: COULD NOT OPEN SPECIFIED FILE " + filename);

	memset(opCodes, 0, sizeof(opCodes));

	int i = 0;
	while (inFile.peek() != EOF) {
		if (i >= 0xE00)
			throw std::runtime_error("INTERPRETER: ROM TOO LARGE FOR MEMORY");
		opCodes[i++] = readOpCode(inFile);
	}
}

u8& Interpreter::operator[](size_t i) {
	return opCodes[i];
}