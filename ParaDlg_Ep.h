#if !defined(AFX_PARADLG_EP_H__64BBDB56_66E2_449D_AAA3_3059F2474948__INCLUDED_)
#define AFX_PARADLG_EP_H__64BBDB56_66E2_449D_AAA3_3059F2474948__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ParaDlg_Ep.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ParaDlg_Ep dialog

class ParaDlg_Ep : public CDialog
{
// Construction
public:
	int nInitID;
public:
	ParaDlg_Ep(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(ParaDlg_Ep)
	enum { IDD = IDD_PARAEP };
	CListBox	m_listbox;
	float	m_infection;
	float	m_death;
	float	m_rebirth;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ParaDlg_Ep)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ParaDlg_Ep)
	virtual BOOL OnInitDialog();
	virtual void OnSelchangeList();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PARADLG_EP_H__64BBDB56_66E2_449D_AAA3_3059F2474948__INCLUDED_)
