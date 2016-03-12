// Model_EP.h: interface for the Model_EP class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MODEL_EP_H__01EE66B4_6CDF_4E98_A00E_F0AF079B1652__INCLUDED_)
#define AFX_MODEL_EP_H__01EE66B4_6CDF_4E98_A00E_F0AF079B1652__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ModelTemplate.h"
#include "ParaDlg_Ep.h"

class Model_EP : public ModelTemplate 
{
public: 
	ParaDlg_Ep * Para;

public:
	void Initialization();
	void Simulation(SpatialWnd *, int);
	Model_EP();
	Model_EP(int);
	Model_EP(int, void *);
	virtual ~Model_EP();

	
};

#endif // !defined(AFX_MODEL_EP_H__01EE66B4_6CDF_4E98_A00E_F0AF079B1652__INCLUDED_)
