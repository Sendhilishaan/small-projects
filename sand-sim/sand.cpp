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
#include <vector>

#define SCREEN_WIDTH 640
#define	SCREEN_HEIGHT 480
#define PIXEL_SIZE 5
#define FREE 0
#define OCCUPIED 1

using namespace std;

typedef struct {
	int x, y;
	bool is_moving;
	SDL_Rect rect;

} Sand;

array<array<int, SCREEN_HEIGHT>, SCREEN_WIDTH> grid = {0};
vector<Sand> sand_list;

void move_all() {
	for (Sand& grain : sand_list) {
		if (grain.y - 1 > SCREEN_HEIGHT / PIXEL_SIZE) { 
			if (grid[grain.x][grain.y - 1] == FREE) {
				grain.y -= 1;
			}
			
		}
	}
}

void sort_sand() {
	// keep the sand in the sand_list sorted in non-decreasing y values
}

int main() {
	SDL_Window *window = NULL;
	SDL_Surface *screenSurface = NULL;
	
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("Failed to init SDL");
		exit(1);
	}

	window = SDL_CreateWindow(
			"sand-simulation!",
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

			if (event.button.button == SDL_BUTTON_LEFT && event.type == SDL_MOUSEBUTTONDOWN && grid[event.button.x][event.button.y] == 1) {
				int x = event.button.x / PIXEL_SIZE;
				int y = event.button.y / PIXEL_SIZE;

				Sand newcell = {
					x,
					y,
					true,
					SDL_Rect{x, y, PIXEL_SIZE, PIXEL_SIZE}
				};

				grid[x][y] = 1;
				sand_list.push_back(newcell);
			}

			// sdl events here, once per frame

		}

		// main logic here

		SDL_UpdateWindowSurface(window);
		SDL_Delay(16); //framerate

	}

	return 1;
}

