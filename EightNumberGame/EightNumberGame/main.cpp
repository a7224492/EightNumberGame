#include <SDL/SDL.h>
#include <ctime>
#include <iostream>
#include "game.h"
#include "drawer.h"

using namespace std;

int main(int argc, char **argv)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Surface *screen = SDL_SetVideoMode(600, 620, 24, 0|SDL_SRCCOLORKEY|SDL_DOUBLEBUF);
	srand((unsigned int)time(NULL));
	
	Game game(screen);
	Drawer drawer(&game);
	game.setDrawer(&drawer);

    bool running = true;
	while (true)
	{
		SDL_Delay(20);
		SDL_Event event;
		SDL_PollEvent(&event);
		if (event.type == SDL_QUIT)
		{
			SDL_Quit();
			return 0;
		}
		if (event.button.type == SDL_MOUSEBUTTONDOWN)
		{
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				int mousex = event.button.x;
				int mousey = event.button.y;
				game.getMouse(mousex, mousey);
			}
		}
		if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_ESCAPE)
			{
				SDL_Quit();
				return 0;
			}
			game.getKeyDown();
		}

		drawer.drawGame();
	}
	
	return 0;
}