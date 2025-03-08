#include "instructions.h"

Instructions::Instructions(Chip8Context* c) : c(c) {}


void Instructions::execute(u16 opcode) {}

// 00E0
void Instructions::CLS() { memset(c->frameBuffer, 0, sizeof(c->frameBuffer)); } 

// 00EE
void Instructions::RET() { 
	c->PC = c->stack[c->PC]; 
	c->PC -= 1;
} 

// 1NNN
void Instructions::JMP(u16 NNN) { c->PC = NNN; }	

// 2NNN
void Instructions::CALLNNN(u16 NNN){}		

// 3XNN
void Instructions::SEVXNN(u8 NN){}			

// 4XNN
void Instructions::SNEVXNN(u8 NN){}		

// 5XY0
void Instructions::SEVXVY(u8 VX, u8 VY){}	

// 6XNN
void Instructions::LDVXNN(u8 VX, u8 NN){}	

// 7XNN
void Instructions::ADDVXNN(u8 VX, u8 NN){}	

// 8XY0
void Instructions::LDVXVY(u8 VX, u8 VY){}   

// 8XY1
void Instructions::ORVXVY(u8 VX, u8 VY){}   

// 8XY2
void Instructions::ANDVXVY(u8 VX, u8 VY){}  

// 8XY3
void Instructions::XORVXVY(u8 VX, u8 VY){}  

// 8XY4
void Instructions::ADDVXVY(u8 VX, u8 VY){}  

// 8XY5
void Instructions::SUBVXVY(u8 VX, u8 VY){}  

// 8XY6
void Instructions::SHRVXVY(u8 VX){}			

// 8XY7
void Instructions::SUBNVXVY(u8 VX, u8 VY){} 

// 8XYE
void Instructions::SHLVXVY(u8 VX){}			

// 9XY0
void Instructions::SNEVXVY(u8 VX, u8 VY){}	

// ANNN
void Instructions::LDINNN(u8 NNN){}					

// BNNN
void Instructions::JMPV0NNN(u8 NNN){}				

// CXNN
void Instructions::RNDVXNN(u8 VX, u8 NNN){}			

// DXYN
void Instructions::DRWVXVYN(u8 VX, u8 VY, u8 N){}	

// EX9E
void Instructions::SKPVX(u8 VX){}	

// EXA1
void Instructions::SKNPVX(u8 VX){}	

// FX07
void Instructions::LDVXDT(u8 VX){}	

// FX0A
void Instructions::LDVXK(u8 VX){}	

// FX15
void Instructions::LDDTVX(u8 VX){}	

// FX18
void Instructions::LDSTVX(u8 VX){}	

// FX1E
void Instructions::ADDIVX(u8 VX){}	

// FX29 
void Instructions::LDFVX(u8 VX){}	

// FX33
void Instructions::LDBVX(u8 VX){}	

// FX55
void Instructions::LDIVX(u8 VX){}	

// FX65
void Instructions::LDVXI(u8 VX){}	