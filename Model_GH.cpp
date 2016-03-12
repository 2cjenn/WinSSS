// Model_GH.cpp: implementation of the Model_GH class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "sss.h"
#include "Model_GH.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Model_GH::Model_GH()
{

}

Model_GH::~Model_GH()
{

}

Model_GH::Model_GH(int rowcol, void * tempPara)
{
	Para = (ParaDlg_GH *) tempPara;
	nStates = 8;
	nRow = rowcol;
	nCol = rowcol;
	
	nbr = Para->m_nbr;
	pStateArray = new char[nRow * nCol];
	Initialization();
}

void Model_GH::Initialization()
{
	int i;
	for (i =0; i<nRow * nCol; i++)
		pStateArray[i] = pRand->IRandom(0,nStates-1);

}

void Model_GH::Simulation(SpatialWnd * pSpatial, int speed)
{

	nbr = Para->m_nbr;
	for(int iii= 0; iii<nStates; iii++)
	{
		nDistribution[iii] = 0;
		dFreq[iii] = 0;
	}

	double dContactBirth = Para->m_cbirth;
	double dDeath1 = Para->m_death1;
	double dDeath2 = Para->m_death2;
	double dDeath3 = Para->m_death3;
	double dDeath4 = Para->m_death4;
	double dDeath5 = Para->m_death5;
	double dDeath6 = Para->m_death6;
	double dDeath7 = Para->m_death7;
	int i;
    int iX, iY, iX2, iY2;
    double max_rate, cb, cd1, cd2,cd3;
	double cd4, cd5, cd6, cd7;
 
    max_rate = dContactBirth;
    if(max_rate < dDeath1) max_rate=dDeath1;
    if(max_rate < dDeath2) max_rate=dDeath2;
	if(max_rate < dDeath3) max_rate=dDeath3;
	if(max_rate < dDeath4) max_rate=dDeath4;
    if(max_rate < dDeath5) max_rate=dDeath5;
	if(max_rate < dDeath6) max_rate=dDeath6;
	if(max_rate < dDeath7) max_rate=dDeath7;
   
    
    cb = dContactBirth/max_rate;
    cd1 = dDeath1/max_rate;
    cd2 = dDeath2/max_rate;
	cd3 = dDeath3/max_rate;
	cd4 = dDeath4/max_rate;
    cd5 = dDeath5/max_rate;
	cd6 = dDeath6/max_rate;
	cd7 = dDeath7/max_rate;
    
	int total = nRow * nCol;
	
	for (i = 0; i < total / speed; i++)
	{
		iX = pRand->IRandom(0, nCol-1);		// Generate a random X coordinate. 
		iY = pRand->IRandom(0, nCol-1);		// Generate a random Y coordinate. 

		double UNIFORM = pRand->Random();
		switch (pStateArray [iX + nRow * iY]) 
		{
			case 0:
					if (UNIFORM < cb) 
					{
						int count = 0;
						for(int ii = 0; ii < nbr; ii++)
						{
							iX2 = (iX + nbrX [ii] + nRow) % nRow;
							iY2 = (iY + nbrY [ii] + nCol) % nCol;
							if ( pStateArray[iX2 + nRow * iY2] == 1)
								count++;
						}
					
						if (count >= Para->m_nThreshold)
								pStateArray[iX + nRow * iY] = 1;
						
					}
					
					break;
			
			case 1:
					if ( UNIFORM < cd1 ) 
						pStateArray[iX + nRow * iY] = 2;
					break;

			case 2:
				
					if (UNIFORM < cd2) 
						pStateArray [iX + nRow * iY] = 3;
					break;
			case 3:
				
					if (UNIFORM < cd3) 
						pStateArray [iX + nRow * iY] = 4;
					break;
			case 4:
							
					if (UNIFORM < cd4) 
						pStateArray [iX + nRow * iY] = 5;
					break;
			case 5:
							
					if (UNIFORM < cd5) 
						pStateArray [iX + nRow * iY] = 6;
					break;

			case 6:
							
					if (UNIFORM < cd6) 
						pStateArray [iX + nRow * iY] = 7;
					break;
			case 7:
							
					if (UNIFORM < cd7) 
						pStateArray [iX + nRow * iY] = 0;
					break;

		}
	}

	FreqStat(pSpatial);
}
