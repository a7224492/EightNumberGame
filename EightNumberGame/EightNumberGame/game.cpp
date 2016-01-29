#include <string>
#include <ctime>

#include "game.h"
#include "utils.h"
#include "drawer.h"

#define IMG_PATH_PRE "E:/360liulanqi_downloads/"
#define BLANK cards[CARD_NUM-1]
#define KEY_INPUT_PERIOD 200

Game::Game(SDL_Surface *screen)
{
	init(screen);	
}

void Game::init(SDL_Surface *screen)
{
	this->screen = screen;
	activeCard = -1;
	oldKeyTime = 0;
	newKeyTime = 0;
	
	loadData();
	
	for (int i = 0; i < CARD_NUM; ++i)
	{
		 cards[i].posx = -1;
		 cards[i].posy = -1;
		 if (i < CARD_NUM-1)
			cards[i].img  = normalCardImg[i];
		 else
		    cards[i].img = SDL_LoadBMP(IMG_PATH_PRE"gfx/blank.bmp");
	}
	
	for (int i = 0; i < CARD_NUM; ++i)
	{
		int x = 0;
		int y = 0;
		bool isPosRight = false;

		do
		{		
			x = RandInt(0,2);
			y = RandInt(0,2);
			int j;
			for (j = 0; j < i; ++j)
			{
				if (cards[j].posx == x &&cards[j].posy == y)
				{
					break;
				}
			}
			if (i == j)
				isPosRight = true;
		} while (!isPosRight);
		cards[i].posx = x;
		cards[i].posy = y;
	}
}

void Game::getMouse(int mousex, int mousey)
{
	int posx = mousex/CARD_WIDTH;
	int posy = mousey/CARD_WIDTH;
	int i;

	for (i = 0; i < CARD_NUM; ++i)
	{
		if (cards[i].posx == posx && cards[i].posy == posy)
		{
			break;
		}
	}
	
	if (i == CARD_NUM-1)
	{
		//is blank card
		if (activeCard != -1)
		{
			//move card
			moveCard();
		}
	}else{
		activeCard = i;
		//number card is selected
		for (int i = 0; i < CARD_NUM-1; ++i)
		{
			if (i == activeCard)
				cards[i].img = activeCardImg[i];
			else
				cards[i].img = normalCardImg[i];
		}	
	}
}

void Game::getKeyDown()
{
	Uint8 *keystate = SDL_GetKeyState(0);
	if (oldKeyTime == 0)
	{
		if (keystate[SDLK_UP])
		{
			if (cards[CARD_NUM-1].posy != 2)
			{
				int i = getCardByPos(cards[CARD_NUM-1].posx, cards[CARD_NUM-1].posy+1);
				swapCardPos(cards[CARD_NUM-1], cards[i]);
			}else
				return;
		}else if (keystate[SDLK_DOWN])
		{
			if (cards[CARD_NUM-1].posy != 0)
			{
				int i = getCardByPos(cards[CARD_NUM-1].posx, cards[CARD_NUM-1].posy-1);
				swapCardPos(cards[CARD_NUM-1], cards[i]);
			}else
				return;
		}else if (keystate[SDLK_LEFT])
		{
			if (cards[CARD_NUM-1].posx != 2)
			{
				int i = getCardByPos(cards[CARD_NUM-1].posx+1, cards[CARD_NUM-1].posy);
				swapCardPos(cards[CARD_NUM-1], cards[i]);
			}else
				return;
		}else if (keystate[SDLK_RIGHT])
		{
			if (cards[CARD_NUM-1].posx != 0)
			{
				int i = getCardByPos(cards[CARD_NUM-1].posx-1, cards[CARD_NUM-1].posy);
				swapCardPos(cards[CARD_NUM-1], cards[i]);
			}else
				return;
		}
		oldKeyTime = SDL_GetTicks();
	}else{
		newKeyTime = SDL_GetTicks();
		if ((newKeyTime-oldKeyTime) >= KEY_INPUT_PERIOD)
			oldKeyTime = 0;
	}
}

void Game::loadData()
{
	for (int i = 0; i < CARD_NUM-1; ++i)
	{
		string normalImgFile = IMG_PATH_PRE"gfx/"+itos(i+1)+"_normal.bmp";
		string activeImgFile = IMG_PATH_PRE"gfx/"+itos(i+1)+"_active.bmp";
		normalCardImg[i] = SDL_LoadBMP(normalImgFile.c_str());
		activeCardImg[i] = SDL_LoadBMP(activeImgFile.c_str());
	}
}

void Game::moveCard()
{
	int activeCardx = cards[activeCard].posx;
	int activeCardy = cards[activeCard].posy;

	if (isAdjacentBlankCard(activeCardx, activeCardy))
	{
		swapCardPos(cards[activeCard], cards[CARD_NUM-1]);
	}
}

bool Game::isAdjacentBlankCard(int posx, int posy)
{
	int blankx = cards[CARD_NUM-1].posx;
	int blanky = cards[CARD_NUM-1].posy;

	if (blankx == posx && (blanky == posy+1 || blanky ==posy-1))
		return true;
	if (blanky == posy && (blankx == posx+1 || blankx ==posx-1))
		return true;

	return false;
}

void Game::swapCardPos(Card &card1, Card &card2)
{
	struct Pos
	{
		int x,y;
	};

	Pos temp;
	memcpy(&temp,&card1,sizeof(Pos));
	memcpy(&card1,&card2,sizeof(Pos));
	memcpy(&card2,&temp,sizeof(Pos));
}

bool Game::isBlankUp(const Card &card){
	return (card.posx == cards[CARD_NUM-1].posx && (card.posy+1)==cards[CARD_NUM-1].posy);
}
bool Game::isBlankDown(const Card &card){
	return (card.posx == cards[CARD_NUM-1].posx && (card.posy-1)==cards[CARD_NUM-1].posy);
}
bool Game::isBlankLeft(const Card &card){
	return (card.posy == cards[CARD_NUM-1].posy && (card.posx+1)==cards[CARD_NUM-1].posx);
}
bool Game::isBlankRight(const Card &card){
	return (card.posy == cards[CARD_NUM-1].posy && (card.posx-1)==cards[CARD_NUM-1].posx);
}

int Game::getCardByPos(int posx, int posy)
{
	for (int i = 0; i< CARD_NUM; ++i)
	{
		if (cards[i].posx == posx && cards[i].posy == posy)
		{
			return i;
		}
	}

	return -1;
}