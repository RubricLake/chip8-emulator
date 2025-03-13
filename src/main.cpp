#include "util.h"
#include "context.h"
#include "instructions.h"
#include "interpreter.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

// CHIP-8 Emulator by Ethan Kigotho

/* 
HELPFUL BLOGS / REFERENCES
https://tonisagrista.com/blog/2021/chip8-spec/
http://devernay.free.fr/hacks/chip8/C8TECH10.HTM#2.4
*/ 
 
int main(int argc, char* argv[]) {
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	
	int result = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
	if (result < 0) {
		SDL_Log("SDL init error: %s", SDL_GetError());
		return -1;
	}
	
	window = SDL_CreateWindow("chip-8 emulator", 64, 32, 0);
	if (window == NULL) {
		SDL_Log("SDL init error: %s", SDL_GetError());
		return -2;
	}
	
	renderer = SDL_CreateRenderer(window, NULL);
	if (renderer == NULL) {
		SDL_Log("SDL_CreateRenderer: %s", SDL_GetError());
		return -3;
	}
	
	SDL_Log("SDL3 Initialized!");
	
	SDL_Event event;
	int quit = 0;
	while (!quit) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_EVENT_QUIT:
				SDL_Log("SDL3 event quit");
				quit = 1;
				break;
			}
		}
	
		SDL_SetRenderDrawColor(renderer, 0, 0, 0xff, 0xff);
		SDL_RenderClear(renderer);
		SDL_RenderPresent(renderer);
		SDL_Delay(1);
	}
	
	SDL_Log("SDL3 Shutdown");
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	Chip8Context* ctx = new Chip8Context();
	Instructions ins(ctx);
	Interpreter ROM("test_opcode.ch8");
	ctx->loadRAM(ROM.opCodes, sizeof(ROM.opCodes), 0x200);

}