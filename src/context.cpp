#include "context.h"

Chip8Context::Chip8Context() : DT(0), ST(0), I(0), PC(0x200), SP(0) {
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

// index = col + (row * totalColumns)
void Chip8Context::drawBuffer(SDL_Renderer* renderer) const {

	for (int row = 0; row < CHIP8_HEIGHT; row++) {
		for (int col = 0; col < CHIP8_WIDTH; col++) {
			u8 color = (frameBuffer[col + (row * CHIP8_WIDTH)] == 0) ? 0 : 0xff;
			SDL_SetRenderDrawColor(renderer, color, color, color, 0xff);
			SDL_FRect pixel = { col, row, 1.0f, 1.0f };
			SDL_RenderFillRect(renderer, &pixel);
		}
	}
}