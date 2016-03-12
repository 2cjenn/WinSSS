// sss.h : main header file for the SSS application
//

#if !defined(AFX_SSS_H__8FBB8E3E_D686_4860_9020_7AA99634F001__INCLUDED_)
#define AFX_SSS_H__8FBB8E3E_D686_4860_9020_7AA99634F001__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSssApp:
// See sss.cpp for the implementation of this class
//

class CSssApp : public CWinApp
{
public:
	CSssApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSssApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSssApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SSS_H__8FBB8E3E_D686_4860_9020_7AA99634F001__INCLUDED_)
