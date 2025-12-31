#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <wchar.h>

#define SCREEN_WIDTH 640
#define	SCREEN_HEIGHT 480

void init_window();
void draw_grid();

int main() {
	printf("Hello cgol\n");
	init_window();
	return 1;
}

void init_window() {
	SDL_Window *window = NULL;
	SDL_Surface *screenSurface = NULL;
	
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("Failed to init SDL");
		exit(1);
	}
	
	window = SDL_CreateWindow("cgol", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN); //|| SDL_WINDOW_MOUSE_GRABBED || SDL_WINDOW_MOUSE_CAPTURE);

	if (window == NULL) {
		printf("da window break");
		exit(1);
	}
	
	SDL_Surface *surface = SDL_GetWindowSurface(window);
	SDL_Rect test_rect = {0, 0, 50, 50};
	SDL_Rect *rect = &test_rect;
	SDL_FillRect(surface, rect, 0x00ffffff);
	SDL_UpdateWindowSurface(window);
	
	SDL_Delay(2000);

}

void load_grid() {
	// load grid upon start for user to select init squares

}
