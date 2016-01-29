#ifndef DRAWER_H
#define DRAWER_H

#include <SDL/SDL.h>

class Game;

class Drawer
{
public:
	Drawer(Game *game);	
	void drawGame();
private:
	void drawCard(SDL_Surface *cardImg, int posx, int posy);	

	Game *game;		
};

#endif 