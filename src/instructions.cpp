#include "instructions.h"

Instructions::Instructions(Chip8Context* c) : c(c) {}


void Instructions::execute(u16 opcode) {}

// 00E0
void Instructions::CLS() { 
	memset(c->frameBuffer, 0, sizeof(c->frameBuffer));
} 

// 00EE
void Instructions::RET() { 
	c->PC = c->stack[c->SP]; 
	c->SP -= 1;
} 

// 1NNN
void Instructions::JMP(u16 NNN) {
	c->PC = NNN; 
}	

// 2NNN
void Instructions::CALLNNN(u16 NNN){
	c->SP += 1;
	c->stack[c->SP] = c->PC;
	c->PC = NNN;
}		

// 3XNN
void Instructions::SEVXNN(u8 VX, u8 NN) {
	if (c->REG[VX] == NN)
		c->PC += 2;
}			

// 4XNN
void Instructions::SNEVXNN(u8 VX, u8 NN) {
	if (c->REG[VX] != NN)
		c->PC += 2;
}		

// 5XY0
void Instructions::SEVXVY(u8 VX, u8 VY) { 
	if (c->REG[VX] == c->REG[VY])
		c->PC += 2;
}	

// 6XNN
void Instructions::LDVXNN(u8 VX, u8 NN) {
	c->REG[VX] = NN;
}	

// 7XNN
void Instructions::ADDVXNN(u8 VX, u8 NN) {
	c->REG[VX] += NN;
}	

// 8XY0
void Instructions::LDVXVY(u8 VX, u8 VY) {
	c->REG[VX] = c->REG[VY];
}   

// 8XY1
void Instructions::ORVXVY(u8 VX, u8 VY) {
	c->REG[VX] = c->REG[VX] | c->REG[VY];
}   

// 8XY2
void Instructions::ANDVXVY(u8 VX, u8 VY) {
	c->REG[VX] = c->REG[VX] & c->REG[VY];
}  

// 8XY3
void Instructions::XORVXVY(u8 VX, u8 VY) {
	c->REG[VX] = c->REG[VX] ^ c->REG[VY];
}  

// 8XY4
void Instructions::ADDVXVY(u8 VX, u8 VY) {
	if (c->REG[VX] + c->REG[VY] > 0xFF)
		c->REG[0xF] = 1;
	else
		c->REG[0xF] = 0;
	
	c->REG[VX] += c->REG[VY];
}  

// 8XY5
void Instructions::SUBVXVY(u8 VX, u8 VY) {
	if (c->REG[VX] > c->REG[VY])
		c->REG[0xF] = 1;
	else
		c->REG[0xF] = 0;

	c->REG[VX] = c->REG[VX] - c->REG[VY];
}  

// 8XY6
void Instructions::SHRVXVY(u8 VX) {
	c->REG[0xF] = c->REG[VX] & 0x01;
	c->REG[VX] /= 2;
}			

// 8XY7
void Instructions::SUBNVXVY(u8 VX, u8 VY) {
	if (c->REG[VY] > c->REG[VX])
		c->REG[0xF] = 1;
	else
		c->REG[0xF] = 0;

	c->REG[VX] = c->REG[VY] - c->REG[VX];
} 

// 8XYE
void Instructions::SHLVXVY(u8 VX) {
	c->REG[0xF] = (c->REG[VX] & 0x80) >> 7;
	c->REG[VX] = c->REG[VX] << 1;
}			

// 9XY0
void Instructions::SNEVXVY(u8 VX, u8 VY) {
	if (c->REG[VX] != c->REG[VY])
		c->PC += 2;
}	

// ANNN
void Instructions::LDINNN(u8 NNN) {
	c->I = NNN;
}					

// BNNN
void Instructions::JMPV0NNN(u8 NNN) {
	c->PC = NNN + c->REG[0];
}				

// CXNN
void Instructions::RNDVXNN(u8 VX, u8 NN) {
	c->REG[VX] = (rand() % 255) & NN;
}			

// DXYN (draw xor)
void Instructions::DRWVXVYN(u8 VX, u8 VY, u8 N) {
	
}	

// EX9E
void Instructions::SKPVX(u8 VX) {
	if (c->keyboard[c->REG[VX]] == 1)
		c->PC += 2;
}	

// EXA1
void Instructions::SKNPVX(u8 VX) {
	if (c->keyboard[c->REG[VX]] == 0)
		c->PC += 2;
}	

// FX07
void Instructions::LDVXDT(u8 VX) {
	c->REG[VX] = c->DT;
}	

// FX0A (wait for input)
void Instructions::LDVXK(u8 VX) {
	
}	

// FX15
void Instructions::LDDTVX(u8 VX) {
	c->DT = c->REG[VX];
}	

// FX18
void Instructions::LDSTVX(u8 VX) {
	c->ST = c->REG[VX];
}	

// FX1E
void Instructions::ADDIVX(u8 VX) {
	c->I += c->REG[VX];
}	

// FX29 
void Instructions::LDFVX(u8 VX) {
	c->I = c->REG[VX] * 0x05;
}	

// FX33
void Instructions::LDBVX(u8 VX) {}	

// FX55
void Instructions::LDIVX(u8 VX) {
	for (size_t i = 0; i < VX; i++)
		c->RAM[c->I + i] = c->REG[i];
	
}	

// FX65
void Instructions::LDVXI(u8 VX) {
	for (size_t i = 0; i < VX; i++)
		c->REG[i] = c->RAM[c->I + i];
	
}	