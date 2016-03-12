// Model_LVoter.h: interface for the Model_LVoter class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MODEL_LVOTER_H__AEDB6FC6_1CB4_4610_BC1F_5F5D2B4EBD27__INCLUDED_)
#define AFX_MODEL_LVOTER_H__AEDB6FC6_1CB4_4610_BC1F_5F5D2B4EBD27__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ModelTemplate.h"
#include "ParaDlg_Voter.h"

class Model_LVoter : public ModelTemplate 
{
public:

	void Initialization();
	void Simulation(SpatialWnd *, int);
	Model_LVoter(int, void *);
	Model_LVoter();
	virtual ~Model_LVoter();
	ParaDlg_Voter * Para;

};

#endif // !defined(AFX_MODEL_LVOTER_H__AEDB6FC6_1CB4_4610_BC1F_5F5D2B4EBD27__INCLUDED_)
