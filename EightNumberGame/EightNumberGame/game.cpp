#include <string>
#include <ctime>

#include "game.h"
#include "utils.h"
#include "drawer.h"

#define IMG_PATH_PRE "C:/Users/jz/Desktop/"
#define KEY_INPUT_PERIOD 200
#define GENOMEPOP_SIZE 200
#define GENOME_LEN 800
#define CROSSOVER_RATE 0.7
#define MUTATE_RATE 0.001
#define SEED_NUM 2

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
	isRunAI = false;
	totalFitness = 0;
	solution = -1;
	bestFit = 0;
	
	loadData();
	
	for (int i = 0; i < CARD_NUM; ++i)
	{
		 cards[i].posx = -1;
		 cards[i].posy = -1;
		 if (i < CARD_NUM-1)
			cards[i].img  = normalCardImg[i];
		 else
		    cards[i].img = SDL_LoadBMP(IMG_PATH_PRE"blank.bmp");
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
	//int posx = mousex/CARD_WIDTH;
	//int posy = mousey/CARD_WIDTH;
	//int i;

	//for (i = 0; i < CARD_NUM; ++i)
	//{
	//	if (cards[i].posx == posx && cards[i].posy == posy)
	//	{
	//		break;
	//	}
	//}
	//
	//if (i == CARD_NUM-1)
	//{
	//	//is blank card
	//	if (activeCard != -1)
	//	{
	//		//move card
	//		moveCard();
	//	}
	//}else{
	//	activeCard = i;
	//	//number card is selected
	//	for (int i = 0; i < CARD_NUM-1; ++i)
	//	{
	//		if (i == activeCard)
	//			cards[i].img = activeCardImg[i];
	//		else
	//			cards[i].img = normalCardImg[i];
	//	}	
	//}
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
	if (keystate[SDLK_RETURN])
	{
		oldKeyTime = -1;
		isRunAI = true;
		startAI();
	}
}

void Game::setDrawer(Drawer *drawer)
{
	this->drawer = drawer;
}

void Game::loadData()
{
	for (int i = 0; i < CARD_NUM-1; ++i)
	{
		string normalImgFile = IMG_PATH_PRE+itos(i+1)+"_normal.bmp";
		normalCardImg[i] = SDL_LoadBMP(normalImgFile.c_str());
	}
	string backgroundImgFile = IMG_PATH_PRE"background.bmp";
	background = SDL_LoadBMP(backgroundImgFile.c_str());
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

void Game::startAI()
{
	createRandGenomePop();
	while (isRunAI)
	{
		epoch();
	}
	SDL_Delay(3000);
}

void Game::epoch()
{
	if ((solution = updateFitness()) != -1)
		return;
	vector<Genome> newGenomePop;
	for (int i = 0;i < SEED_NUM; ++i)
	{
		newGenomePop.push_back(genomePopVec[bestFit]);
	}
	while (newGenomePop.size() < GENOMEPOP_SIZE)
	{
		Genome g1 = rouletteWheelSelection();
		Genome g2 = rouletteWheelSelection();
		Genome b1,b2;
		crossover(g1,g2,b1,b2);
		mutate(b1);
		mutate(b2);
		newGenomePop.push_back(b1);
		newGenomePop.push_back(b2);
	}
	genomePopVec = newGenomePop;
}

int Game::updateFitness()
{
	int largestFitness = 0;
	totalFitness = 0;
	bestFit = 0;
	for (int i = 0; i < GENOMEPOP_SIZE; ++i)
	{
		Genome genome = genomePopVec[i];
		for (int j = 0; j < genome.bits.size(); j+=2)
		{
			int a = genome.bits[j];
			int b = genome.bits[j+1];
			int dir = b*2+a;
			switch (dir)
			{
				//up
			case 0:
				if (cards[CARD_NUM-1].posy != 0)
				{
					int cardIndex = getCardByPos(cards[CARD_NUM-1].posx, cards[CARD_NUM-1].posy-1);
					swapCardPos(cards[CARD_NUM-1], cards[cardIndex]);
				}
				break;
				//down
			case 1:
				if (cards[CARD_NUM-1].posy != 2)
				{
					int cardIndex = getCardByPos(cards[CARD_NUM-1].posx, cards[CARD_NUM-1].posy+1);
					swapCardPos(cards[CARD_NUM-1], cards[cardIndex]);
				}
				break;
				//left
			case 2:
				if (cards[CARD_NUM-1].posx != 0)
				{
					int cardIndex = getCardByPos(cards[CARD_NUM-1].posx-1, cards[CARD_NUM-1].posy);
					swapCardPos(cards[CARD_NUM-1], cards[cardIndex]);
				}
				break;
				//right
			case 3:
				if (cards[CARD_NUM-1].posx != 2)
				{
					int cardIndex = getCardByPos(cards[CARD_NUM-1].posx+1, cards[CARD_NUM-1].posy);
					swapCardPos(cards[CARD_NUM-1], cards[cardIndex]);
				}
				break;
			}
		}
		drawer->drawGame();
		double sum = 0;
		for (int j = 0; j < CARD_NUM; ++j)
		{
			sum += abs(cards[j].posy*3+cards[j].posx-j);
		}
		genomePopVec[i].fitness = sum;
		if (genomePopVec[i].fitness == 0)
		{
			isRunAI = false;
			return i;
			break;
		}
		if (largestFitness < genomePopVec[i].fitness)
		{
			largestFitness = genomePopVec[i].fitness;
		}
		
		//SDL_Delay(50);
	}
	for (int i = 0; i < GENOMEPOP_SIZE; ++i)
	{
		genomePopVec[i].fitness = largestFitness-genomePopVec[i].fitness;
		if (genomePopVec[bestFit].fitness < genomePopVec[i].fitness)
		{
			bestFit = i;
		}
		totalFitness += genomePopVec[i].fitness;
	}
	return -1;
}

void Game::createRandGenomePop()
{
	for (int i = 0; i < GENOMEPOP_SIZE; ++i)
	{
		Genome genome;
		for (int j = 0; j < GENOME_LEN; ++j)
		{
			genome.bits.push_back(RandInt(0,1));
		}
		genomePopVec.push_back(genome);
	}
}

Game::Genome& Game::rouletteWheelSelection()
{
	double slice	= RandFloat() * totalFitness;

	double total	= 0.0;

	int	selectedGenome = 0;

	for (int i=0; i< GENOMEPOP_SIZE; ++i)
	{

		total += genomePopVec[i].fitness;

		if (total > slice) 
		{
			selectedGenome = i;
			break;
		}
	}

	return genomePopVec[selectedGenome];
}

void Game::crossover(Genome &dad, Genome &mum, Genome &baby1, Genome &baby2)
{
	
	if (dad.bits == mum.bits || RandFloat() > CROSSOVER_RATE)
	{
		baby1 = dad;
		baby2 = mum;
		return;
	}
	int crossPos = RandInt(0, GENOME_LEN-1);
	for (int j = 0; j < crossPos; ++j)
	{
		baby1.bits.push_back(dad.bits[j]);
		baby2.bits.push_back(mum.bits[j]);
	}
	for (int j = crossPos; j < GENOME_LEN; ++j)
	{
		baby1.bits.push_back(mum.bits[j]);
		baby2.bits.push_back(dad.bits[j]);
	}
}

void Game::mutate(Genome &genome)
{
	for (int i = 0; i < GENOME_LEN; ++i)
	{
		if (RandFloat() < MUTATE_RATE)
		{
			genome.bits[i] = !genome.bits[i];
		}
	}
}

bool Game::isGenomeEqual(const Genome &g1, const Genome &g2)
{
	return true;
}