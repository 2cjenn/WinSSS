// ModelTemplate.h: interface for the ModelTemplate class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MODELTEMPLATE_H__FCF2B8E1_454C_4E5F_BACE_4F04E2E37410__INCLUDED_)
#define AFX_MODELTEMPLATE_H__FCF2B8E1_454C_4E5F_BACE_4F04E2E37410__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



#include "sssWnd.h"
#include "MyRand.h"
#include "SpatialWnd.h"

#define State(i, j)  pStateArray[(i) + ((j) * nRow)]


class ModelTemplate
{
protected: 
	int nMaxStates; 
	int nStates; //number of the states in this model;
	int nCol;
	int nRow;  //rows and columns numbers of the map; 
	int nDistribution[16];
	int nbr;
	int nbrX[24];
    int nbrY[24];
	int nbrFX[40];
	int nbrFY[40];
	int nbrTX[80];
	int nbrTY[80];
	int nTotal;
	int nWndSize; // window size for freq.
	double ** timerArray;
	int nTimers;
	int action;
	int xLocation;
	int yLocation;
	double minTimer;

public: 
	MyRand * pRand;
	
	double dStateColors[16][3]; //(a,b,c) assign a color to each state;
	char * pStateArray; //maximum 16 states;	
	double dFreq[16]; //the frequency array of each states;
	int * dPermutation;

public:
	void FreqStat(SpatialWnd *);
	int GetCol();
	int GetRow();
	
	
	friend void sssWnd::DrawPhasePortrait(void *, double,int, int, int);
	friend void sssWnd::Paint(void *, double);
	friend void sssWnd::Drawlines(void *, int, int, double);
	ModelTemplate();
	ModelTemplate(int);
	ModelTemplate(int, void *);
	virtual ~ModelTemplate();
	

protected:	
	void Simulation(); //simulation method that need to be overloaded. 
	void FreqStat();   //calc the freq. of each species within a window whose size is given by nWndSize show by drwaline()
	



};

#endif // !defined(AFX_MODELTEMPLATE_H__FCF2B8E1_454C_4E5F_BACE_4F04E2E37410__INCLUDED_)
