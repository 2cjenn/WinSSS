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

enum Infected { Neither = 0, HumanA = 1, HumanB = 2, Both = 3 };

void Model_MultiContact::ResetTimers()
{
	double hRecover = Para->m_death1;
	double hInfected = Para->m_birth1;

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
			double infNbrHB = 0.0;
			double infNbrHA = 0.0;
			for (int i = 0; i < 4; i++)
			{
				int kMod = k + nbrX[i];
				int lMod = l + nbrY[i];

				if ((*ModState(kMod, lMod) == HumanB) || (*ModState(kMod, lMod) == Both))
				{
					infNbrHB += 1.0;
				}

				if ((*ModState(kMod, lMod) == HumanA) || (*ModState(kMod, lMod) == Both))
				{
					infNbrHA += 1.0;
				}
			}
			//find connected lattice neighbours
			double infConnNbrHB = 0.0;
			double infConnNbrHA = 0.0;

			//For r = 1
			for (int i = 0; i < 8; i++)
			{
				int kMod = k + nbrX[i];
				int lMod = l + nbrY[i];

				if ((*ModState(kMod, lMod) == HumanB) || (*ModState(kMod, lMod) == Both))
				{
					infConnNbrHB += 1.0;
				}

				if ((*ModState(kMod, lMod) == HumanA) || (*ModState(kMod, lMod) == Both))
				{
					infConnNbrHA += 1.0;
				}
			}

			//For r = 5
			/*for (int i = 0; i < 40; i++)
			{
				int kMod = k + nbrFX[i];
				int lMod = l + nbrFY[i];

				if ((*ModState(kMod, lMod) == HumanB) || (*ModState(kMod, lMod) == Both))
				{
					infConnNbrHB += 1.0;
				}

				if ((*ModState(kMod, lMod) == HumanA) || (*ModState(kMod, lMod) == Both))
				{
					infConnNbrHA += 1.0;
				}
			}*/

			//For r = 10
			/*for (int i = 0; i < 80; i++)
			{
				int kMod = k + nbrTX[i];
				int lMod = l + nbrTY[i];

				if ((*ModState(kMod, lMod) == HumanB) || (*ModState(kMod, lMod) == Both))
				{
					infConnNbrHB += 1.0;
				}

				if ((*ModState(kMod, lMod) == HumanA) || (*ModState(kMod, lMod) == Both))
				{
					infConnNbrHA += 1.0;
				}
			}*/

			/*if ((State(k, l) == HumanB) || (State(k, l) == Both))
			{
				infConnNbrHB += 1.0;
			}
			if ((State(k, l) == HumanA) || (State(k, l) == Both))
			{
				infConnNbrHA += 1.0;
			}*/

			double timer;

			//Case 0 Recovery on A
			if ((State(k, l) == HumanB) || (State(k, l) == Both))
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
			//Case 1 Infection on lattice B
			if ((State(k, l) == Neither) || (State(k, l) == HumanA))
			{
				if (infNbrHB != 0)
				{
					timer = d1(generator);
					timer = timer / (hInfected * infNbrHB);
					if (timer < minTimer)
					{
						action = 1;
						xLocation = k;
						yLocation = l;
						minTimer = timer;
					}
				}
			}
			//Case 2 B infected by A
			if ((State(k, l) == Neither) || (State(k, l) == HumanA))
			{
				if (infConnNbrHA != 0)
				{
					timer = d1(generator);
					timer = timer / (hInfected * infConnNbrHA);
					if (timer < minTimer)
					{
						action = 2;
						xLocation = k;
						yLocation = l;
						minTimer = timer;
					}
				}
			}
			//Case 3 Recover on B
			if ((State(k, l) == HumanA) || (State(k, l) == Both))
			{
				timer = d1(generator);
				timer = timer / hRecover;
				if (timer < minTimer)
				{
					action = 3;
					xLocation = k;
					yLocation = l;
					minTimer = timer;
				}
			}
			//Case 4 A infected by B
			if ((State(k, l) == Neither) || (State(k, l) == HumanB))
			{
				if (infConnNbrHB != 0)
				{
					timer = d1(generator);
					timer = timer / (hInfected * infConnNbrHB);
					if (timer < minTimer)
					{
						action = 4;
						xLocation = k;
						yLocation = l;
						minTimer = timer;
					}
				}
			}
			//Case 5 Infection on lattice A
			if ((State(k, l) == Neither) || (State(k, l) == HumanB))
			{
				if (infNbrHA != 0)
				{
					timer = d1(generator);
					timer = timer / (hInfected * infNbrHA);
					if (timer < minTimer)
					{
						action = 1;
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
	{
		pStateArray[i] = 0;
	}
	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			State((nRow / 2 + i), (nCol / 2 + j)) = 1;
		}
	}
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
			if (State(xLocation, yLocation) == HumanB)
			{
				State(xLocation, yLocation) = Neither;
			}
			else if (State(xLocation, yLocation) == Both)
			{
				State(xLocation, yLocation) = HumanA;
			}
			break;
		case 1:
		case 2:
			if (State(xLocation, yLocation) == Neither)
			{
				State(xLocation, yLocation) = HumanB;
			}
			else if (State(xLocation, yLocation) == HumanA)
			{
				State(xLocation, yLocation) = Both;
			}
			break;
		case 3:
			if (State(xLocation, yLocation) == HumanA)
			{
				State(xLocation, yLocation) = Neither;
			}
			else if (State(xLocation, yLocation) == Both)
			{
				State(xLocation, yLocation) = HumanB;
			}
			break;
		case 4:
		case 5:
			if (State(xLocation, yLocation) == Neither)
			{
				State(xLocation, yLocation) = HumanA;
			}
			else if (State(xLocation, yLocation) == HumanB)
			{
				State(xLocation, yLocation) = Both;
			}
			break;
		}
	}

FreqStat(pSpatial);

}

