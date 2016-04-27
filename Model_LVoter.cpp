// Model_LVoter.cpp: implementation of the Model_LVoter class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "sss.h"
#include "Model_LVoter.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Model_LVoter::Model_LVoter()
{

}

Model_LVoter::~Model_LVoter()
{

}





Model_LVoter::Model_LVoter(int rowcol, void * tempPara)
{
	Para = (ParaDlg_Voter *) tempPara;
	nStates = Para->m_nStates;
	nRow = rowcol;
	nCol = rowcol;
	pStateArray = new char[nRow * nCol];
	Initialization();

}

void Model_LVoter::Initialization()
{
	for (int i =0; i<nRow * nCol; i++)
		pStateArray[i] = pRand->IRandom(0,nStates-1);
}


void Model_LVoter::Simulation(SpatialWnd * pSpatial, int speed)
{
	if (nStates != Para->m_nStates)
	{
		nStates = Para->m_nStates;
		Initialization();
	}
	
	for(int iii= 0; iii<nStates; iii++)
	{
		nDistribution[iii] = 0;
		dFreq[iii] = 0;
	}

	int total = nRow * nCol;
	int i;
	
	switch (Para->m_bThreshold)
	{
	case FALSE:  // linear model
		for (i = 0; i < total / speed; i++)
		{
			int iX = pRand->IRandom(0, nRow-1);		// Generate a random X coordinate. 
			int iY = pRand->IRandom(0, nCol-1);		// Generate a random Y coordinate. 
			int iDir = pRand->IRandom(0,Para->m_nbr-1);  
					
										
			int iX2 = (iX + nbrX [iDir] + nRow) % nRow;
			int iY2 = (iY + nbrY [iDir] + nCol) % nCol;
						
			pStateArray[iX + nRow * iY] = pStateArray[iX2 + nRow * iY2];
			
		}
		break;

	case TRUE:   //threshold model
		for (i = 0; i < total / speed; i++)
		{
			int iX = pRand->IRandom(0, nRow-1);
			int iY = pRand->IRandom(0, nCol-1);

			int nCount[10]; //maximum 10 species 
			short int bAboveThreshold[10]; 
			for (int iii = 0; iii < 10; iii++)
			{
				nCount[iii] = 0;
				bAboveThreshold[iii] = 0;  //fasle
			}

			for (int iDir=0; iDir < Para->m_nbr; iDir++)
			{
				int iX2 = (iX + nbrX [iDir] + nRow) % nRow;
				int iY2 = (iY + nbrY [iDir] + nCol) % nCol;
				nCount[State(iX2, iY2)] ++;
			}  //count how many individuals of each species in neighbor.

			int tempCount = 0;
			for (iii = 0; iii < nStates; iii++)
			{
				if (nCount[iii] >= Para->m_nThreshold)
				{
					bAboveThreshold[iii] = 1; //true;
					tempCount ++;
				}
			}

			if (tempCount > 0)
			{
				int speciestobe = pRand->IRandom(1, tempCount);
				tempCount = 0;
				for (iii = 0; iii < nStates; iii++)
				{
					tempCount += bAboveThreshold[iii];
					if (speciestobe == tempCount)
						break;
				}

				State(iX, iY) = iii;

			}
		}
		
	}
	
	
	FreqStat(pSpatial);
	
}
