// ParaDlg_MultiCont.cpp : implementation file
//

#include "stdafx.h"
#include "sss.h"
#include "ParaDlg_MultiCont.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ParaDlg_MultiCont dialog


ParaDlg_MultiCont::ParaDlg_MultiCont(CWnd* pParent /*=NULL*/)
	: CDialog(ParaDlg_MultiCont::IDD, pParent)
{
	//{{AFX_DATA_INIT(ParaDlg_MultiCont)
	m_birth1 = 0.25f;
	m_birth2 = 3.0f;
	m_death1 = 0.5f;
	m_death2 = 0.5f;
	//}}AFX_DATA_INIT
}


void ParaDlg_MultiCont::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ParaDlg_MultiCont)
	DDX_Text(pDX, IDC_EDIT_Birth1, m_birth1);
	DDX_Text(pDX, IDC_EDIT_Birth2, m_birth2);
	DDX_Text(pDX, IDC_EDIT_Death1, m_death1);
	DDX_Text(pDX, IDC_EDIT_Death2, m_death2);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ParaDlg_MultiCont, CDialog)
	//{{AFX_MSG_MAP(ParaDlg_MultiCont)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ParaDlg_MultiCont message handlers
