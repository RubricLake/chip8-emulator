#include "util.h"
#include "context.h"
#include "instructions.h"

// CHIP-8 Emulator
// Made with the help of https://tonisagrista.com/blog/2021/chip8-spec/

int main() {
	Chip8Context* ctx = new Chip8Context();
	Instructions ins(ctx);
}