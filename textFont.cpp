#include "textFont.h"

extern blockNumber firstNumber[25];
extern blockNumber secondNumber[25];
extern blockNumber thirdNumber[25];
extern blockNumber fourthNumber[25];
extern blockNumber fifthNumber[25];
extern blockNumber sixthNumber[25];

extern blockNumber lR[25];
extern blockNumber lO[25];
extern blockNumber lW[25];
extern blockNumber lS[25];
extern blockNumber rowFirstNumber[25];
extern blockNumber rowSecondNumber[25];
extern blockNumber rowThirdNumber[25];

/* ------------------------ Numbers ------------------------ */
const int number0[25] = {
	0, 1, 1, 1, 1,
	0, 1, 0, 0, 1,
	0, 1, 0, 0, 1,
	0, 1, 0, 0, 1,
	0, 1, 1, 1, 1
};
const int number1[25] = {
	0, 0, 0, 0, 2,
	0, 0, 0, 2, 2,
	0, 0, 2, 0, 2,
	0, 0, 0, 0, 2,
	0, 0, 0, 0, 2
};
const int number2[25] = {
	0, 3, 3, 3, 3,
	0, 0, 0, 0, 3,
	0, 3, 3, 3, 3,
	0, 3, 0, 0, 0,
	0, 3, 3, 3, 3
};
const int number3[25] = {
	0, 4, 4, 4, 4,
	0, 0, 0, 0, 4,
	0, 0, 4, 4, 4,
	0, 0, 0, 0, 4,
	0, 4, 4, 4, 4
};
const int number4[25] = {
	0, 5, 0, 0, 5,
	0, 5, 0, 0, 5,
	0, 5, 5, 5, 5,
	0, 0, 0, 0, 5,
	0, 0, 0, 0, 5
};
const int number5[25] = {
	0, 6, 6, 6, 6,
	0, 6, 0, 0, 0,
	0, 6, 6, 6, 6,
	0, 0, 0, 0, 6,
	0, 6, 6, 6, 6
};
const int number6[25] = {
	0, 7, 7, 7, 0,
	0, 7, 0, 0, 0,
	0, 7, 7, 7, 7,
	0, 7, 0, 0, 7,
	0, 7, 7, 7, 7
};
const int number7[25] = {
	0, 8, 8, 8, 8,
	0, 0, 0, 0, 8,
	0, 0, 0, 8, 0,
	0, 0, 8, 0, 0,
	0, 8, 0, 0, 0
};
const int number8[25] = {
	0, 9, 9, 9, 9,
	0, 9, 0, 0, 9,
	0, 9, 9, 9, 9,
	0, 9, 0, 0, 9,
	0, 9, 9, 9, 9
};
const int number9[25] = {
	0, 10, 10, 10, 10,
	0, 10,  0,  0, 10,
	0, 10, 10, 10, 10,
	0,  0,  0,  0, 10,
	0,  0,  0,  0, 10
};

const int letterR[25] = {
	0, 0, 11, 11, 11,
	0, 0, 11,  0, 11,
	0, 0, 11, 11, 11,
	0, 0, 11, 11,  0,
	0, 0, 11,  0, 11
};
const int letterO[25] = {
	0, 0, 12, 12, 12,
	0, 0, 12,  0, 12,
	0, 0, 12,  0, 12,
	0, 0, 12,  0, 12,
	0, 0, 12, 12, 12
};
const int letterW[25] = {
	13,  0,  0,  0, 13,
	13,  0,  0,  0, 13,
	13,  0, 13,  0, 13,
	13, 13,  0, 13, 13,
	13,  0,  0,  0, 13
};
const int letterS[25] = {
	14, 14, 14, 0,  0,
	14,  0,  0, 0, 14,
	14, 14, 14, 0,  0,
	 0,  0, 14, 0, 14,
	14, 14, 14, 0,  0,
};

void textFont::drawNumber(blockNumber type, int size)
{
	switch (type)
	{
		case blockNumber::NA:
		{
			break;
		}
		case blockNumber::N0:
		{
			if (size == 1) {
				for (int i = 0; i < 25; i++){
					firstNumber[i] = (blockNumber)number0[i];
				}
			}
			if (size == 2) {
				for (int i = 0; i < 25; i++) {
					secondNumber[i] = (blockNumber)number0[i];
				}
			}
			if (size == 3) {
				for (int i = 0; i < 25; i++) {
					thirdNumber[i] = (blockNumber)number0[i];
				}
			}
			if (size == 4) {
				for (int i = 0; i < 25; i++) {
					fourthNumber[i] = (blockNumber)number0[i];
				}
			}
			if (size == 5) {
				for (int i = 0; i < 25; i++) {
					fifthNumber[i] = (blockNumber)number0[i];
				}
			}
			if (size == 6) {
				for (int i = 0; i < 25; i++) {
					sixthNumber[i] = (blockNumber)number0[i];
				}
			}
			break;
		}
		case blockNumber::N1:
		{
			if (size == 1) {
				for (int i = 0; i < 25; i++) {
					firstNumber[i] = (blockNumber)number1[i];
				}
			}
			if (size == 2) {
				for (int i = 0; i < 25; i++) {
					secondNumber[i] = (blockNumber)number1[i];
				}
			}
			if (size == 3) {
				for (int i = 0; i < 25; i++) {
					thirdNumber[i] = (blockNumber)number1[i];
				}
			}
			if (size == 4) {
				for (int i = 0; i < 25; i++) {
					fourthNumber[i] = (blockNumber)number1[i];
				}
			}
			if (size == 5) {
				for (int i = 0; i < 25; i++) {
					fifthNumber[i] = (blockNumber)number1[i];
				}
			}
			if (size == 6) {
				for (int i = 0; i < 25; i++) {
					sixthNumber[i] = (blockNumber)number1[i];
				}
			}
			break;
		}
		case blockNumber::N2:
		{
			if (size == 1) {
				for (int i = 0; i < 25; i++) {
					firstNumber[i] = (blockNumber)number2[i];
				}
			}
			if (size == 2) {
				for (int i = 0; i < 25; i++) {
					secondNumber[i] = (blockNumber)number2[i];
				}
			}
			if (size == 3) {
				for (int i = 0; i < 25; i++) {
					thirdNumber[i] = (blockNumber)number2[i];
				}
			}
			if (size == 4) {
				for (int i = 0; i < 25; i++) {
					fourthNumber[i] = (blockNumber)number2[i];
				}
			}
			if (size == 5) {
				for (int i = 0; i < 25; i++) {
					fifthNumber[i] = (blockNumber)number2[i];
				}
			}
			if (size == 6) {
				for (int i = 0; i < 25; i++) {
					sixthNumber[i] = (blockNumber)number2[i];
				}
			}
			break;
		}
		case blockNumber::N3:
		{
			if (size == 1) {
				for (int i = 0; i < 25; i++) {
					firstNumber[i] = (blockNumber)number3[i];
				}
			}
			if (size == 2) {
				for (int i = 0; i < 25; i++) {
					secondNumber[i] = (blockNumber)number3[i];
				}
			}
			if (size == 3) {
				for (int i = 0; i < 25; i++) {
					thirdNumber[i] = (blockNumber)number3[i];
				}
			}
			if (size == 4) {
				for (int i = 0; i < 25; i++) {
					fourthNumber[i] = (blockNumber)number3[i];
				}
			}
			if (size == 5) {
				for (int i = 0; i < 25; i++) {
					fifthNumber[i] = (blockNumber)number3[i];
				}
			}
			if (size == 6) {
				for (int i = 0; i < 25; i++) {
					sixthNumber[i] = (blockNumber)number3[i];
				}
			}
			break;
		}
		case blockNumber::N4:
		{
			if (size == 1) {
				for (int i = 0; i < 25; i++) {
					firstNumber[i] = (blockNumber)number4[i];
				}
			}
			if (size == 2) {
				for (int i = 0; i < 25; i++) {
					secondNumber[i] = (blockNumber)number4[i];
				}
			}
			if (size == 3) {
				for (int i = 0; i < 25; i++) {
					thirdNumber[i] = (blockNumber)number4[i];
				}
			}
			if (size == 4) {
				for (int i = 0; i < 25; i++) {
					fourthNumber[i] = (blockNumber)number4[i];
				}
			}
			if (size == 5) {
				for (int i = 0; i < 25; i++) {
					fifthNumber[i] = (blockNumber)number4[i];
				}
			}
			if (size == 6) {
				for (int i = 0; i < 25; i++) {
					sixthNumber[i] = (blockNumber)number4[i];
				}
			}
			break;
		}
		case blockNumber::N5:
		{
			if (size == 1) {
				for (int i = 0; i < 25; i++) {
					firstNumber[i] = (blockNumber)number5[i];
				}
			}
			if (size == 2) {
				for (int i = 0; i < 25; i++) {
					secondNumber[i] = (blockNumber)number5[i];
				}
			}
			if (size == 3) {
				for (int i = 0; i < 25; i++) {
					thirdNumber[i] = (blockNumber)number5[i];
				}
			}
			if (size == 4) {
				for (int i = 0; i < 25; i++) {
					fourthNumber[i] = (blockNumber)number5[i];
				}
			}
			if (size == 5) {
				for (int i = 0; i < 25; i++) {
					fifthNumber[i] = (blockNumber)number5[i];
				}
			}
			if (size == 6) {
				for (int i = 0; i < 25; i++) {
					sixthNumber[i] = (blockNumber)number5[i];
				}
			}
			break;
		}
		case blockNumber::N6:
		{
			if (size == 1) {
				for (int i = 0; i < 25; i++) {
					firstNumber[i] = (blockNumber)number6[i];
				}
			}
			if (size == 2) {
				for (int i = 0; i < 25; i++) {
					secondNumber[i] = (blockNumber)number6[i];
				}
			}
			if (size == 3) {
				for (int i = 0; i < 25; i++) {
					thirdNumber[i] = (blockNumber)number6[i];
				}
			}
			if (size == 4) {
				for (int i = 0; i < 25; i++) {
					fourthNumber[i] = (blockNumber)number6[i];
				}
			}
			if (size == 5) {
				for (int i = 0; i < 25; i++) {
					fifthNumber[i] = (blockNumber)number6[i];
				}
			}
			if (size == 6) {
				for (int i = 0; i < 25; i++) {
					sixthNumber[i] = (blockNumber)number6[i];
				}
			}
			break;
		}
		case blockNumber::N7:
		{
			if (size == 1) {
				for (int i = 0; i < 25; i++) {
					firstNumber[i] = (blockNumber)number7[i];
				}
			}
			if (size == 2) {
				for (int i = 0; i < 25; i++) {
					secondNumber[i] = (blockNumber)number7[i];
				}
			}
			if (size == 3) {
				for (int i = 0; i < 25; i++) {
					thirdNumber[i] = (blockNumber)number7[i];
				}
			}
			if (size == 4) {
				for (int i = 0; i < 25; i++) {
					fourthNumber[i] = (blockNumber)number7[i];
				}
			}
			if (size == 5) {
				for (int i = 0; i < 25; i++) {
					fifthNumber[i] = (blockNumber)number7[i];
				}
			}
			if (size == 6) {
				for (int i = 0; i < 25; i++) {
					sixthNumber[i] = (blockNumber)number7[i];
				}
			}
			break;
		}
		case blockNumber::N8:
		{
			if (size == 1) {
				for (int i = 0; i < 25; i++) {
					firstNumber[i] = (blockNumber)number8[i];
				}
			}
			if (size == 2) {
				for (int i = 0; i < 25; i++) {
					secondNumber[i] = (blockNumber)number8[i];
				}
			}
			if (size == 3) {
				for (int i = 0; i < 25; i++) {
					thirdNumber[i] = (blockNumber)number8[i];
				}
			}
			if (size == 4) {
				for (int i = 0; i < 25; i++) {
					fourthNumber[i] = (blockNumber)number8[i];
				}
			}
			if (size == 5) {
				for (int i = 0; i < 25; i++) {
					fifthNumber[i] = (blockNumber)number8[i];
				}
			}
			if (size == 6) {
				for (int i = 0; i < 25; i++) {
					sixthNumber[i] = (blockNumber)number8[i];
				}
			}
			break;
		}
		case blockNumber::N9:
		{
			if (size == 1) {
				for (int i = 0; i < 25; i++) {
					firstNumber[i] = (blockNumber)number9[i];
				}
			}
			if (size == 2) {
				for (int i = 0; i < 25; i++) {
					secondNumber[i] = (blockNumber)number9[i];
				}
			}
			if (size == 3) {
				for (int i = 0; i < 25; i++) {
					thirdNumber[i] = (blockNumber)number9[i];
				}
			}
			if (size == 4) {
				for (int i = 0; i < 25; i++) {
					fourthNumber[i] = (blockNumber)number9[i];
				}
			}
			if (size == 5) {
				for (int i = 0; i < 25; i++) {
					fifthNumber[i] = (blockNumber)number9[i];
				}
			}
			if (size == 6) {
				for (int i = 0; i < 25; i++) {
					sixthNumber[i] = (blockNumber)number9[i];
				}
			}
			break;
		}
	}
}

void textFont::clearScore()
{
	for (int i = 0; i < 25; i++)
	{
		firstNumber[i] = blockNumber::NA;
		secondNumber[i] = blockNumber::NA;
		thirdNumber[i] = blockNumber::NA;
		fourthNumber[i] = blockNumber::NA;
		fifthNumber[i] = blockNumber::NA;
		sixthNumber[i] = blockNumber::NA;
	}
}

void textFont::drawLetters(blockNumber type, int size)
{
	switch (type)
	{
		case blockNumber::NA:
		{
			break;
		}
		case blockNumber::N0:
		{
			if (size == 1) {
				for (int i = 0; i < 25; i++) {
					rowFirstNumber[i] = (blockNumber)number0[i];
				}
			}
			if (size == 2) {
				for (int i = 0; i < 25; i++) {
					rowSecondNumber[i] = (blockNumber)number0[i];
				}
			}
			if (size == 3) {
				for (int i = 0; i < 25; i++) {
					rowThirdNumber[i] = (blockNumber)number0[i];
				}
			}
			break;
		}
		case blockNumber::N1:
		{
			if (size == 1) {
				for (int i = 0; i < 25; i++) {
					rowFirstNumber[i] = (blockNumber)number1[i];
				}
			}
			if (size == 2) {
				for (int i = 0; i < 25; i++) {
					rowSecondNumber[i] = (blockNumber)number1[i];
				}
			}
			if (size == 3) {
				for (int i = 0; i < 25; i++) {
					rowThirdNumber[i] = (blockNumber)number1[i];
				}
			}
			break;
		}
		case blockNumber::N2:
		{
			if (size == 1) {
				for (int i = 0; i < 25; i++) {
					rowFirstNumber[i] = (blockNumber)number2[i];
				}
			}
			if (size == 2) {
				for (int i = 0; i < 25; i++) {
					rowSecondNumber[i] = (blockNumber)number2[i];
				}
			}
			if (size == 3) {
				for (int i = 0; i < 25; i++) {
					rowThirdNumber[i] = (blockNumber)number2[i];
				}
			}
			break;
		}
		case blockNumber::N3:
		{
			if (size == 1) {
				for (int i = 0; i < 25; i++) {
					rowFirstNumber[i] = (blockNumber)number3[i];
				}
			}
			if (size == 2) {
				for (int i = 0; i < 25; i++) {
					rowSecondNumber[i] = (blockNumber)number3[i];
				}
			}
			if (size == 3) {
				for (int i = 0; i < 25; i++) {
					rowThirdNumber[i] = (blockNumber)number3[i];
				}
			}
			break;
		}
		case blockNumber::N4:
		{
			if (size == 1) {
				for (int i = 0; i < 25; i++) {
					rowFirstNumber[i] = (blockNumber)number4[i];
				}
			}
			if (size == 2) {
				for (int i = 0; i < 25; i++) {
					rowSecondNumber[i] = (blockNumber)number4[i];
				}
			}
			if (size == 3) {
				for (int i = 0; i < 25; i++) {
					rowThirdNumber[i] = (blockNumber)number4[i];
				}
			}
			break;
		}
		case blockNumber::N5:
		{
			if (size == 1) {
				for (int i = 0; i < 25; i++) {
					rowFirstNumber[i] = (blockNumber)number5[i];
				}
			}
			if (size == 2) {
				for (int i = 0; i < 25; i++) {
					rowSecondNumber[i] = (blockNumber)number5[i];
				}
			}
			if (size == 3) {
				for (int i = 0; i < 25; i++) {
					rowThirdNumber[i] = (blockNumber)number5[i];
				}
			}
			break;
		}
		case blockNumber::N6:
		{
			if (size == 1) {
				for (int i = 0; i < 25; i++) {
					rowFirstNumber[i] = (blockNumber)number6[i];
				}
			}
			if (size == 2) {
				for (int i = 0; i < 25; i++) {
					rowSecondNumber[i] = (blockNumber)number6[i];
				}
			}
			if (size == 3) {
				for (int i = 0; i < 25; i++) {
					rowThirdNumber[i] = (blockNumber)number6[i];
				}
			}
			break;
		}
		case blockNumber::N7:
		{
			if (size == 1) {
				for (int i = 0; i < 25; i++) {
					rowFirstNumber[i] = (blockNumber)number7[i];
				}
			}
			if (size == 2) {
				for (int i = 0; i < 25; i++) {
					rowSecondNumber[i] = (blockNumber)number7[i];
				}
			}
			if (size == 3) {
				for (int i = 0; i < 25; i++) {
					rowThirdNumber[i] = (blockNumber)number7[i];
				}
			}
			break;
		}
		case blockNumber::N8:
		{
			if (size == 1) {
				for (int i = 0; i < 25; i++) {
					rowFirstNumber[i] = (blockNumber)number8[i];
				}
			}
			if (size == 2) {
				for (int i = 0; i < 25; i++) {
					rowSecondNumber[i] = (blockNumber)number8[i];
				}
			}
			if (size == 3) {
				for (int i = 0; i < 25; i++) {
					rowThirdNumber[i] = (blockNumber)number8[i];
				}
			}
			break;
		}
		case blockNumber::N9:
		{
			if (size == 1) {
				for (int i = 0; i < 25; i++) {
					rowFirstNumber[i] = (blockNumber)number9[i];
				}
			}
			if (size == 2) {
				for (int i = 0; i < 25; i++) {
					rowSecondNumber[i] = (blockNumber)number9[i];
				}
			}
			if (size == 3) {
				for (int i = 0; i < 25; i++) {
					rowThirdNumber[i] = (blockNumber)number9[i];
				}
			}
			break;
		}
		case blockNumber::LR:
		{
			if (size == 7) {
				for (int i = 0; i < 25; i++) {
					lR[i] = (blockNumber)letterR[i];
				}
			}
			break;
		}
		case blockNumber::LO:
		{
			if (size == 6) {
				for (int i = 0; i < 25; i++) {
					lO[i] = (blockNumber)letterO[i];
				}
			}
			break;
		}
		case blockNumber::LW:
		{
			if (size == 5) {
				for (int i = 0; i < 25; i++) {
					lW[i] = (blockNumber)letterW[i];
				}
			}
			break;
		}
		case blockNumber::LS:
		{
			if (size == 4) {
				for (int i = 0; i < 25; i++) {
					lS[i] = (blockNumber)letterS[i];
				}
			}
			break;
		}
	}
}

void textFont::clearLetters()
{
	for (int i = 0; i < 25; i++)
	{
		rowFirstNumber[i] = blockNumber::NA;
		rowSecondNumber[i] = blockNumber::NA;
		rowThirdNumber[i] = blockNumber::NA;
	}
}