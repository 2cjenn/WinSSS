// Model_Contact.cpp: implementation of the Model_Contact class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "sss.h"
#include "Model_Contact.h"
#include "math.h"
#include "stdlib.h"
#include <random>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Model_Contact::Model_Contact()
{
	
}

//Model_Contact::Model_Contact(int)
//{
//
//}

Model_Contact::~Model_Contact()
{

}

Model_Contact::Model_Contact(int rowcol, void * tempPara)
{
	Para = (ParaDlg_Contact *)tempPara;
	nbr = 4;
	nStates = Para->m_nStates;
	nRow = rowcol;
	nCol = rowcol;
	nTimers = 2;
	pStateArray = new char[nRow * nCol];
	timerArray = new double *[nTimers];
	for (int i = 0; i < nTimers; i++)
	{
		timerArray[i] = new double[nRow * nCol];
	}
	generator.seed(1);
	Initialization();
}



enum State { Healthy = 0, Infected = 1};

void Model_Contact::ResetTimers()
{
	double hRecover = Para->m_a1;
	double hInfected = Para->m_a0;

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
			double infNbr = 0.0;
			for (int i = 0; i < 4; i++)
			{
				int kMod = k + nbrX[i];
				int lMod = l + nbrY[i];

				if (*ModState(kMod, lMod) == Infected)
				{
					infNbr += 1.0;
				}
			}
			
			double timer;
	
			//Case 0 Recover
			if (State(k, l) == Infected)
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
		
			//Case 1 Infection
			if (State(k, l) == Healthy)
			{
				if (infNbr != 0)
				{
					timer = d1(generator);
					timer = timer / (hInfected * infNbr);
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
char * Model_Contact::ModState(int x, int y)
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

void Model_Contact::Initialization()
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


void Model_Contact::Simulation(SpatialWnd * pSpatial, int speed)
{
	nStates = 2;
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
			if (State(xLocation, yLocation) == Infected)
			{
				State(xLocation, yLocation) = Healthy;
			}
			break;

		case 1:
			if (State(xLocation, yLocation) == Healthy)
			{
				State(xLocation, yLocation) = Infected;
			}

			break;
		}
	}

	FreqStat(pSpatial);
}
//void Model_Contact::Initialization()
//{
//	nStates = Para->m_nStates;
//	int i,j;
//	
//	switch(Para->m_init)
//	{
//	case 0:
//		for (i = 0; i < nRow * nCol; i++)
//			pStateArray[i] = pRand->IRandom(0,1);
//		break;
//	case 1:
//		for (i = 0; i < nRow * nCol; i++)
//		{
//			pStateArray[i] = 0;
//		}
//			for (i = -3; i <= 3; i++)
//				for (j = -3; j <= 3; j++)
//				{
//					State((nRow / 2 + i), (nCol / 2 + j)) = 1;
//				}
//		
//
//		break;
//	}
//
//}
//
//void Model_Contact::Simulation(SpatialWnd * pSpatial, int speed)
//{
//	nStates = Para->m_nStates;
//	for(int iii= 0; iii<nStates; iii++)
//	{
//		nDistribution[iii] = 0;
//		dFreq[iii] = 0;
//	}
//
//	int total = nRow * nCol;
//
//	int x2, y2;
//	double dBirth;
//	double dDeath;
//	dBirth = Para->m_a0;  dDeath = Para->m_a1; 
//
//	
//	double maxrate = __max(dBirth,dDeath);
//	dBirth /= maxrate;
//	dDeath /= maxrate;
//
//	
// 
//	int dir;
//	for (int ii = 0; ii < total / speed ; ii++)
//	{
//		int x = pRand->IRandom(0, nRow-1);
//		int y = pRand->IRandom(0, nCol-1);
//	
//	//	int x = pRand->IRandom(0, nRow * nCol -1);
//		int temppos = x * nCol + y;
//		double dUniform = pRand->Random();
//
//		switch (pStateArray[temppos])
//		{
//		case 0:
//			if (dBirth > dUniform)
//
//			{
//				dir = pRand->IRandom(0, 3);
//
//				//		for( i=0; i<nbr; i++)
//
//				int x2 = (x + nbrX[dir] + nRow) % nRow;
//				int y2 = (y + nbrY[dir] + nCol) % nCol;
//
//
//				if (pStateArray[x2 * nCol + y2] == 1)
//				{
//					//	tempArray[temppos] = 1;
//					pStateArray[temppos] = 1;
//				}
//			}
//			break;
//		
//		case 1:
//			if (dDeath >  dUniform)
//			{
//			//	tempArray[temppos] = 0;
//				pStateArray[temppos] = 0;
//			}
//			break; 
//		
//		}
//	}
//
//	FreqStat(pSpatial);
//
//}


