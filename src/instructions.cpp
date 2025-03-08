#include "instructions.h"

void Instructions::execute(u16 opcode) {}

void Instructions::CLS(){} // 00E0
void Instructions::RET(){} // 00EE

void Instructions::JMP(u16 NNN){}			// 1NNN
void Instructions::CALLNNN(u16 NNN){}		// 2NNN
void Instructions::SEVXNN(u8 NN){}			// 3XNN
void Instructions::SNEVXNN(u8 NN){}			// 4XNN
void Instructions::SEVXVY(u8 VX, u8 VY){}	// 5XY0
void Instructions::LDVXNN(u8 VX, u8 NN){}	// 6XNN
void Instructions::ADDVXNN(u8 VX, u8 NN){}	// 7XNN

void Instructions::LDVXVY(u8 VX, u8 VY){}   // 8XY0
void Instructions::ORVXVY(u8 VX, u8 VY){}   // 8XY1
void Instructions::ANDVXVY(u8 VX, u8 VY){}  // 8XY2
void Instructions::XORVXVY(u8 VX, u8 VY){}  // 8XY3
void Instructions::ADDVXVY(u8 VX, u8 VY){}  // 8XY4
void Instructions::SUBVXVY(u8 VX, u8 VY){}  // 8XY5
void Instructions::SHRVXVY(u8 VX){}			// 8XY6
void Instructions::SUBNVXVY(u8 VX, u8 VY){} // 8XY7
void Instructions::SHLVXVY(u8 VX){}			// 8XYE
void Instructions::SNEVXVY(u8 VX, u8 VY){}	// 9XY0

void Instructions::LDINNN(u8 NNN){}					// ANNN
void Instructions::JMPV0NNN(u8 NNN){}				// BNNN
void Instructions::RNDVXNN(u8 VX, u8 NNN){}			// CXNN
void Instructions::DRWVXVYN(u8 VX, u8 VY, u8 N){}	// DXYN

void Instructions::SKPVX(u8 VX){}	// EX9E
void Instructions::SKNPVX(u8 VX){}	// EXA1
void Instructions::LDVXDT(u8 VX){}	// FX07
void Instructions::LDVXK(u8 VX){}	// FX0A
void Instructions::LDDTVX(u8 VX){}	// FX15
void Instructions::LDSTVX(u8 VX){}	// FX18
void Instructions::ADDIVX(u8 VX){}	// FX1E
void Instructions::LDFVX(u8 VX){}	// FX29 
void Instructions::LDBVX(u8 VX){}	// FX33
void Instructions::LDIVX(u8 VX){}	// FX55
void Instructions::LDVXI(u8 VX){}	// FX65