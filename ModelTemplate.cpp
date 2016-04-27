// ModelTemplate.cpp: implementation of the ModelTemplate class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "sss.h"
#include "ModelTemplate.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////



ModelTemplate::ModelTemplate()
{
	dStateColors[0][0]= 0.0;dStateColors[0][1]= 0.6;dStateColors[0][2]= 0.0;	//green
	dStateColors[1][0]= 1.0;dStateColors[1][1]= 1.0;dStateColors[1][2]= 0.0;	//yellow
	dStateColors[2][0]= 1.0;dStateColors[2][1]= 0.0;dStateColors[2][2]= 0.0;	//red
	dStateColors[3][0]= 0.5;dStateColors[3][1]= 0.5;dStateColors[3][2]= 0.5;	
	dStateColors[4][0]= 0.0;dStateColors[4][1]= 1.0;dStateColors[4][2]= 1.0;
	dStateColors[5][0]= 1.0;dStateColors[5][1]= 0.0;dStateColors[5][2]= 1.0;	//grey
	dStateColors[6][0]= 0.2;dStateColors[6][1]= 0.4;dStateColors[6][2]= 0.6;	//grey
	dStateColors[7][0]= 0.6;dStateColors[7][1]= 0.4;dStateColors[7][2]= 0.2;
	dStateColors[8][0]= 0.4;dStateColors[8][1]= 0.6;dStateColors[8][2]= 0.2;
	dStateColors[9][0]= 0.4;dStateColors[9][1]= 0.2;dStateColors[9][2]= 0.6;
	
	

	nbrX[0] = 1; nbrX[1]= -1; nbrX[2] = 0; nbrX[3]= 0;
	nbrX[4] = 1; nbrX[5]= -1; nbrX[6] = 1; nbrX[7]= -1;

	nbrY[0] = 0; nbrY[1]= 0; nbrY[2] = -1; nbrY[3]= 1;
	nbrY[4] = -1; nbrY[5]= 1; nbrY[6] = 1; nbrY[7]= -1;

	nbrX[8] = 2; nbrY[8] = 0;
	nbrX[9] = 2; nbrY[9] = -1;
	nbrX[10] = 2; nbrY[10] = -2;
	nbrX[11] = 1; nbrY[11] = -2;
	nbrX[12] = 0; nbrY[12] = -2;
	nbrX[13] = -1; nbrY[13] = -2;
	nbrX[14] = -2; nbrY[14] = -2;
	nbrX[15] = -2; nbrY[15] = -1;
	nbrX[16] = -2; nbrY[16] = 0;
	nbrX[17] = -2; nbrY[17] = 1;
	nbrX[18] = -2; nbrY[18] = 2;
	nbrX[19] = -1; nbrY[19] = 2;
	nbrX[20] = 0; nbrY[20] = 2;
	nbrX[21] = 1; nbrY[21] = 2;
	nbrX[22] = 2; nbrY[22] = 2;
	nbrX[23] = 2; nbrY[23] = 1;

	pRand = new MyRand(0);

	//r = 5
	for (int i = 0; i < 11; i++)
	{
		nbrFX[i] = 5;
		nbrFY[i] = 5 - i;
	}
	for (int i = 11; i < 20; i++)
	{
		nbrFX[i] = 15 - i;
		nbrFY[i] = -5;
	}
	for (int i = 20; i < 31; i++)
	{
		nbrFX[i] = -5;
		nbrFY[i] = i - 25;
	}
	for (int i = 31; i < 40; i++)
	{
		nbrFX[i] = i - 35;
		nbrFY[i] = 5;
	}

	//r = 10
	for (int i = 0; i < 21; i++)
	{
		nbrTX[i] = 10;
		nbrTY[i] = 10 - i;
	}
	for (int i = 21; i < 40; i++)
	{
		nbrTX[i] = 30 - i;
		nbrTY[i] = -10;
	}
	for (int i = 40; i < 61; i++)
	{
		nbrTX[i] = -10;
		nbrTY[i] = i - 50;
	}
	for (int i = 61; i < 80; i++)
	{
		nbrTX[i] = i - 70;
		nbrTY[i] = 10;
	}
}

ModelTemplate::ModelTemplate(int rowcol)
{
	
}

ModelTemplate::~ModelTemplate()
{
	delete pStateArray;
}

void ModelTemplate::FreqStat()
{

	int i, j;
	for (i=0; i<nWndSize; i++)
		for (j=0; j<nWndSize; j++)
		{
			nDistribution[State(i,j)]++;
		}
	double temp = nWndSize * nWndSize;
	for (i=0; i<nStates; i++)
		dFreq[i] = nDistribution[i] /temp;

}

int ModelTemplate::GetRow()
{
	return nRow;

}

int ModelTemplate::GetCol()
{
	return nCol;
}

void ModelTemplate::FreqStat(SpatialWnd * pSpatial)
{
	nWndSize = pSpatial->m_wndsize;
	int px = pSpatial->m_posx;
	int py = pSpatial->m_posy;

	int i, j;
	for (i=0; i<nWndSize; i++)
		for (j=0; j<nWndSize; j++)
		{
			nDistribution[State((i+px)%nRow,(j+py)%nCol)]++;
		}
	double temp = (double) (nWndSize * nWndSize);
	for (i=0; i<nStates; i++)
		dFreq[i] = (double)nDistribution[i] /temp;

}
