// Model_RSP.cpp: implementation of the Model_RSP class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "sss.h"
#include "Model_RSP.h"
#include "ModelTemplate.h"
#include "MyRand.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Model_RSP::Model_RSP(int rowcol, void * tempPara)
{
	Para = (ParaDlg_RSP *) tempPara;
	nStates = Para->m_nStates;
	nRow = rowcol;
	nCol = rowcol;
	pStateArray = new char[nRow * nCol];
	Initialization();

}


Model_RSP::Model_RSP()
{

}

Model_RSP::~Model_RSP()
{

}


void Model_RSP::Initialization()
{
	for (int i =0; i<nRow * nCol; i++)
		pStateArray[i] = pRand->IRandom(0,nStates-1);
}


void Model_RSP::Simulation(SpatialWnd * pSpatial, int speed)
{
	nStates = Para->m_nStates;
	nbr = Para->m_nbr;


	for(int iii= 0; iii<nStates; iii++)
	{
		nDistribution[iii] = 0;
		dFreq[iii] = 0;
	}

	double d01 = Para->m_d01;
	double d12 = Para->m_d12;
	double d20 = Para->m_d20;
	double d3 = Para->m_d3;
	double d4 = Para->m_d4;
	double d5 = Para->m_d5;
	double d6 = Para->m_d6;
	double d7 = Para->m_d7;

	int i;
    int iX, iY, iDir, iX2, iY2;
    double max_rate, c01, c12, c20, c3, c4, c5, c6, c7;
  
    max_rate = d01;
    if(max_rate < d12) max_rate=d12;
    if(max_rate < d20) max_rate=d20;
    if(max_rate < d3) max_rate = d3;
	if(max_rate < d4) max_rate = d4;
	if(max_rate < d5) max_rate = d5;
	if(max_rate < d6) max_rate = d6;
	if(max_rate < d7) max_rate = d7;
	
    c01 = d01/max_rate;
    c12 = d12/max_rate;
    c20 = d20/max_rate;
	c3 = d3/max_rate;
	c4 = d4/max_rate;
	c5 = d5/max_rate;
	c6 = d6/max_rate;
	c7 = d7/max_rate;

	
   int total = nRow * nCol;
	
	for (i = 0; i < total / (speed + 1); i++)
	{
		iX = pRand->IRandom(0, nCol-1);		// Generate a random X coordinate. 
		iY = pRand->IRandom(0, nCol-1);		// Generate a random Y coordinate. 

		double UNIFORM = pRand->Random();
		int count = 0;
		switch(Para->m_bthreshold)
		{
		case false:
				switch (pStateArray [iX + nRow * iY]) 
				{
					case 0:
							if (UNIFORM < c01) 
							{
								iDir = pRand->IRandom(0,nbr);  
												
								iX2 = (iX + nbrX [iDir] + nRow) % nRow;
								iY2 = (iY + nbrY [iDir] + nCol) % nCol;
							
								if ( pStateArray[iX2 + nRow * iY2] == 1)
										pStateArray[iX + nRow * iY] = 1;
								
							}
							
							break;
					
					case 1:
							if (UNIFORM < c12) 
							{
								iDir = pRand->IRandom(0,nbr);  
												
								iX2 = (iX + nbrX [iDir] + nRow) % nRow;
								iY2 = (iY + nbrY [iDir] + nCol) % nCol;
							
								if ( pStateArray[iX2 + nRow * iY2] == 2)
										pStateArray[iX + nRow * iY] = 2;
								
							}
							
							break;
					case 2:
						
							if (UNIFORM < c20) 
							{
								iDir = pRand->IRandom(0,nbr);  
												
								iX2 = (iX + nbrX [iDir] + nRow) % nRow;
								iY2 = (iY + nbrY [iDir] + nCol) % nCol;
							
								if ( pStateArray[iX2 + nRow * iY2] == 3 % nStates)
									pStateArray[iX + nRow * iY] = 3 % nStates;
								
							}
							
							break;

					case 3:
							if (UNIFORM < c3) 
							{
								iDir = pRand->IRandom(0,nbr);  
												
								iX2 = (iX + nbrX [iDir] + nRow) % nRow;
								iY2 = (iY + nbrY [iDir] + nCol) % nCol;
							
								if ( pStateArray[iX2 + nRow * iY2] == 4 % nStates && 4 <= nStates)
										pStateArray[iX + nRow * iY] = 4 % nStates;
								
							}
							break;
					
					case 4:
						
							if (UNIFORM < c4) 
							{
								iDir = pRand->IRandom(0,nbr);  
												
								iX2 = (iX + nbrX [iDir] + nRow) % nRow;
								iY2 = (iY + nbrY [iDir] + nCol) % nCol;
							
								if ( pStateArray[iX2 + nRow * iY2] == 5 % nStates && 5 <= nStates)
									pStateArray[iX + nRow * iY] = 5 % nStates;
								
							}
							
							break;

					case 5:
							if (UNIFORM < c5) 
							{
								iDir = pRand->IRandom(0,nbr);  
												
								iX2 = (iX + nbrX [iDir] + nRow) % nRow;
								iY2 = (iY + nbrY [iDir] + nCol) % nCol;
							
								if ( pStateArray[iX2 + nRow * iY2] == 6 % nStates && 6 <= nStates)
										pStateArray[iX + nRow * iY] = 6 % nStates;
								
							}
							break;

					case 6:
						
							if (UNIFORM < c6) 
							{
								iDir = pRand->IRandom(0,nbr);  
												
								iX2 = (iX + nbrX [iDir] + nRow) % nRow;
								iY2 = (iY + nbrY [iDir] + nCol) % nCol;
							
								if ( pStateArray[iX2 + nRow * iY2] == 7 % nStates && 7 <= nStates)
									pStateArray[iX + nRow * iY] = 7 % nStates;
								
							}
							
							break;

					case 7:
							if (UNIFORM < c7) 
							{
								iDir = pRand->IRandom(0,nbr);  
												
								iX2 = (iX + nbrX [iDir] + nRow) % nRow;
								iY2 = (iY + nbrY [iDir] + nCol) % nCol;
							
								if ( pStateArray[iX2 + nRow * iY2] == 8 % nStates)
										pStateArray[iX + nRow * iY] = 8 % nStates;
								
							}
							break;

				}

			break;

		case true:
				switch (pStateArray [iX + nRow * iY]) 
				{
					case 0:
							if (UNIFORM < c01) 
							{
								count = 0;
								for (iDir = 0; iDir < nbr; iDir++)
								{												
									iX2 = (iX + nbrX [iDir] + nRow) % nRow;
									iY2 = (iY + nbrY [iDir] + nCol) % nCol;
							
									if ( pStateArray[iX2 + nRow * iY2] == 1)
										count++;
								}

								if (count >= Para->m_nthreshold)
									pStateArray[iX + nRow * iY] = 1;
								
							}
							
							break;
					
					case 1:
							if (UNIFORM < c12) 
							{
								count = 0;
								for (iDir = 0; iDir < nbr; iDir++)
								{												
									iX2 = (iX + nbrX [iDir] + nRow) % nRow;
									iY2 = (iY + nbrY [iDir] + nCol) % nCol;
							
									if ( pStateArray[iX2 + nRow * iY2] == 2)
										count++;
								}

								if (count >= Para->m_nthreshold)
									pStateArray[iX + nRow * iY] = 2;
							}
							
							break;
					case 2:
						
							if (UNIFORM < c20) 
							{
								count = 0;
								for (iDir = 0; iDir < nbr; iDir++)
								{												
									iX2 = (iX + nbrX [iDir] + nRow) % nRow;
									iY2 = (iY + nbrY [iDir] + nCol) % nCol;
							
									if ( pStateArray[iX2 + nRow * iY2] == 3 % nStates)
										count++;
								}

								if (count >= Para->m_nthreshold)
									pStateArray[iX + nRow * iY] = 3 % nStates;
								
							}
							
							break;

					case 3:
							if (UNIFORM < c3) 
							{
								count = 0;
								for (iDir = 0; iDir < nbr; iDir++)
								{												
									iX2 = (iX + nbrX [iDir] + nRow) % nRow;
									iY2 = (iY + nbrY [iDir] + nCol) % nCol;
							
									if ( pStateArray[iX2 + nRow * iY2] == 4 % nStates)
										count++;
								}

								if (count >= Para->m_nthreshold && 4 <= nStates)
									pStateArray[iX + nRow * iY] = 4 % nStates;
							
							}
							break;
					
					case 4:
						
							if (UNIFORM < c4) 
							{
								count = 0;
								for (iDir = 0; iDir < nbr; iDir++)
								{												
									iX2 = (iX + nbrX [iDir] + nRow) % nRow;
									iY2 = (iY + nbrY [iDir] + nCol) % nCol;
							
									if ( pStateArray[iX2 + nRow * iY2] == 5 % nStates)
										count++;
								}

								if (count >= Para->m_nthreshold && 5 <= nStates)
									pStateArray[iX + nRow * iY] = 5 % nStates;
							}
							
							break;

					case 5:
							if (UNIFORM < c5) 
							{
								count = 0;
								for (iDir = 0; iDir < nbr; iDir++)
								{												
									iX2 = (iX + nbrX [iDir] + nRow) % nRow;
									iY2 = (iY + nbrY [iDir] + nCol) % nCol;
							
									if ( pStateArray[iX2 + nRow * iY2] == 6 % nStates)
										count++;
								}

								if (count >= Para->m_nthreshold && 6 <= nStates)
									pStateArray[iX + nRow * iY] = 6 % nStates;
								
							}
							break;

					case 6:
						
							if (UNIFORM < c6) 
							{
								count = 0;
								for (iDir = 0; iDir < nbr; iDir++)
								{												
									iX2 = (iX + nbrX [iDir] + nRow) % nRow;
									iY2 = (iY + nbrY [iDir] + nCol) % nCol;
							
									if ( pStateArray[iX2 + nRow * iY2] == 7 % nStates)
										count++;
								}

								if (count >= Para->m_nthreshold && 7 <= nStates)
									pStateArray[iX + nRow * iY] = 7 % nStates;
								
							}
							
							break;

					case 7:
							if (UNIFORM < c7) 
							{
								count = 0;
								for (iDir = 0; iDir < nbr; iDir++)
								{												
									iX2 = (iX + nbrX [iDir] + nRow) % nRow;
									iY2 = (iY + nbrY [iDir] + nCol) % nCol;
							
									if ( pStateArray[iX2 + nRow * iY2] == 8 % nStates)
										count++;
								}

								if (count >= Para->m_nthreshold && 8 <= nStates)
									pStateArray[iX + nRow * iY] = 8 % nStates;
								
							}
							break;

				}		

			break;

		
		}

	
	}

	FreqStat(pSpatial);
	
}