#if !defined(AFX_PARADLG_Cyclic_H__A28F6AA2_6609_4BBA_AEBC_5D7216C64013__INCLUDED_)
#define AFX_PARADLG_Cyclic_H__A28F6AA2_6609_4BBA_AEBC_5D7216C64013__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ParaDlg_Cyclic.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ParaDlg_Cyclic dialog

class ParaDlg_Cyclic : public CDialog
{
// Construction
public:
	ParaDlg_Cyclic(CWnd* pParent = NULL);   // standard constructor

	int m_nbr;
	int m_nStates;
// Dialog Data
	//{{AFX_DATA(ParaDlg_Cyclic)
	enum { IDD = IDD_PARACYCLIC };
	CComboBox	m_nbrsize;
	CComboBox	m_numstates;
	CEdit	m_Dens2;
	CEdit	m_Dens1;
	CEdit	m_Partition;
	CButton	m_Rand;
	CButton	m_Chess;
	float	m_a0;
	float	m_b1;
	float	m_a2;
	float	m_b3;
	float	m_a4;
	float	m_b5;
	float	m_a6;
	float	m_b7;
	float	m_a8;
	float	m_b9;
	int		m_nThreshold;
	BOOL	m_bThreshold;
	float	m_sparkdensity;
	BOOL	m_bspark;
	int		m_Init;
	BOOL	m_icChess;
	BOOL	m_icRand;
	float	m_r1Density;
	float	m_r2Density;
	int		m_NumPartition;
	
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ParaDlg_Cyclic)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ParaDlg_Cyclic)
	virtual BOOL OnInitDialog();
	afx_msg void OnThreshold();
	afx_msg void OnSpark();
	afx_msg void OnCheckIcRand();
	afx_msg void OnCheckIcChess();
	afx_msg void OnSelchangeNumStates();
	afx_msg void OnSelchangeNbrSize();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PARADLG_Cyclic_H__A28F6AA2_6609_4BBA_AEBC_5D7216C64013__INCLUDED_)
