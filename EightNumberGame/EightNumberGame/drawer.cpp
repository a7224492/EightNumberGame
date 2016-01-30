#include "drawer.h"
#include "game.h"


Drawer::Drawer(Game *game)
{
	this->game = game;
}

void Drawer::drawGame()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	if (event.type == SDL_QUIT)
	{
		SDL_Quit();
		exit(0);
	}
	if (event.type = SDL_KEYDOWN)
	{
		if (event.key.keysym.sym == SDLK_ESCAPE)
		{
			SDL_Quit();
			exit(0);
		}
	}
	SDL_BlitSurface(game->background, NULL, game->screen, NULL);
	for (int i = 0; i < CARD_NUM; ++i)
	{
		drawCard(game->cards[i].img, game->cards[i].posx, game->cards[i].posy);
	}
	SDL_Flip(game->screen);
}

void Drawer::drawCard(SDL_Surface *cardImg, int posx, int posy)
{
	SDL_Rect rect = {posx*CARD_WIDTH, posy*CARD_WIDTH, 0, 0};
	SDL_BlitSurface(cardImg, NULL, game->screen, &rect);
}
