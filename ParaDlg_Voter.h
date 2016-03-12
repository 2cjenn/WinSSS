#if !defined(AFX_PARADLG_VOTER_H__C4553AD1_836B_4262_A2B0_8CDA1356BA57__INCLUDED_)
#define AFX_PARADLG_VOTER_H__C4553AD1_836B_4262_A2B0_8CDA1356BA57__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ParaDlg_Voter.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ParaDlg_Voter dialog

class ParaDlg_Voter : public CDialog
{
// Construction
public:
	ParaDlg_Voter(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(ParaDlg_Voter)
	enum { IDD = IDD_PARAVOTER };
	CButton	m_CheckThreshold;
	CEdit	m_EditThreshold;
	CComboBox	m_ComboNbr;

	CEdit	m_EditStates;

	BOOL	m_bLinear;
	BOOL	m_bNonlinear;
	int		m_nStates;

	BOOL	m_bThreshold;
	int		m_nThreshold;
	//}}AFX_DATA

	int m_nbr;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ParaDlg_Voter)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ParaDlg_Voter)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeCOMBONbr();
	afx_msg void OnCHECKThreshold();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PARADLG_VOTER_H__C4553AD1_836B_4262_A2B0_8CDA1356BA57__INCLUDED_)
