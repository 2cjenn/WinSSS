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

class Model_Contact : public ModelTemplate  
{
public:
	ParaDlg_Contact * Para;
public:

	void Simulation(SpatialWnd *, int);
	void Initialization();
	Model_Contact();
	Model_Contact(int);
	Model_Contact(int, void*);
	virtual ~Model_Contact();

private:

};

#endif // !defined(AFX_MODEL_CONTACT_H__29FB1784_B05C_4412_BB07_D2BBA2E18D43__INCLUDED_)
