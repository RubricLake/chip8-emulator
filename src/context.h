#pragma once 
#ifndef CONTEXT_H
#define CONTEXT_H

#include <iostream>
#include <cstring>
#include <SDL3/SDL.h>
#include "util.h"

class Chip8Context {
public:
	// [0x000 - 0x200) are for the system
	// [0x200 - 0xFFF) are for user programs (put code from ROMs here)
	u8 RAM[kilobytes(4)];

	// General Purpose Registers
	u8 REG[16];

	// FIFO Memory
	u16 stack[16];

	// The Screen to be drawn to
	// Pixels are on or off
	b8 frameBuffer[CHIP8_HEIGHT * CHIP8_WIDTH];

	// Stores if a key is being pressed
	// 1, 2, 3, 4
	// Q, W, E, R
	// A, S, D, F
	// Z, X, C, V
	b8 keyboard[16];

	// Special Purpose Reigsters
	u8 DT;  // Delay Timer
	u8 ST;  // Sound Timer
	u16 I;  // Index Register
	u16 PC; // Program Counter
	u16 SP; // Stack Pointer

	// Constructs a context
	// Loads font data, and zeros out others.
	Chip8Context();

	// Given an array of data
	void loadRAM(u8* data, size_t dataSize, size_t startAddress);

	// Draw the frame buffer to the screen
	void drawBuffer(SDL_Renderer* renderer) const;

};
#endif

