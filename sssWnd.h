#if !defined(AFX_SSSWND_H__B893C4C2_4341_4D34_BCF3_A6E38691440A__INCLUDED_)
#define AFX_SSSWND_H__B893C4C2_4341_4D34_BCF3_A6E38691440A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// sssWnd.h : header file
//

#include "gl\glu.h"

/////////////////////////////////////////////////////////////////////////////
// sssWnd window

class sssWnd : public CStatic
{
// Construction
public:
	sssWnd();

public:
	void DisableOpenGL();
	void EnableOpenGL();
	CSize GetWnd();

public:
	HGLRC  hRC;
	HDC  hDC;

//	GLUquadricObj *qObj;

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(sssWnd)
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	void DrawLegend(void *, int);
	void DrawPhasePortrait(void *, double, int, int, int);
	void Drawlines(void *, int, int, double);
	void Paint(void *, double);
	virtual ~sssWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(sssWnd)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SSSWND_H__B893C4C2_4341_4D34_BCF3_A6E38691440A__INCLUDED_)


