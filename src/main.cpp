#include "util.h"
#include "context.h"
#include "instructions.h"
#include "interpreter.h"

// CHIP-8 Emulator by Ethan Kigotho

/* 
HELPFUL BLOGS / REFERENCES
https://tonisagrista.com/blog/2021/chip8-spec/
http://devernay.free.fr/hacks/chip8/C8TECH10.HTM#2.4
*/ 
 
int main() {
	Chip8Context* ctx = new Chip8Context();
	Instructions ins(ctx);
	Interpreter ROM("test_opcode.ch8");
	ctx->loadRAM(ROM.opCodes, sizeof(ROM.opCodes), 0x200);

}