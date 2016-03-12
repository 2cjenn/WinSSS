#if !defined(AFX_PARADLG_MULTICONT_H__D766CF54_DDAB_4F68_9DFB_073BEF551E08__INCLUDED_)
#define AFX_PARADLG_MULTICONT_H__D766CF54_DDAB_4F68_9DFB_073BEF551E08__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ParaDlg_MultiCont.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ParaDlg_MultiCont dialog

class ParaDlg_MultiCont : public CDialog
{
// Construction
public:
	ParaDlg_MultiCont(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(ParaDlg_MultiCont)
	enum { IDD = IDD_PARAMULTICONTACT };
	float	m_birth1;
	float	m_birth2;
	float	m_death1;
	float	m_death2;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ParaDlg_MultiCont)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ParaDlg_MultiCont)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PARADLG_MULTICONT_H__D766CF54_DDAB_4F68_9DFB_073BEF551E08__INCLUDED_)
