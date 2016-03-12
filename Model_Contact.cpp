// Model_Contact.cpp: implementation of the Model_Contact class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "sss.h"
#include "Model_Contact.h"
#include "math.h"
#include "stdlib.h"

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

Model_Contact::Model_Contact(int)
{

}

Model_Contact::Model_Contact(int rowcol, void * tempPara)
{
	Para = (ParaDlg_Contact *)tempPara;
	nbr = 4;
	nStates = Para->m_nStates;
	nRow = rowcol;
	nCol = rowcol;
	pStateArray = new char[nRow * nCol];
	Initialization();
}

Model_Contact::~Model_Contact()
{

}

void Model_Contact::Initialization()
{
	nStates = Para->m_nStates;
	int i,j;
	
	switch(Para->m_init)
	{
	case 0:
		for (i = 0; i < nRow * nCol; i++)
			pStateArray[i] = pRand->IRandom(0,1);
		break;
	case 1:
		for (i = 0; i < nRow * nCol; i++)
		{
			pStateArray[i] = 0;
		}
			for (i = -3; i <= 3; i++)
				for (j = -3; j <= 3; j++)
				{
					State((nRow / 2 + i), (nCol / 2 + j)) = 1;
				}
		

		break;
	}

}

void Model_Contact::Simulation(SpatialWnd * pSpatial, int speed)
{
	nStates = Para->m_nStates;
	for(int iii= 0; iii<nStates; iii++)
	{
		nDistribution[iii] = 0;
		dFreq[iii] = 0;
	}

	int total = nRow * nCol;

	int x2, y2;
	double dBirth;
	double dDeath;
	dBirth = Para->m_a0;  dDeath = Para->m_a1; 

	
	double maxrate = __max(dBirth,dDeath);
	dBirth /= maxrate;
	dDeath /= maxrate;

	
 
	int dir;
	for (int ii = 0; ii < total / speed ; ii++)
	{
		int x = pRand->IRandom(0, nRow-1);
		int y = pRand->IRandom(0, nCol-1);
	
	//	int x = pRand->IRandom(0, nRow * nCol -1);
		int temppos = x * nCol + y;
		double dUniform = pRand->Random();

		switch (pStateArray[temppos])
		{
		case 0:
			if (dBirth > dUniform)
			dir = pRand->IRandom(0,3);
	//		for( i=0; i<nbr; i++)
			{
				x2 = (x + nbrX[dir] + nRow) % nRow;
				y2 = (y + nbrY[dir] + nCol) % nCol;
			}
		
			if ( pStateArray[x2 * nCol + y2 ] == 1 ) 
			{ 
			//	tempArray[temppos] = 1;
				pStateArray[temppos] = 1;
			}
			break;
		
		case 1:
			if (dDeath >  dUniform)
			{
			//	tempArray[temppos] = 0;
				pStateArray[temppos] = 0;
			}
			break; 
		
		}
	}

	FreqStat(pSpatial);

}


