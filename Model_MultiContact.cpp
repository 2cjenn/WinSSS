// Model_MultiContact.cpp: implementation of the Model_MultiContact class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "sss.h"
#include "Model_MultiContact.h"
#include <random>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Model_MultiContact::Model_MultiContact()
{
	nStates = 4;

}

Model_MultiContact::~Model_MultiContact()
{

}

Model_MultiContact::Model_MultiContact(int rowcol, void * tempPara)
{
	Para = (ParaDlg_MultiCont *)tempPara;
	nbr = 4;
	nStates = 4;
	nRow = rowcol;
	nCol = rowcol;
	nTimers = 6;
	pStateArray = new char[nRow * nCol];
	timerArray = new double *[nTimers];
	for (int i = 0; i < nTimers; i++)
	{
		timerArray[i] = new double[nRow * nCol];
	}
	generator.seed(1);
	distribution = std::uniform_int_distribution<int>(0, 8);

	Initialization();
}

enum Infected { Neither = 0, Mosquito = 1, Human = 2, Both = 3 };

int kDest;
int lDest;

void Model_MultiContact::ResetTimers()
{
	/*double dBirth1 = Para->m_birth1;
	double dBirth2 = Para->m_birth2;
	double dDeath1 = Para->m_death1;
	double dDeath2 = Para->m_death2;*/

	double hRecover = 1;
	double hInfectH = Para->m_birth1;
	double mInfectH = Para->m_death1;

	double mDie = Para->m_death2;
	double hInfectM = Para->m_death1;
	double mJump = Para->m_birth2;

	/*double bite = 1;*/

	std::exponential_distribution<double> d1(1.0);

	minTimer = (std::numeric_limits<double>::max)();
	action = -1;
	xLocation = 0;
	yLocation = 0;

	for (int k = 0; k < nRow; k++)
	{
		for (int l = 0; l < nCol; l++)
		{
			//find normal lattice neighbours
			double infNbrH = 0.0;
			double infNbrM = 0.0;
			for (int i = 0; i < 4; i++)
			{
				int kMod = k + nbrX[i];
				int lMod = l + nbrY[i];

				if ((*ModState(kMod, lMod) == Human) || (*ModState(kMod, lMod) == Both))
				{
					infNbrH += 1;
				}
			}
			for (int i = 0; i < 8; i++)
			{
				int kMod = k + nbrX[i];
				int lMod = l + nbrY[i];

				if ((*ModState(kMod, lMod) == Mosquito) || (*ModState(kMod, lMod) == Both))
				{
					infNbrM += 1;
				}
			}
			//find connected lattice neighbours
			double infBiteNbrH = 0.0;
			double infBiteNbrM = 0.0;

			for (int i = 0; i < 8; i++)
			{
				int kMod = k + nbrX[i];
				int lMod = l + nbrY[i];

				if ((*ModState(kMod, lMod) == Human) || (*ModState(kMod, lMod) == Both))
				{
					infBiteNbrH += 1.0;
				}

				if ((*ModState(kMod, lMod) == Mosquito) || (*ModState(kMod, lMod) == Both))
				{
					infBiteNbrM += 1.0;
				}
			}
			if ((State(k, l) == Human) || (State(k, l) == Both))
			{
				infBiteNbrH += 1.0;
			}
			if ((State(k, l) == Mosquito) || (State(k, l) == Both))
			{
				infBiteNbrM += 1.0;
			}

			double timer;

			//Case 0 Human Recover
			if ((State(k, l) == Human) || (State(k, l) == Both))
			{
				timer = d1(generator);
				timer = timer / hRecover;
				if (timer < minTimer)
				{
					action = 0;
					xLocation = k;
					yLocation = l;
					minTimer = timer;
				}
			}
			//Case 1 Human STI
			if ((State(k, l) == Neither) || (State(k, l) == Mosquito))
			{
				if (infNbrH != 0)
				{
					timer = d1(generator);
					timer = timer / (hInfectH * infNbrH);
					if (timer < minTimer)
					{
						action = 1;
						xLocation = k;
						yLocation = l;
						minTimer = timer;
					}
				}
			}
			//Case 2 Human bitten
			if ((State(k, l) == Neither) || (State(k, l) == Mosquito))
			{
				if (infBiteNbrM != 0)
				{
					timer = d1(generator);
					timer = timer / (mInfectH * infBiteNbrM);
					if (timer < minTimer)
					{
						action = 2;
						xLocation = k;
						yLocation = l;
						minTimer = timer;
					}
				}
			}
			//Case 3 Mosquito Die
			if ((State(k, l) == Mosquito) || (State(k, l) == Both))
			{
				timer = d1(generator);
				timer = timer / mDie;
				if (timer < minTimer)
				{
					action = 3;
					xLocation = k;
					yLocation = l;
					minTimer = timer;
				}
			}
			//Case 4 Mosquito bites
			if ((State(k, l) == Neither) || (State(k, l) == Human))
			{
				if (infBiteNbrH != 0)
				{
					timer = d1(generator);
					timer = timer / (hInfectM * infBiteNbrH);
					if (timer < minTimer)
					{
						action = 4;
						xLocation = k;
						yLocation = l;
						minTimer = timer;
					}
				}
			}
			//Case 5 Mosquito moves
			if ((State(k, l) == Mosquito) || (State(k, l) == Both))
			{
				if (8 - infNbrM != 0)
				{
					timer = d1(generator);
					timer = timer / (mJump * (8 - infNbrM));
					if (timer < minTimer)
					{
						action = 5;
						xLocation = k;
						yLocation = l;
						minTimer = timer;
					}
				}
			}
		}
	}

}
char * Model_MultiContact::ModState(int x, int y)
{
	x = x%nRow;
	if (x < 0)
	{
		x += nRow;
	}
	y = y%nCol;
	if (y < 0)
	{
		y += nCol;
	}
	return &pStateArray[(x)+((y)* nRow)];
}

void Model_MultiContact::Initialization()
{
	for (int i = 0; i < nRow * nCol; i++)
		//pStateArray[i] = pRand->IRandom(0, 1);
	{
		/*if (0.9 > pRand->Random())
			pStateArray[i] = Neither;
		else
			pStateArray[i] = Mosquito;*/

		pStateArray[i] = 0;
	}
	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			State((nRow / 2 + i), (nCol / 2 + j)) = 1;
		}
	}
	/*for (int i = -32; i <= -30; i++)
	{
		for (int j = -15; j <= -13; j++)
		{
			State((nRow / 2 + i), (nCol / 2 + j)) = 1;
		}
	}
	for (int i = 22; i <= 24; i++)
	{
		for (int j = 35; j <= 37; j++)
		{
			State((nRow / 2 + i), (nCol / 2 + j)) = 1;
		}
	}*/
}


void Model_MultiContact::Simulation(SpatialWnd * pSpatial, int speed)
{
	nStates = 4;
	for (int iii = 0; iii < nStates; iii++)
	{
		nDistribution[iii] = 0;
		dFreq[iii] = 0;
	}
	for (int i = 0; i < 10; i++)
	{
		ResetTimers();
		switch (action)
		{
		case -1:
			break;
		case 0:
			if (State(xLocation, yLocation) == Human)
			{
				State(xLocation, yLocation) = Neither;
			}
			else if (State(xLocation, yLocation) == Both)
			{
				State(xLocation, yLocation) = Mosquito;
			}
			break;
		case 1:
		case 2:
			if (State(xLocation, yLocation) == Neither)
			{
				State(xLocation, yLocation) = Human;
			}
			else if (State(xLocation, yLocation) == Mosquito)
			{
				State(xLocation, yLocation) = Both;
			}
			break;
		case 3:
			if (State(xLocation, yLocation) == Mosquito)
			{
				State(xLocation, yLocation) = Neither;
			}
			else if (State(xLocation, yLocation) == Both)
			{
				State(xLocation, yLocation) = Human;
			}
			break;
		case 4:
			if (State(xLocation, yLocation) == Neither)
			{
				State(xLocation, yLocation) = Mosquito;
			}
			else if (State(xLocation, yLocation) == Human)
			{
				State(xLocation, yLocation) = Both;
			}
			break;
		case 5:
			bool jumped = false;
			int xDestination;
			int yDestination;
			do {
				int random_neighbour = distribution(generator);
				if (random_neighbour == 8)
				{
					xDestination = xLocation;
					yDestination = yLocation;
				}
				else
				{
					xDestination = xLocation + nbrX[random_neighbour];
					yDestination = yLocation + nbrY[random_neighbour];
				}
					if ((*ModState(xDestination, yDestination) == Human) || (*ModState(xDestination, yDestination) == Neither))
					{
						if (State(xLocation, yLocation) == Mosquito)
						{
							State(xLocation, yLocation) = Neither;
							if (*ModState(xDestination, yDestination) == Human)
							{
								*ModState(xDestination, yDestination) = Both;
							}
							else if (*ModState(xDestination, yDestination) == Neither)
							{
								*ModState(xDestination, yDestination) = Mosquito;
							}
						}
						else if (State(xLocation, yLocation) == Both)
						{
							State(xLocation, yLocation) = Human;
							if (*ModState(xDestination, yDestination) == Human)
							{
								*ModState(xDestination, yDestination) = Both;
							}
							else if (*ModState(xDestination, yDestination) == Neither)
							{
								*ModState(xDestination, yDestination) = Mosquito;
							}
						}
						jumped = true;
					}
			} while (!jumped);

		}
	}



	/*int total = nRow * nCol;

	int x2, y2, x3, y3;*/


	/*double maxrate = __max(__max(dBirth1, dDeath1), __max(dBirth2, dDeath2));
	dBirth1 /= maxrate;
	dBirth2 /= maxrate;
	dDeath1 /= maxrate;
	dDeath2 /= maxrate;*/

	/*double maxrate = __max(__max(__max(mJump, mInfectH), __max(hRecover, hInfectM)), hInfectH);
	mJump /= maxrate;
	mInfectH /= maxrate;
	hRecover /= maxrate;
	bite /= maxrate;*/

	/*int dir, dir2;
	for (int ii = 0; ii < total / (speed + 1); ii++)
	{
		int iX = pRand->IRandom(0, nRow - 1);
		int iY = pRand->IRandom(0, nCol - 1);

		double dUniform = pRand->Random();

		int nCount1 = 0;
		int nCount2 = 0;
		int iDir;
		double totalRate;
		double partialRate1;
		double partialRate2;

		double infNbrH = 0;
		double infNbrM = 0;
*/
/*for (int i = 0; i < 4; i++)
{
	if (State(iX + nbrX[i], iY + nbrY[i]) == Human || State(iX + nbrX[i], iY + nbrY[i]) == Both)
	{
		infNbrH += .25;
	}

	if (State(iX + nbrX[i], iY + nbrY[i]) == Mosquito || State(iX + nbrX[i], iY + nbrY[i]) == Both)
	{
		infNbrM += .25;
	}
}

double infBiteNbrH = 0;
double infBiteNbrM = 0;

for (int i = 0; i < 8; i++)
{
	if (State(iX + nbrX[i], iY + nbrY[i]) == Human || State(iX + nbrX[i], iY + nbrY[i]) == Both)
	{
		infBiteNbrH += .125;
	}

	if (State(iX + nbrX[i], iY + nbrY[i]) == Mosquito || State(iX + nbrX[i], iY + nbrY[i]) == Both)
	{
		infBiteNbrM += .125;
	}
}*/


/*
switch (State(iX, iY))
{
case Neither:
	if (hInfectH > dUniform)
	{
		dir = pRand->IRandom(0, 3);
	}

	x2 = (iX + nbrX[dir] + nRow) % nRow;
	y2 = (iY + nbrY[dir] + nCol) % nCol;

	if (State(x2, y2) == Human || State(x2, y2) == Both)
	{
		State(iX, iY) = Human;
	}

	if (bite > dUniform)
	{
		dir2 = pRand->IRandom(0, 7);
	}
	x3 = (iX + nbrX[dir2] + nRow) % nRow;
	y3 = (iY + nbrY[dir2] + nCol) % nCol;

	if (State(x3, y3) == Human || State(x3, y3) == Both)
	{
		if (State(iX, iY) == Human)
		{
			State(iX, iY) = Both;
		}
		else
		{
			State(iX, iY) = Mosquito;
		}
	}

	if (State(x3, y3) == Mosquito || State(x3, y3) == Both)
	{
		if (State(iX, iY) == Human)
		{
			State(iX, iY) = Both;
		}
		else
		{
			State(iX, iY) = Mosquito;
		}
	}
	break;


case Mosquito:
	if (mJump > dUniform)
	{
		dir = pRand->IRandom(0, 3);
	}

	x2 = (iX + nbrX[dir] + nRow) % nRow;
	y2 = (iY + nbrY[dir] + nCol) % nCol;

	if (State(x2, y2) == Human || State(x2, y2) == Neither)
	{
		State(x2, y2) = Mosquito;
		State(iX, iY) = Neither;
	}

	if (hInfectH > dUniform)
	{
		dir = pRand->IRandom(0, 3);
	}

	x3 = (iX + nbrX[dir] + nRow) % nRow;
	y3 = (iY + nbrY[dir] + nCol) % nCol;

	if (State(x3, y3) == Human || State(x3, y3) == Both)
	{
		State(iX, iY) = Human;
	}
	break;

case Human:
	if (hRecover > dUniform)
	{
		State(iX, iY) = Neither;
	}

	if (hInfectM > dUniform)
	{
		dir = pRand->IRandom(0, 7);
	}

	x2 = (iX + nbrX[dir] + nRow) % nRow;
	y2 = (iY + nbrY[dir] + nCol) % nCol;

	if (State(x2, y2) == Human || State(x2, y2) == Both)
	{
		State(iX, iY) = Both;
	}

	break;

case Both:
	if (hRecover > dUniform)
	{
		State(iX, iY) = Mosquito;
	}
	break;

}
}*/

FreqStat(pSpatial);

}

