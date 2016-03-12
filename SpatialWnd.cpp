// SpatialWnd.cpp : implementation file
//

#include "stdafx.h"
#include "sss.h"
#include "SpatialWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SpatialWnd dialog


SpatialWnd::SpatialWnd(CWnd* pParent /*=NULL*/)
	: CDialog(SpatialWnd::IDD, pParent)
{
	//{{AFX_DATA_INIT(SpatialWnd)
	m_sp1 = 0;
	m_sp2 = 1;
	m_steplength= 1000;
	m_posx = 0;
	m_posy = 0;
	m_wndsize = 50;
	//}}AFX_DATA_INIT
}


void SpatialWnd::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SpatialWnd)
	DDX_Text(pDX, IDC_EDIT_Phase_Species1, m_sp1);
	DDX_Text(pDX, IDC_EDIT_Phase_Species2, m_sp2);
	DDX_Text(pDX, IDC_EDIT_Phase_StepSize, m_steplength);
	DDV_MinMaxInt(pDX, m_steplength, 100, 2000);
	DDX_Text(pDX, IDC_EDIT_SpatialWnd_PosX, m_posx);
	DDX_Text(pDX, IDC_EDIT_SpatialWnd_PosY, m_posy);
	DDX_Text(pDX, IDC_EDIT_SpatialWnd_Size, m_wndsize);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(SpatialWnd, CDialog)
	//{{AFX_MSG_MAP(SpatialWnd)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SpatialWnd message handlers
