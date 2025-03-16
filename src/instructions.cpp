#include <SDL3/SDL.h>
#include "instructions.h"

Instructions::Instructions(Chip8Context* c) : c(c) {}

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
	c->REG[0xf] = 0;
	for (int i = 0; i < N; i++) {
		u8 byte = c->RAM[c->I + i];
		for (int j = 0; j < 8; j++) {
			int x = (c->REG[VX] + j) % CHIP8_WIDTH;
			int y = (c->REG[VY] + i) % CHIP8_HEIGHT;

			int index = x + (y * CHIP8_WIDTH);
			int before = c->frameBuffer[index];
			c->frameBuffer[index] = c->frameBuffer[index] ^ NthBit(byte, 7-j);
			if (before == 1 && c->frameBuffer[index] == 0)
				c->REG[0xf] = 1;
		}
	}
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
	SDL_Event event;
	while (true) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_EVENT_KEY_DOWN) {
				for (int i = 0; i < 16; i++) {
					if (c->keyLookup[i] == event.key.key) {
						c->REG[VX] = i;
						return;
					}
				}
			}
		}
	}
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

void Instructions::execute(u16 opcode) {
	
	switch (opcode >> 12) {
	case 0:
		if (opcode == 0x00E0)
			CLS();
		else if (opcode == 0x00EE)
			RET();
		break;
	case 1:
		JMP(opcode ^ 0x1000);
		break;
	case 2:
		CALLNNN(opcode ^ 0x2000);
		break;
	case 3:
		SEVXNN((opcode >> 8) ^ 0x30, opcode & 0xff);
		break;
	case 4:
		SNEVXNN((opcode >> 8) ^ 0x40, opcode & 0xff);
		break;
	case 5:
		SEVXVY((opcode >> 8) ^ 0x50, (opcode & 0xff) >> 4);
		break;
	case 6:
		LDVXNN((opcode >> 8) ^ 0x60, opcode & 0xff);
		break;
	case 7:
		ADDVXNN((opcode >> 8) ^ 0x70, opcode & 0xff);
		break;
	case 8:
		break;
	case 9:
		SNEVXVY((opcode >> 8) ^ 0x90, (opcode & 0xff) >> 4);
		break;
	case 0xA:
		LDINNN(opcode ^ 0xA000);
		break;
	case 0xB:
		JMPV0NNN(opcode ^ 0xB000);
		break;
	case 0xC:
		RNDVXNN((opcode >> 8) ^ 0xC0, opcode & 0xff);
		break;
	case 0xD:
		DRWVXVYN((opcode >> 8) ^ 0xD0, (opcode & 0xff) >> 4, opcode & 0xf);
		break;
	case 0xE:
		break;
	case 0xF:
		break;

	default:
		break;
	}
}
