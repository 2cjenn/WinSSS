// ParaDlg_Contact1.cpp : implementation file
//

#include "stdafx.h"
#include "sss.h"
#include "ParaDlg_Contact.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ParaDlg_Contact dialog

ParaDlg_Contact::ParaDlg_Contact(CWnd* pParent /*=NULL*/)
	: CDialog(ParaDlg_Contact::IDD, pParent)
{
	//{{AFX_DATA_INIT(ParaDlg_Contact)
	m_a0 = 1.5f;
	m_a1 = 1.0f;
	m_init = 0;
	m_nStates = 2;
	//}}AFX_DATA_INIT
}




void ParaDlg_Contact::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ParaDlg_Contact)
	DDX_Control(pDX, IDC_COMBO_INIT, m_initsetting);
	DDX_Text(pDX, IDC_EDIT1, m_a0);
	DDX_Text(pDX, IDC_EDIT2, m_a1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ParaDlg_Contact, CDialog)
	//{{AFX_MSG_MAP(ParaDlg_Contact)
	ON_CBN_SELCHANGE(IDC_COMBO_INIT, OnSelchangeComboInit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ParaDlg_Contact message handlers

BOOL ParaDlg_Contact::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_initsetting.AddString("Random");
	m_initsetting.AddString("Center");
	if (m_init == 0)
		m_initsetting.SetCurSel(0);
	else 
		m_initsetting.SetCurSel(1);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}



void ParaDlg_Contact::OnSelchangeComboInit() 
{
	switch(m_initsetting.GetCurSel())
	{
	case 0: 
		m_init = 0;
		break;
	case 1: 
		m_init = 1;
		break;
	}		
}
