// ParaDlg_GH.cpp : implementation file
//

#include "stdafx.h"
#include "sss.h"
#include "ParaDlg_GH.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ParaDlg_GH dialog


ParaDlg_GH::ParaDlg_GH(CWnd* pParent /*=NULL*/)
	: CDialog(ParaDlg_GH::IDD, pParent)
{
	
	//{{AFX_DATA_INIT(ParaDlg_GH)
	m_cbirth = 3.0f;
	m_death1 = 1.0f;
	m_death2 = 1.0f;
	m_death3 = 1.0f;
	m_death4 = 1.0f;
	m_death5 = 1.0f;
	m_death6 = 1.0f;
	m_death7 = 1.0f;
	m_nThreshold = 3;
	m_nbr = 24;
	//}}AFX_DATA_INIT
}


void ParaDlg_GH::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ParaDlg_GH)
	DDX_Control(pDX, IDC_LIST1, m_listnbr);
	DDX_Text(pDX, IDC_EDIT1, m_cbirth);
	DDX_Text(pDX, IDC_EDIT2, m_death1);
	DDX_Text(pDX, IDC_EDIT3, m_death2);
	DDX_Text(pDX, IDC_EDIT4, m_death3);
	DDX_Text(pDX, IDC_EDIT5, m_death4);
	DDX_Text(pDX, IDC_EDIT6, m_death5);
	DDX_Text(pDX, IDC_EDIT7, m_death6);
	DDX_Text(pDX, IDC_EDIT8, m_death7);
	DDX_Text(pDX, IDC_EDIT9, m_nThreshold);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ParaDlg_GH, CDialog)
	//{{AFX_MSG_MAP(ParaDlg_GH)
	ON_LBN_SELCHANGE(IDC_LIST1, OnSelchangeNbr)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ParaDlg_GH message handlers

BOOL ParaDlg_GH::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_listnbr.AddString("Four Direct");
	m_listnbr.AddString("Eight Squre");
	m_listnbr.AddString("24 Neighbors");
	if (m_nbr == 4) 
		m_listnbr.SetCurSel(0);
	else if (m_nbr == 8)
		m_listnbr.SetCurSel(1);
	else if (m_nbr == 24)
		m_listnbr.SetCurSel(2);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void ParaDlg_GH::OnSelchangeNbr() 
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
