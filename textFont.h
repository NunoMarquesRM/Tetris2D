#include "colors.h"
#ifndef TEXTFONT_H
#define TEXTFONT_H

struct textFont {
	void drawNumber(blockNumber, int);
	void drawLetters(blockNumber, int);
	void clearScore();
	void clearLetters();
};

#endif