#if !defined(AFX_PARADLG_RSP_H__F85A247D_CF24_4E97_AD4F_46DF593D50F0__INCLUDED_)
#define AFX_PARADLG_RSP_H__F85A247D_CF24_4E97_AD4F_46DF593D50F0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ParaDlg_RSP.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ParaDlg_RSP dialog

class ParaDlg_RSP : public CDialog
{
// Construction
public:
	ParaDlg_RSP(CWnd* pParent = NULL);   // standard constructor

	int m_nbr;

	// Dialog Data
	//{{AFX_DATA(ParaDlg_RSP)
	enum { IDD = IDD_PARARSP };
	CListBox	m_listnbr;
	float	m_d01;
	float	m_d12;
	float	m_d20;
	float	m_d3;
	float	m_d4;
	float	m_d5;
	float	m_d6;
	float	m_d7;
	int		m_nStates;
	BOOL	m_bthreshold;
	int		m_nthreshold;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ParaDlg_RSP)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ParaDlg_RSP)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeNbr();
	afx_msg void OnThreshold();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PARADLG_RSP_H__F85A247D_CF24_4E97_AD4F_46DF593D50F0__INCLUDED_)
