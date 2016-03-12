// Model_Cyclic.cpp: implementation of the Model_Cyclic class.
//
//////////////////////////////////////////////////////////////////////
// add sparkling when movie freeze. on Jan. 3rd. 2004. 

#include "stdafx.h"
#include "sss.h"
#include "Model_Cyclic.h"
#include "ParaDlg_Cyclic.h"
#include <math.h>
#include <time.h>
#include "MyRand.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Model_Cyclic::Model_Cyclic()
{

}

Model_Cyclic::Model_Cyclic(int)
{

}


Model_Cyclic::Model_Cyclic(int rowcol, void * tempPara)
{
	Para = (ParaDlg_Cyclic *) tempPara;

	nStates = Para->m_nStates;
	nRow = rowcol;
	nCol = rowcol;
	nTotal = nRow * nCol;
	pStateArray = new char[nRow * nCol];
	Initialization();
}

Model_Cyclic::~Model_Cyclic()
{

}

void Model_Cyclic::Simulation(int speed, bool record, FILE * fp, int recordcount, SpatialWnd * pSpatial)
{
	nStates = Para->m_nStates;

	nbr = Para->m_nbr;
	for(int iii= 0; iii<nStates; iii++)
	{
		nDistribution[iii] = 0;
		dFreq[iii] = 0;
	}

	if (Para->m_bspark) 
	{ 
		Spark();
		Para->m_bspark = false;
	}

	int nCount = 0;
	
	int i;
	int x2, y2;
	double para[10];
	para[0]= Para->m_a0;  para[1] = Para->m_b1; 
	para[2]= Para->m_a2;  para[3] = Para->m_b3; 
	para[4]= Para->m_a4;  para[5] = Para->m_b5; 
	para[6]= Para->m_a6;  para[7] = Para->m_b7; 
	para[8]= Para->m_a8;  para[9] = Para->m_b9; 
	
	double maxrate = para[0];
	for (i = 1; i < 10; i++)
	{
		if (para[i] > maxrate) maxrate = para[i];
	}

	for(i = 0; i < 10; i++)
	{
		para[i] /= maxrate;
	}
	//normalize. 

	int total = nRow * nCol;
  	
	for (iii = 0; iii < total / speed ; iii++)
		{	
			int x = pRand->IRandom(0, nRow-1);
			int y = pRand->IRandom(0, nCol-1);

			int pos = x * nCol + y;
			
			double dUniform = pRand->Random();
			switch(Para->m_bThreshold)
			{
			case false: //not threshold
				{
					switch (pStateArray[pos])
					{
					case 0:
						
						if ( para[0] > dUniform) 
							pStateArray[pos] = 1;
						break;
					
					case 1:
						
						if (para[1] > dUniform) //open
						{
							int dir = pRand->IRandom(0, nbr-1);
							x2 = (x + nbrX[dir] + nRow) % nRow;
							y2 = (y + nbrY[dir] + nCol) % nCol;
							if (pStateArray[x2 * nCol + y2] == 2)
								pStateArray[pos] = 2;
						}
						break;
					
					case 2:
						
						if ( para[2] > dUniform) 
							pStateArray[pos] = 3;
						break;
					
					case 3:
						
						if (para[3] > dUniform) //open
						{
							int dir = pRand->IRandom(0, nbr-1);
							x2 = (x + nbrX [dir] + nRow) % nRow;
							y2 = (y + nbrY [dir] + nCol) % nCol;
							if (pStateArray[x2 * nCol + y2] == (4 % nStates))
								pStateArray[pos] = (4 % nStates);
						}
						break;

					case 4:
						
						if ( para[4] > dUniform) 
							pStateArray[pos] = 5;
						
						break;

					case 5:
						
						if (para[5] > dUniform) //open
						{
							int dir = pRand->IRandom(0, nbr-1);
							x2 = (x + nbrX [dir] + nRow) % nRow;
							y2 = (y + nbrY [dir] + nCol) % nCol;
							if (pStateArray[x2 * nCol + y2] == (6 % nStates))
								pStateArray[pos] = (6 % nStates);
						}
						break;

					case 6:
						
						if (para[6] > dUniform)
							pStateArray[pos] = 7;
						break;

					case 7:
						
						if (para[7] > dUniform) //open
						{
							int dir = pRand->IRandom(0, nbr-1);
							x2 = (x + nbrX [dir] + nRow) % nRow;
							y2 = (y + nbrY [dir] + nCol) % nCol;
							if (pStateArray[x2 * nCol + y2] == (8 % nStates))
								pStateArray[pos] = (8 % nStates);
						}
						break;

					case 8:
						
						if (para[8] > dUniform)
							pStateArray[pos] = 9;
						break;
							
					case 9:
						
						if (para[9] > dUniform) //open
						{
							int dir = pRand->IRandom(0, nbr-1);
							x2 = (x + nbrX [dir] + nRow) % nRow;
							y2 = (y + nbrY [dir] + nCol) % nCol;
							if (pStateArray[x2 * nCol + y2] == (10 % nStates))
								pStateArray[pos] = (10 % nStates);
						}
						break;
	
					}
				};
				break;
		
	
			case true:
				{
						switch (pStateArray[pos])
						{
						case 0:
							if ( para[0] > dUniform) 
								pStateArray[pos] = 1;
							break;
						
						case 1:
							nCount = 0;
							for (i = 0; i < nbr; i++)
							{
								x2 = (x + nbrX [i] + nRow) % nRow;
								y2 = (y + nbrY [i] + nCol) % nCol;
								if (pStateArray[x2 * nCol + y2] == 2)
									nCount ++;
							}  // count the number of state 2 near state 1;

							if ( nCount >= Para->m_nThreshold && para[1] > dUniform) 
								pStateArray[pos] = 2;
							break;
						
						case 2:
							if ( para[2] > dUniform) 
								pStateArray[pos] = 3;
							break;
						
						case 3:
							nCount = 0;
							for (i = 0; i < nbr; i++)
							{
								x2 = (x + nbrX [i] + nRow) % nRow;
								y2 = (y + nbrY [i] + nCol) % nCol;
								if (pStateArray[x2 * nCol + y2] == (4 % nStates))
									nCount ++;
							}  // count the number of state 4 near state 3;

							if ( nCount >= Para->m_nThreshold && para[3] > dUniform) 
								pStateArray[pos] = (4 % nStates);
							break;


						case 4:
							if ( para[4] > dUniform) 
								pStateArray[pos] = 5;
							break;
						
						case 5:
							nCount = 0;
							for (i = 0; i < nbr; i++)
							{
								x2 = (x + nbrX [i] + nRow) % nRow;
								y2 = (y + nbrY [i] + nCol) % nCol;
								if (pStateArray[x2 * nCol + y2] == (6 % nStates))
									nCount ++;
							}  // count the number of state 6 near state 5;

							if ( nCount >= Para->m_nThreshold && para[5] > dUniform) 
								pStateArray[pos] = (6 % nStates);
							break;
						
						case 6:
							if ( para[6] > dUniform) 
								pStateArray[pos] = 7;
							break;
						
						case 7:
							nCount = 0;
							for (i = 0; i < nbr; i++)
							{
								x2 = (x + nbrX [i] + nRow) % nRow;
								y2 = (y + nbrY [i] + nCol) % nCol;
								if (pStateArray[x2 * nCol + y2] == (8 % nStates))
									nCount ++;
							}  // count the number of state 8 near state 7;

							if ( nCount >= Para->m_nThreshold && para[7] > dUniform) 
								pStateArray[pos] = (8 % nStates);
							break;

						case 8:
							if ( para[8] > dUniform) 
								pStateArray[pos] = 9;
							break;
						
						case 9:
							nCount = 0;
							for (i = 0; i < nbr; i++)
							{
								x2 = (x + nbrX [i] + nRow) % nRow;
								y2 = (y + nbrY [i] + nCol) % nCol;
								if (pStateArray[x2 * nCol + y2] == 0)
									nCount ++;
							}  // count the number of state 2 near state 1;

							if ( nCount >= Para->m_nThreshold && para[9] > dUniform) 
								pStateArray[pos] = 0;
							break;

						
						}

				};
				break;
			}
		
		}
	FreqStat(record, fp, recordcount, pSpatial);
}

void Model_Cyclic::FreqStat(bool record, FILE * fp, int recordcount, SpatialWnd * pSpatial)
{
	int i, j;
	nWndSize = pSpatial->m_wndsize;
	int px = pSpatial->m_posx;
	int py = pSpatial->m_posy;
	for (i=0; i<nWndSize; i++)
		for (j=0; j<nWndSize; j++)
		{
			nDistribution[State((i+px) % nRow, (j+py) % nCol)]++;
		}
	double temp = nWndSize * nWndSize;
	for (i=0; i<nStates; i++)
		dFreq[i] = nDistribution[i] /temp;

	
	if (record && fp!=NULL)
	{
		fprintf(fp, "%d \t %4.2f \t  %4.2f \n", recordcount, dFreq[pSpatial->m_sp1], dFreq[pSpatial->m_sp2]);
	}


}


void Model_Cyclic::Initialization()
{
	nStates = Para->m_nStates;
	int i, j;
	int state;
	double prob;
	switch(Para->m_Init)
	{
	case 0: //random
		for(i = 0; i < nRow * nCol; i++)
			pStateArray[i] = pRand->IRandom(0, nStates-1);
		break;

	case 1: //chessboard
		double r1 = Para->m_r1Density / 100.;
		double s1 = Para->m_r2Density / 100.;
		int nPartition = Para->m_NumPartition;
	//	int nBlockSize = (int) (nRow / (double)nPartition);
		int remain = nRow % nPartition;
		int nBlockSize = (nRow - remain) / nPartition;
		int lx, ly;

		for(i = 0; i < nPartition; i++)
			for (j = 0; j < nPartition; j++)
			{
				state; 
				prob = pRand->Random();
				if ( prob < r1)
					state = 1;
				else if ( prob < r1 + s1)
					state = 3;
				else 
					state = 1 + 2 * pRand->IRandom(1, nStates / 2-1);
				
				for (lx = 0; lx < nBlockSize; lx ++)
					for (ly = 0; ly < nBlockSize; ly++)
						State((i * nBlockSize + lx) , (j * nBlockSize + ly) ) = state;
					
			}

		if (remain != 0)
		{
			
			for (j=0; j< nPartition; j++)
				{
					state; 
					prob = pRand->Random();
					if ( prob < r1)
						state = 1;
					else if ( prob < r1 + s1)
						state = 3;
					else 
						state = 1 + 2 * pRand->IRandom(1, nStates / 2-1);
					for (i=nPartition * nBlockSize; i < nRow; i++ )
						for (ly = 0; ly < nBlockSize; ly++)
							State(i, (j*nBlockSize + ly)) = state;
				}

			
			for (i=0; i< nPartition; i++)
				{
					state; 
					prob = pRand->Random();
					if ( prob < r1)
						state = 1;
					else if ( prob < r1 + s1)
						state = 3;
					else 
						state = 1 + 2 * pRand->IRandom(1, nStates / 2-1);
					for (lx = 0; lx < nBlockSize; lx++)
						for (j=nPartition * nBlockSize; j < nRow; j++ )
						State((i*nBlockSize + lx), j) = state;
				}

			state = 1+2 * pRand->IRandom(0, nStates / 2-1);
			for (i=nPartition * nBlockSize; i < nRow; i++ )
				for (j=nPartition * nBlockSize; j < nRow; j++ )
				{
					State(i,j)=state;

				}

		}
		
		
		break;
	}
	

}


void Model_Cyclic::Spark()
{
	double prob = Para->m_sparkdensity * 0.01; 
	for (int i = 0; i < nTotal; i++)
	{
		if (pRand->Random() < prob)
			pStateArray[i] = 2 * pRand->IRandom(0, nStates/2 - 1);

	}

}