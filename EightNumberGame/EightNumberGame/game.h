#ifndef GAME_H
#define GAME_H

#include <SDL/SDL.h>

#define CARD_NUM 9
#define CARD_WIDTH 200

class Drawer;

class Game
{
public:
	Game(SDL_Surface *screen);
	void getMouse(int mousex, int mousey);
	void getKeyDown();
	
	struct Card{
		int posx,posy;
		SDL_Surface *img;
	};
	Card cards[CARD_NUM];
	SDL_Surface *screen;
	
private:
	void init(SDL_Surface *screen);
	void loadData();
	void moveCard();
	bool isAdjacentBlankCard(int posx, int posy);
	inline bool isBlankUp(const Card &card);
	inline bool isBlankDown(const Card &card);
	inline bool isBlankLeft(const Card &card);
	inline bool isBlankRight(const Card &card);
	inline void swapCardPos(Card &card1, Card &card2);
	inline int getCardByPos(int posx, int posy);
	
	SDL_Surface *normalCardImg[CARD_NUM-1];
	SDL_Surface *activeCardImg[CARD_NUM-1];
	int activeCard;
	int oldKeyTime, newKeyTime;
};

#endif