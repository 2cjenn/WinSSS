#if !defined(AFX_PARADLG_CONTACT1_H__9DC2FE9E_9E18_4CEA_B63A_18C8B6E3F939__INCLUDED_)
#define AFX_PARADLG_CONTACT1_H__9DC2FE9E_9E18_4CEA_B63A_18C8B6E3F939__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ParaDlg_Contact.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ParaDlg_Contact dialog

class ParaDlg_Contact : public CDialog
{
// Construction
public:
	ParaDlg_Contact(CWnd* pParent = NULL);   // standard constructor
	int	m_nStates;
	int m_init;
// Dialog Data
	//{{AFX_DATA(ParaDlg_Contact)
	enum { IDD = IDD_PARACONTACT };
	CComboBox	m_initsetting;
	float	m_a0;
	float	m_a1;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ParaDlg_Contact)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ParaDlg_Contact)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComboInit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PARADLG_CONTACT1_H__9DC2FE9E_9E18_4CEA_B63A_18C8B6E3F939__INCLUDED_)
