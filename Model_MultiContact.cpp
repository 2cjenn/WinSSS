// Model_MultiContact.cpp: implementation of the Model_MultiContact class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "sss.h"
#include "Model_MultiContact.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Model_MultiContact::Model_MultiContact()
{
	nStates = 3;

}

Model_MultiContact::~Model_MultiContact()
{

}

Model_MultiContact::Model_MultiContact(int rowcol, void * tempPara)
{
	Para = (ParaDlg_MultiCont *)tempPara;
	nbr = 4;
	nStates = 3;
	nRow = rowcol;
	nCol = rowcol;
	pStateArray = new char[nRow * nCol];
	Initialization();
}

void Model_MultiContact::Initialization()
{
	for (int i = 0; i < nRow * nCol; i++)
		pStateArray[i] = pRand->IRandom(0, nStates-1);

}



void Model_MultiContact::Simulation(SpatialWnd * pSpatial, int speed)
{
	nStates = 3;
	for(int iii= 0; iii<nStates; iii++)
	{
		nDistribution[iii] = 0;
		dFreq[iii] = 0;
	}

	int total = nRow * nCol;

	int x2, y2;
	double dBirth1 = Para->m_birth1;
	double dBirth2 = Para->m_birth2;
	double dDeath1 = Para->m_death1;
	double dDeath2 = Para->m_death2;
	  
	double maxrate = __max(__max(dBirth1,dDeath1), __max(dBirth2, dDeath2));
	dBirth1 /= maxrate;   
	dBirth2 /= maxrate;
	dDeath1 /= maxrate;
	dDeath2 /= maxrate;
	
 
	int dir;
	for (int ii = 0; ii < total / (speed+1) ; ii++)
	{
		int iX = pRand->IRandom(0, nRow-1);
		int iY = pRand->IRandom(0, nCol-1);
	

		double dUniform = pRand->Random();

		int nCount1 = 0;
		int nCount2 = 0;
		int iDir;
		double totalRate;
		double partialRate1;
		double partialRate2;
		switch (State(iX, iY))
		{
		case 0:
			
			nCount1 = 0;
			nCount2 = 0;
			for(iDir = 0; iDir < nbr; iDir++)
			{
				int iX2 = (iX + nbrX[iDir] + nRow) % nRow;
				int iY2 = (iY + nbrY[iDir] + nCol) % nCol;
			
				if (State(iX2, iY2) == 1 ) 
					nCount1 ++;
				if (State(iX2, iY2) == 2 ) 
					nCount2 ++;
			}
		
			partialRate1 = nCount1 * dBirth1;
			partialRate2 = nCount2 * dBirth2;
			totalRate = partialRate1 + partialRate2; 
			
			if (totalRate / (double) nbr > dUniform)
			{
				if (pRand->Random() < partialRate1 / totalRate) 
					State(iX, iY) = 1;
				else 
					State(iX, iY) = 2;

			}
			break;
			
		
		case 1:
			if (dDeath1 >  dUniform)
			{
				State(iX, iY) = 0;
			}
			break; 

		case 2:
			if (dDeath2 > dUniform)
			{
				State(iX, iY) = 0;
			}
			break;
		
		}
	}

	FreqStat(pSpatial);

}

