// Model_MultiContact.h: interface for the Model_MultiContact class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MODEL_MULTICONTACT_H__37645924_9B93_425B_8A50_62602C60AC7F__INCLUDED_)
#define AFX_MODEL_MULTICONTACT_H__37645924_9B93_425B_8A50_62602C60AC7F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ModelTemplate.h"
#include "ParaDlg_MultiCont.h"
#include <random>

class Model_MultiContact : public ModelTemplate 
{

public:
	ParaDlg_MultiCont * Para;
	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution;

public:

	void Simulation(SpatialWnd *, int);
	void Initialization();
	void ResetTimers();
	char * ModState(int, int);
	Model_MultiContact();
	Model_MultiContact(int);
	Model_MultiContact(int, void*);
	virtual ~Model_MultiContact();


};

#endif // !defined(AFX_MODEL_MULTICONTACT_H__37645924_9B93_425B_8A50_62602C60AC7F__INCLUDED_)
