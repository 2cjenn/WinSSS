// ParaDlg_Ep.cpp : implementation file
//

#include "stdafx.h"
#include "sss.h"
#include "ParaDlg_Ep.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ParaDlg_Ep dialog


ParaDlg_Ep::ParaDlg_Ep(CWnd* pParent /*=NULL*/)
	: CDialog(ParaDlg_Ep::IDD, pParent)
{
	//{{AFX_DATA_INIT(ParaDlg_Ep)
	m_infection = 2.0f;
	m_death = 0.1f;
	m_rebirth = 0.04f;
	//}}AFX_DATA_INIT

	nInitID = 0;
	
	
}


void ParaDlg_Ep::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ParaDlg_Ep)
	DDX_Control(pDX, IDC_LIST, m_listbox);
	DDX_Text(pDX, IDC_EDIT1, m_infection);
	DDX_Text(pDX, IDC_EDIT2, m_death);
	DDX_Text(pDX, IDC_EDIT3, m_rebirth);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ParaDlg_Ep, CDialog)
	//{{AFX_MSG_MAP(ParaDlg_Ep)
	ON_LBN_SELCHANGE(IDC_LIST, OnSelchangeList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ParaDlg_Ep message handlers






void ParaDlg_Ep::OnSelchangeList() 
{
	nInitID = m_listbox.GetCurSel();
	
}

BOOL ParaDlg_Ep::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_listbox.AddString("Center");
	m_listbox.AddString("Random");
	m_listbox.SetCurSel(nInitID);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
