#pragma once
#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include <cstring>
#include "util.h"
#include "context.h"

// General Function Pointer
typedef void (*OpcodeFunc)();
class Instructions {
public:
	// Given an opcode, determine which operation to execute.
	Instructions(Chip8Context* ctx);
	void execute(u16 opcode);

private:
	Chip8Context* c;

	void CLS(); // 00E0
	void RET(); // 00EE

	void JMP(u16 NNN);			// 1NNN
	void CALLNNN(u16 NNN);		// 2NNN
	void SEVXNN(u8 VX, u8 NN);	// 3XNN
	void SNEVXNN(u8 VX, u8 NN);	// 4XNN
	void SEVXVY(u8 VX, u8 VY);	// 5XY0
	void LDVXNN(u8 VX, u8 NN);	// 6XNN
	void ADDVXNN(u8 VX, u8 NN); // 7XNN

	void LDVXVY(u8 VX, u8 VY);   // 8XY0
	void ORVXVY(u8 VX, u8 VY);   // 8XY1
	void ANDVXVY(u8 VX, u8 VY);  // 8XY2
	void XORVXVY(u8 VX, u8 VY);  // 8XY3
	void ADDVXVY(u8 VX, u8 VY);  // 8XY4
	void SUBVXVY(u8 VX, u8 VY);  // 8XY5
	void SHRVXVY(u8 VX);		 // 8XY6
	void SUBNVXVY(u8 VX, u8 VY); // 8XY7
	void SHLVXVY(u8 VX);		 // 8XYE
	void SNEVXVY(u8 VX, u8 VY);	 // 9XY0
	
	void LDINNN(u8 NNN);			   // ANNN
	void JMPV0NNN(u8 NNN);			   // BNNN
	void RNDVXNN(u8 VX, u8 NNN);	   // CXNN
	void DRWVXVYN(u8 VX, u8 VY, u8 N); // DXYN

	void SKPVX(u8 VX);  // EX9E
	void SKNPVX(u8 VX); // EXA1
	void LDVXDT(u8 VX); // FX07
	void LDVXK(u8 VX);  // FX0A
	void LDDTVX(u8 VX); // FX15
	void LDSTVX(u8 VX); // FX18
	void ADDIVX(u8 VX); // FX1E
	void LDFVX(u8 VX);  // FX29 
	void LDBVX(u8 VX);  // FX33
	void LDIVX(u8 VX);	// FX55
	void LDVXI(u8 VX);	// FX65
};	

#endif