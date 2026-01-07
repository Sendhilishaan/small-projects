#include "SDL2/SDL.h"
#include "SDL2/SDL_surface.h"
#include "SDL2/SDL_video.h"
#include <arm_neon.h>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <stdint.h>
#include <vector>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define PIXEL_SIZE 5

using namespace std;

class Particle {
	public:
		
		uint32_t x, y;
		uint8_t color;
		
		Particle(): x(0), y(0), color(0) {}

		Particle(uint64_t xCord, uint64_t yCord): x(xCord), y(yCord) {}

		virtual void tick() = 0;

};

class Sand: public Particle {

	public:

		Sand(uint64_t x, uint64_t y) : Particle(x, y) {
			color = 1;
		}
	
		virtual void tick() {
			x -= 1;
			y -= 1;
		}
};

vector<vector<Particle>> grid(SCREEN_WIDTH, vector<Particle>(SCREEN_HEIGHT));
vector<vector<uint64_t> > liveParticles;

int main() {
	cout << "hi";
	
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
	uint8_t running = 1;
	SDL_Surface *surface = SDL_GetWindowSurface(window);

	SDL_UpdateWindowSurface(window);

	while (running) {
		while(SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				SDL_Quit();
				running = 0;
			}
		}
	}

	return 0;
}
