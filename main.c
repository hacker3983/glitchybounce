#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#define BALL_AVERAGESPEED 10 // 10 centimeters
#define BALL_MINMOVETIME 10 // 10 milliseconds per movement (minimum)
#define BALL_MAXMOVETIME 100 // 90 milliseconds per movement (maximum)
#define BALL_INCREASESPEEDMS 50 // Decrease ball movement speed every 50 milliseconds
#define BALL_

int main(int argc, char** argv) {
	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_PNG);
	int quit = 0, width = 0, height = 0;
	SDL_Event e;
	SDL_Window* window = SDL_CreateWindow("Glitchy Bounce", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			900, 600, SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_Texture* ball_texture = IMG_LoadTexture(renderer, "basketball.png");
	SDL_Rect ball_canvas = {0, 0, 40, 40};
	int ball_speed = BALL_AVERAGESPEED, ball_velx = BALL_AVERAGESPEED, ball_vely = BALL_AVERAGESPEED,
	    ball_movetime = BALL_MINMOVETIME, ball_movespeed_timeout = 0;
	Uint64 target_time = 0, ball_movetimeout = 0;
	SDL_SetTextureColorMod(ball_texture, 0xff, 0xff, 0xff);
	while(!quit) {
		while(SDL_PollEvent(&e)) {
			if(e.type == SDL_QUIT) {
				quit = 1; break;
			}
		}
		SDL_GetWindowSize(window, &width, &height);
		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
		SDL_RenderClear(renderer);
		if(!target_time) {
			target_time = SDL_GetTicks64() + ball_movetime;
		}
		if(!ball_movespeed_timeout) {
			ball_movespeed_timeout = SDL_GetTicks64() + BALL_INCREASESPEEDMS;
		}
		SDL_GetWindowSize(window, &width, &height);
		SDL_RenderCopy(renderer, ball_texture, NULL, &ball_canvas);
		if(SDL_GetTicks64() >= target_time) {	
			ball_canvas.x += ball_velx; ball_canvas.y += ball_vely;
			if(ball_canvas.x <= 1) {
				ball_velx = ball_speed;
			} else if(ball_canvas.x >= width - ball_canvas.w) {
				ball_velx = -ball_speed;
			}
			if(ball_canvas.y >= height - ball_canvas.h) {
				ball_vely = -ball_speed;
			} else if(ball_canvas.y <= 1) {
				ball_vely = ball_speed;
			}
			target_time = 0;
		}

		if(SDL_GetTicks64() >= ball_movespeed_timeout) {
			ball_movetime += BALL_AVERAGESPEED;
			ball_speed += BALL_AVERAGESPEED;
			ball_movespeed_timeout = 0;
		}
		if(ball_movetime >= BALL_MAXMOVETIME) {
			ball_movetime = BALL_MINMOVETIME;
			target_time = 0;
		}
		if(ball_speed > 40) {
			ball_speed = BALL_AVERAGESPEED;
		}
		SDL_RenderPresent(renderer);
	}
	SDL_DestroyTexture(ball_texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	IMG_Quit();
	SDL_Quit();
	return 0;
}
