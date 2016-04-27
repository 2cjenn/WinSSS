// Model_Contact.h: interface for the Model_Contact class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MODEL_CONTACT_H__29FB1784_B05C_4412_BB07_D2BBA2E18D43__INCLUDED_)
#define AFX_MODEL_CONTACT_H__29FB1784_B05C_4412_BB07_D2BBA2E18D43__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ModelTemplate.h"
#include "ParaDlg_Contact.h"
#include <random>

class Model_Contact : public ModelTemplate  
{
public:
	ParaDlg_Contact * Para;

	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution;
public:

	void Simulation(SpatialWnd *, int);
	void Initialization();
	void ResetTimers();
	char * ModState(int, int);
	Model_Contact();
	Model_Contact(int);
	Model_Contact(int, void*);
	virtual ~Model_Contact();

private:

};

#endif // !defined(AFX_MODEL_CONTACT_H__29FB1784_B05C_4412_BB07_D2BBA2E18D43__INCLUDED_)
