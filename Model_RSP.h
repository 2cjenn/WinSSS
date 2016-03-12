// Model_RSP.h: interface for the Model_RSP class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MODEL_RSP_H__923E0F46_595B_4F38_9DC3_625D8CA1CD98__INCLUDED_)
#define AFX_MODEL_RSP_H__923E0F46_595B_4F38_9DC3_625D8CA1CD98__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ModelTemplate.h"
#include "ParaDlg_RSP.h"
class Model_RSP : public ModelTemplate 
{
public:
	ParaDlg_RSP * Para;

public:
	void Initialization();
	void Simulation(SpatialWnd *, int);
	Model_RSP(int);
	Model_RSP();
	Model_RSP(int, void *);
	virtual ~Model_RSP();

};

#endif // !defined(AFX_MODEL_RSP_H__923E0F46_595B_4F38_9DC3_625D8CA1CD98__INCLUDED_)
