#include "context.h"

Chip8Context::Chip8Context() : DT(0), ST(0), I(0), PC(0), SP(0) {
	memset(RAM, 0, sizeof(RAM));
	memset(REG, 0, sizeof(REG));
	memset(stack, 0, sizeof(stack));
	memset(frameBuffer, 0, sizeof(frameBuffer));
	memset(keyboard, 0, sizeof(keyboard));

	// Load Fonts into RAM
	loadRAM(fontData, sizeof(fontData), 0x000);

}

void Chip8Context::loadRAM(u8* data, size_t dataSize, size_t startAddress) {
	if (dataSize + startAddress <= sizeof(RAM)) // Space available
		memcpy(&RAM[startAddress], data, dataSize);
	else
		std::cout << "MEMORY OUT OF BOUNDS" << std::endl;
}