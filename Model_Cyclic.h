// Model_Cyclic.h: interface for the Model_Cyclic class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MODEL_CYCLIC_H__126EBB33_517A_434F_9BAF_09826952294E__INCLUDED_)
#define AFX_MODEL_CYCLIC_H__126EBB33_517A_434F_9BAF_09826952294E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ModelTemplate.h"
#include "ParaDlg_Cyclic.h"


class Model_Cyclic : public ModelTemplate 
{
public:
	ParaDlg_Cyclic * Para;
public:

	void Initialization();
	void Simulation(int, bool, FILE *, int, SpatialWnd *);
	void Spark();
	void FreqStat(bool, FILE *, int, SpatialWnd *);

	Model_Cyclic();
	Model_Cyclic(int);
	Model_Cyclic(int, void *);
	virtual ~Model_Cyclic();

};

#endif // !defined(AFX_MODEL_CYCLIC_H__126EBB33_517A_434F_9BAF_09826952294E__INCLUDED_)
