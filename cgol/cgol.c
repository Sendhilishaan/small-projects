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
#define PIXEL_SIZE 10

#define live 1
#define dead 0

void draw_grid();
void test_rect(SDL_Window *window, SDL_Surface *surface, int x);
void load_grid(SDL_Window *window, SDL_Surface *surface);

int GRID[SCREEN_WIDTH / PIXEL_SIZE][SCREEN_HEIGHT / PIXEL_SIZE];

typedef struct {
	int x, y;
} cell;

typedef struct {
	size_t count;
	size_t capacity;
	cell *cells; // dynamic array
} cellList;

void drawGrid(SDL_Surface *surface, cellList aliveCells);
void logic(SDL_Surface *surface, cellList *aliveCells);
void addCell(SDL_Surface *surface, int x, int y, cellList *aliveCells);
void remCell(SDL_Surface *surface, int x, int y, cellList *aliveCells);

int main() {
	SDL_Window *window = NULL;
	SDL_Surface *screenSurface = NULL;
	
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("Failed to init SDL");
		exit(1);
	}

	window = SDL_CreateWindow(
			"cgol",
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

	load_grid(window, surface);
	SDL_UpdateWindowSurface(window);

	int playing = 0;

	// cellList init
	cellList aliveCells;
	aliveCells.count = 0;
	aliveCells.capacity = 10;
	aliveCells.cells = malloc(aliveCells.capacity * sizeof(cell));

	while (running) {
		while(SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				running = 0;
			}

			if (event.button.button == SDL_BUTTON_LEFT && event.type == SDL_MOUSEBUTTONDOWN) {
				addCell(surface, event.button.x, event.button.y, &aliveCells);
			}
			if (event.button.button == SDL_BUTTON_RIGHT && event.type == SDL_MOUSEBUTTONDOWN) {
				remCell(surface, event.button.x, event.button.y, &aliveCells);
			}
			if (event.key.keysym.sym == SDLK_RETURN) {
				playing = 1;
			}


		}

		//SDL_FillRect(surface, NULL, 0x00000000);
		// call the window update func here
		if (playing == 1) {
			SDL_FillRect(surface, NULL, 0x00000000);
			logic(surface, &aliveCells);
			drawGrid(surface, aliveCells);
			load_grid(window, surface);
			SDL_Delay(1000);
		}

		SDL_UpdateWindowSurface(window);
		SDL_Delay(16);

	}
	return 1;
}

void load_grid(SDL_Window *window, SDL_Surface *surface) {
	// load grid upon start for user to select init squares
	// each "cell" is 10 by 10 so 64 / 48 cells in the screen
	// we want to draw grid lines
	SDL_Rect horiz = {0, PIXEL_SIZE, SCREEN_WIDTH, 1};
	SDL_Rect *horizLine = &horiz;

	SDL_Rect vert = {PIXEL_SIZE, 0, 1, SCREEN_HEIGHT};
	SDL_Rect *vertLine = &vert;

	int step = 0;
	while (step < SCREEN_WIDTH || step < SCREEN_HEIGHT) {
		if (step < SCREEN_HEIGHT) {
			SDL_FillRect(surface, horizLine, 0x00808080);
			horizLine->y += PIXEL_SIZE;
		}
		if (step < SCREEN_WIDTH) {
			SDL_FillRect(surface, vertLine, 0x00808080);
			vertLine->x += PIXEL_SIZE;
		}
		step += PIXEL_SIZE;
	}
}

void addCell(SDL_Surface *surface, int x, int y, cellList *aliveCells) {
	// add cell on lmb click at that location
	// and to grid

	int xArr = x / PIXEL_SIZE;
	int yArr = y / PIXEL_SIZE;
	
	if (GRID[xArr][yArr] == 0) {

		int xPos = (x / 10) * 10;
		int yPos = (y / 10) * 10;

		cell newCell = {xPos, yPos};

		if (aliveCells->capacity <= aliveCells->count) {
			aliveCells->capacity *= 2;
			aliveCells->cells = realloc(aliveCells->cells, sizeof(cell) * aliveCells->capacity);
		}
		aliveCells->cells[aliveCells->count] = newCell;
		aliveCells->count++;

		SDL_Rect *cell = &(SDL_Rect){xPos + 1, yPos + 1, PIXEL_SIZE - 1, PIXEL_SIZE - 1};
		SDL_FillRect(surface, cell, 0x00ffffff);

		GRID[xArr][yArr] = 1;
	}
}
void remCell(SDL_Surface *surface, int x, int y, cellList *aliveCells) {
	// add cell on lmb click at that location
	// and to grid

	int xArr = x / PIXEL_SIZE;
	int yArr = y / PIXEL_SIZE;
	if (GRID[xArr][yArr] == 1) {

		int xPos = (x / 10) * 10;
		int yPos = (y / 10) * 10;

		SDL_Rect *cell = &(SDL_Rect){xPos + 1, yPos + 1, PIXEL_SIZE - 1, PIXEL_SIZE - 1};
		SDL_FillRect(surface, cell, 0x00000000);

		for (size_t i = 0; i < aliveCells->count; i++) {
			if (aliveCells->cells[i].x == xPos && aliveCells->cells[i].y == yPos) {
				for (size_t j = i; j < aliveCells->count - 1; j++) {
					aliveCells->cells[j] = aliveCells->cells[j + 1];
				}
				aliveCells->count--;
				break;
			}
		}

		GRID[xArr][yArr] = 0;
	}
}

void logic(SDL_Surface *surface, cellList *aliveCells) {
	static int nextGrid[SCREEN_WIDTH / PIXEL_SIZE][SCREEN_HEIGHT / PIXEL_SIZE];

	// this needs alot of optimisation, just getting logic down
	// and also can write cleaner vars
	for (int x = 0; x < SCREEN_WIDTH / PIXEL_SIZE; x++) {
		for (int y = 0; y < SCREEN_HEIGHT / PIXEL_SIZE; y++) {
			int liveCells = 0;

			for (int dx = -1; dx <= 1; dx++) {
				for (int dy = -1; dy <= 1; dy++) {
					if (dx == 0 && dy == 0) continue;
					
					int nx = x + dx;
					int ny = y + dy;
					
					if (nx >= 0 && nx < SCREEN_WIDTH / PIXEL_SIZE && 
						ny >= 0 && ny < SCREEN_HEIGHT / PIXEL_SIZE) {
						if (GRID[nx][ny] == 1) liveCells++;
					}
				}
			}
			
			if (liveCells < 2 || liveCells > 3) {
				remCell(surface, x * PIXEL_SIZE, y * PIXEL_SIZE, aliveCells);
				nextGrid[x][y] = 0;
			}
			if (liveCells == 2 || liveCells == 3) nextGrid[x][y] = GRID[x][y];
			if (liveCells == 3) {
				addCell(surface, x * PIXEL_SIZE, y * PIXEL_SIZE, aliveCells);
				nextGrid[x][y] = 1;
			}
		}
	}

	memcpy(GRID, nextGrid, sizeof(nextGrid));
}

void drawGrid(SDL_Surface *surface, cellList aliveCells) {
	for (int i = 0; i < aliveCells.count; i++) {
		SDL_Rect *cell = &(SDL_Rect){aliveCells.cells[i].x, aliveCells.cells[i].y, PIXEL_SIZE, PIXEL_SIZE};
		SDL_FillRect(surface, cell, 0x00ffffff);
	}
}
