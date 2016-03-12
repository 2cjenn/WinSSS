// Model_EP.cpp: implementation of the Model_EP class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "sss.h"
#include "Model_EP.h"
#include "ParaDlg_EP.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////




Model_EP::Model_EP()
{
	
}

Model_EP::Model_EP(int rowcol, void * tempPara)
{
	Para = (ParaDlg_Ep *) tempPara;
	nStates = 3;//Para->m_nStates;
	nRow = rowcol;
	nCol = rowcol;
	pStateArray = new char[nRow * nCol];
	Initialization();
}

Model_EP::~Model_EP()
{

}

void Model_EP::Simulation(SpatialWnd * pSpatial, int speed)
{
	for(int iii= 0; iii<nStates; iii++)
	{
		nDistribution[iii] = 0;
		dFreq[iii] = 0;
	
	}

	double dRebirth = Para->m_rebirth;
	double dInfect = Para->m_infection;
	double dDeath = Para->m_death;
	int i;
    int iX, iY, iDir, iX2, iY2;
    double max_rate, c01, c12, c20;
 
    max_rate = dRebirth;
    if(max_rate < dInfect) max_rate=dInfect;
    if(max_rate < dDeath) max_rate=dDeath;
    
    c01 = dInfect/max_rate;
    c12 = dDeath/max_rate;
    c20 = dRebirth/max_rate;
	
   
	int total = nRow * nCol; 	
	for (i = 0; i < total / speed; i++)
	{
		iX = pRand->IRandom(0, nCol-1);		// Generate a random X coordinate. 
		iY = pRand->IRandom(0, nCol-1);		// Generate a random Y coordinate. 

		double UNIFORM = pRand->Random();
		switch (pStateArray [iX + nRow * iY]) 
		{
			case 0:
					if (UNIFORM < c01) 
					{
						iDir = pRand->IRandom(0,3);  
										
						iX2 = (iX + nbrX [iDir] + nRow) % nRow;
						iY2 = (iY + nbrY [iDir] + nCol) % nCol;
					
						if ( pStateArray[iX2 + nRow * iY2] == 1)
								pStateArray[iX + nRow * iY] = 1;
						
					}
					
					break;
			
			case 1:
					if ( UNIFORM < c12 ) 
						pStateArray[iX + nRow * iY] = 2;
					break;

			case 2:
				
					if (UNIFORM < c20) pStateArray [iX + nRow * iY] = 0;
					break;
		}
	}

	FreqStat(pSpatial);

}

void Model_EP::Initialization()
{
	int i, j;

	for(i = 0; i < nRow * nCol; i++)
		pStateArray[i] = 0;

	switch (Para->nInitID)
	{
	case 0:
		for(i=0; i<5; i++)
			for (j=0; j<5; j++)
				pStateArray[(nRow/2 -2 + i) * nRow + (nCol/2 -2 +j)] = 1;
		break;
	case 1:
		for (i =0; i<nRow * nCol; i++)
			pStateArray[i] = pRand->IRandom(0,nStates-1);
	}

}
