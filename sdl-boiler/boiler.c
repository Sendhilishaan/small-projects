#include <stdio.h>
#include "SDL2/SDL_events.h"
#include "SDL2/SDL_keycode.h"
#include "SDL2/SDL_mouse.h"
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <stddef.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <string.h>

#define SCREEN_WIDTH 640
#define	SCREEN_HEIGHT 480

int main() {
	SDL_Window *window = NULL;
	SDL_Surface *screenSurface = NULL;
	
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("Failed to init SDL");
		exit(1);
	}

	window = SDL_CreateWindow(
			"program name",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		SDL_WINDOW_SHOWN
	);

	if (window == NULL) {
		printf("da window break");
		exit(1);
	}
	
	SDL_Event event;
	int running = 1;
	SDL_Surface *surface = SDL_GetWindowSurface(window);


	while (running) {
		while(SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				running = 0;
			}

			// sdl events here, once per frame

		}

		// main logic here

		SDL_UpdateWindowSurface(window);
		SDL_Delay(16); //framerate

	}

	return 1;
}
