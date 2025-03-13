#pragma once
#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <fstream>
#include <exception>
#include <string>
#include "util.h"

using std::ifstream;
using std::string;

class Interpreter {
public:
	u8 opCodes[0xE00];
	Interpreter();
	Interpreter(string filename);

	void readROM(string filename);
	u8& operator[](size_t i);
private:
	u8 readOpCode(ifstream& fs);
};


#endif