#pragma once
#ifndef UTIL_H
#define UTIL_H

// Defines
typedef unsigned char u8;
typedef unsigned short u16;
typedef u8 b8;

// Font Data
extern u8 fontData[80];

// Returns amount of bytes in n kilobytes
constexpr int kilobytes(int n) { return n * 1024; }

#endif