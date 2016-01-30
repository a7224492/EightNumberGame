#ifndef GAME_H
#define GAME_H

#include <SDL/SDL.h>
#include <vector>

#define CARD_NUM 9
#define CARD_WIDTH 200

using namespace std;

class Drawer;
class Genome;

class Game
{
public:
	Game(SDL_Surface *screen);
	void getMouse(int mousex, int mousey);
	void getKeyDown();
	void setDrawer(Drawer *drawer);
	
	struct Card{
		int posx,posy;
		SDL_Surface *img;
	};
	Card cards[CARD_NUM];
	SDL_Surface *screen;
	SDL_Surface *background;
	
private:
	enum DIR {UP,DOWN,LEFT,RIGHT};
	struct Genome
	{
		vector<int> bits;
		double fitness;
	};

	bool isGenomeEqual(const Genome &g1, const Genome &g2);

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

	void startAI();
	void epoch();
	int updateFitness();
	void createRandGenomePop();
	Genome& rouletteWheelSelection();
	void crossover(Genome &dad, Genome &mum, Genome &baby1, Genome &baby2);
	void mutate(Genome &genome);

	
	SDL_Surface *normalCardImg[CARD_NUM-1];
	int activeCard;
	int oldKeyTime, newKeyTime;
	vector<Genome> genomePopVec;
	bool isRunAI;
	double totalFitness;
	int solution;
	Drawer *drawer;
	int bestFit;
};

#endif