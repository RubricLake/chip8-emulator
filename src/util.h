#pragma once
#ifndef UTIL_H
#define UTIL_H

// Defines
typedef unsigned char u8;
typedef unsigned short u16;
typedef u8 b8;

// Font Data
extern u8 fontData[80];

// Constants
const int CHIP8_WIDTH = 64;
const int CHIP8_HEIGHT = 32;
const int CHIP8_WINDOW_SCALE = 10;

// Returns amount of bytes in n kilobytes
constexpr int kilobytes(int n) { return n * 1024; }

// Returns the Most Significant Bit (Left-Most)
static b8 MSB(u8 byte) { return b8(byte & 128); }

// Returns the Least Significant Bit (Right-Most)
static b8 LSB(u8 byte) { return b8(byte & 1); }

// Returns the Nth bit.
// The 0th Bit is the least signfiicant.
static b8 NthBit(u8 byte, int n) { return b8((byte >> n) & 1); }
#endif