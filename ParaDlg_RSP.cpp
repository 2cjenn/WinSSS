// ParaDlg_RSP.cpp : implementation file
//

#include "stdafx.h"
#include "sss.h"
#include "ParaDlg_RSP.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ParaDlg_RSP dialog


ParaDlg_RSP::ParaDlg_RSP(CWnd* pParent /*=NULL*/)
	: CDialog(ParaDlg_RSP::IDD, pParent)
{
	//{{AFX_DATA_INIT(ParaDlg_RSP)
	m_d01 = 1.0f;
	m_d12 = 1.0f;
	m_d20 = 1.0f;
	m_d3 = 1.0f;
	m_d4 = 1.0f;
	m_d5 = 1.0f;
	m_d6 = 1.0f;
	m_d7 = 1.0f;
	m_nStates = 6;
	m_bthreshold = FALSE;
	m_nbr = 8;
	m_nthreshold = 1;
	//}}AFX_DATA_INIT
}


void ParaDlg_RSP::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ParaDlg_RSP)
	DDX_Control(pDX, IDC_LIST1, m_listnbr);
	DDX_Text(pDX, IDC_EDIT1, m_d01);
	DDX_Text(pDX, IDC_EDIT2, m_d12);
	DDX_Text(pDX, IDC_EDIT3, m_d20);
	DDX_Text(pDX, IDC_EDIT4, m_d3);
	DDX_Text(pDX, IDC_EDIT5, m_d4);
	DDX_Text(pDX, IDC_EDIT6, m_d5);
	DDX_Text(pDX, IDC_EDIT7, m_d6);
	DDX_Text(pDX, IDC_EDIT8, m_d7);
	DDX_Text(pDX, IDC_EDIT9, m_nStates);
	DDV_MinMaxInt(pDX, m_nStates, 3, 8);
	DDX_Check(pDX, IDC_CHECK1, m_bthreshold);
	DDX_Text(pDX, IDC_EDIT10, m_nthreshold);
	//}}AFX_DATA_MAP

	
}


BEGIN_MESSAGE_MAP(ParaDlg_RSP, CDialog)
	//{{AFX_MSG_MAP(ParaDlg_RSP)
	ON_LBN_SELCHANGE(IDC_LIST1, OnSelchangeNbr)
	ON_BN_CLICKED(IDC_CHECK1, OnThreshold)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ParaDlg_RSP message handlers





BOOL ParaDlg_RSP::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_listnbr.AddString("4 nbrs");
	m_listnbr.AddString("8 nbrs");
	m_listnbr.AddString("24 nbrs");
	m_listnbr.SetCurSel(0);

	if (m_nbr == 4) 
		m_listnbr.SetCurSel(0);
	else if (m_nbr == 8)
		m_listnbr.SetCurSel(1);
	else if (m_nbr == 24)
		m_listnbr.SetCurSel(2);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void ParaDlg_RSP::OnSelchangeNbr() 
{
	switch(m_listnbr.GetCurSel())
	{
	case 0: m_nbr = 4;
		break;
	case 1: m_nbr = 8;
		break;
	case 2: m_nbr = 24;
		break;
	}
	
}

void ParaDlg_RSP::OnThreshold() 
{
	m_bthreshold = !m_bthreshold;
	
}
