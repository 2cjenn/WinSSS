#if !defined(AFX_PARADLG_GH_H__137CF931_74A4_413E_9900_07155CEB5F54__INCLUDED_)
#define AFX_PARADLG_GH_H__137CF931_74A4_413E_9900_07155CEB5F54__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ParaDlg_GH.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ParaDlg_GH dialog

class ParaDlg_GH : public CDialog
{
// Construction
public:
	ParaDlg_GH(CWnd* pParent = NULL);   // standard constructor

	int m_nbr;
// Dialog Data
	//{{AFX_DATA(ParaDlg_GH)
	enum { IDD = IDD_PARAGH };
	CListBox	m_listnbr;
	float	m_cbirth;
	float	m_death1;
	float	m_death2;
	float	m_death3;
	float	m_death4;
	float	m_death5;
	float	m_death6;
	float	m_death7;
	int		m_nThreshold;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ParaDlg_GH)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ParaDlg_GH)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeNbr();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PARADLG_GH_H__137CF931_74A4_413E_9900_07155CEB5F54__INCLUDED_)
