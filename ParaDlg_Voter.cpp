// ParaDlg_Voter1.cpp : implementation file
//

#include "stdafx.h"
#include "sss.h"
#include "ParaDlg_Voter.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ParaDlg_Voter dialog


ParaDlg_Voter::ParaDlg_Voter(CWnd* pParent /*=NULL*/)
	: CDialog(ParaDlg_Voter::IDD, pParent)
{
	//{{AFX_DATA_INIT(ParaDlg_Voter)

	m_nStates = 4;

	m_bThreshold = FALSE;
	m_nbr = 4;
	m_nThreshold = 1;
	//}}AFX_DATA_INIT
}


void ParaDlg_Voter::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ParaDlg_Voter)
	DDX_Control(pDX, IDC_CHECK_Threshold, m_CheckThreshold);
	DDX_Control(pDX, IDC_EDIT_Threshold, m_EditThreshold);
	DDX_Control(pDX, IDC_COMBO_Nbr, m_ComboNbr);
	
	DDX_Control(pDX, IDC_EDIT_NUM_STATES, m_EditStates);
	

	DDX_Text(pDX, IDC_EDIT_NUM_STATES, m_nStates);
	DDV_MinMaxInt(pDX, m_nStates, 2, 10);

	DDX_Check(pDX, IDC_CHECK_Threshold, m_bThreshold);
	DDX_Text(pDX, IDC_EDIT_Threshold, m_nThreshold);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ParaDlg_Voter, CDialog)
	//{{AFX_MSG_MAP(ParaDlg_Voter)
	ON_CBN_SELCHANGE(IDC_COMBO_Nbr, OnSelchangeCOMBONbr)
	ON_BN_CLICKED(IDC_CHECK_Threshold, OnCHECKThreshold)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ParaDlg_Voter message handlers





BOOL ParaDlg_Voter::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_ComboNbr.AddString("Four Direct");
	m_ComboNbr.AddString("Eight Square");
	m_ComboNbr.AddString("Twenty-Four");
	switch(m_nbr)
	{
	case 4:
		m_ComboNbr.SetCurSel(0);
		break;
	case 8:
		m_ComboNbr.SetCurSel(1);
		break;
	case 24:
		m_ComboNbr.SetCurSel(2);
		break;

	}
	
	if (m_bThreshold)
	{
		m_EditThreshold.EnableWindow();
		m_CheckThreshold.SetCheck(TRUE);
	}
	else
	{
		m_EditThreshold.EnableWindow(FALSE);
		m_CheckThreshold.SetCheck(FALSE);
	}

	
	
//	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}



void ParaDlg_Voter::OnSelchangeCOMBONbr() 
{
	switch(m_ComboNbr.GetCurSel())
	{
	case 0:
		m_nbr = 4;
		break;
	case 1:
		m_nbr = 8;
		break;
	case 2:
		m_nbr = 24;
		break;
	}
}

void ParaDlg_Voter::OnCHECKThreshold() 
{
	m_bThreshold = !m_bThreshold;
	if (m_bThreshold)
		m_EditThreshold.EnableWindow();
	else
		m_EditThreshold.EnableWindow(FALSE);

}
