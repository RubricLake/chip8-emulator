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
 
static int init(SDL_Window*& window, SDL_Renderer*& renderer) {
	int result = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
	if (result < 0) {
		SDL_Log("SDL init error: %s", SDL_GetError());
		return -1;
	}

	window = SDL_CreateWindow("chip-8 emulator", CHIP8_WIDTH * CHIP8_WINDOW_SCALE, CHIP8_HEIGHT * CHIP8_WINDOW_SCALE, 0);
	if (window == NULL) {
		SDL_Log("SDL init error: %s", SDL_GetError());
		return -2;
	}

	renderer = SDL_CreateRenderer(window, NULL);
	if (renderer == NULL) {
		SDL_Log("SDL_CreateRenderer: %s", SDL_GetError());
		return -3;
	}

	// Bigger Window with original resolution
	bool logic = SDL_SetRenderLogicalPresentation(renderer, CHIP8_WIDTH, CHIP8_HEIGHT, SDL_LOGICAL_PRESENTATION_INTEGER_SCALE);
	if (!logic) {
		SDL_Log("SDL_RenderLogicalPresentation: %s", SDL_GetError());
		return -4;
	}

	SDL_Log("SDL3 Initialized!");
	return 0;
}

int main(int argc, char* argv[]) {
	Chip8Context* ctx = new Chip8Context();
	Instructions ins(ctx);
	Interpreter ROM("test_opcode.ch8");
	ctx->loadRAM(ROM.opCodes, sizeof(ROM.opCodes), 0x200);
	
	// SDL INIT
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	int code = init(window, renderer);
	if (code < 0)
		return code;
	
	// Scale Window
	

	// Main Loop
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

		// Black Background
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xff);
		SDL_RenderClear(renderer);

		// Draw white pixel to center of screen
		SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
		SDL_FRect pixel = { CHIP8_WIDTH * 0.5f, CHIP8_HEIGHT * 0.5f, 1.0f, 1.0f };
		SDL_RenderFillRect(renderer, &pixel);
		SDL_RenderPresent(renderer);


		SDL_Delay(1);
	}
	
	SDL_Log("SDL3 Shutdown");
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}