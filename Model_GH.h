// Model_GH.h: interface for the Model_GH class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MODEL_GH_H__50AD3C29_AD76_42E8_AF0A_6B79112BF721__INCLUDED_)
#define AFX_MODEL_GH_H__50AD3C29_AD76_42E8_AF0A_6B79112BF721__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ModelTemplate.h"
#include "ParaDlg_GH.h"

class Model_GH : public ModelTemplate
{
public:
	ParaDlg_GH * Para;
public:
	void Simulation(SpatialWnd *, int);
	void Initialization();
	Model_GH();
	Model_GH(int);
	Model_GH(int, void *);
	virtual ~Model_GH();

};

#endif // !defined(AFX_MODEL_GH_H__50AD3C29_AD76_42E8_AF0A_6B79112BF721__INCLUDED_)
