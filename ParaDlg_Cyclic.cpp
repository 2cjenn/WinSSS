// ParaDlg_Cyclic.cpp : implementation file
//

#include "stdafx.h"
#include "sss.h"
#include "ParaDlg_Cyclic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ParaDlg_Cyclic dialog


ParaDlg_Cyclic::ParaDlg_Cyclic(CWnd* pParent /*=NULL*/)
	: CDialog(ParaDlg_Cyclic::IDD, pParent)
{
	//{{AFX_DATA_INIT(ParaDlg_Cyclic)
	m_a0 = 1.0f;
	m_b1 = 10.0f;
	m_a2 = 1.0f;
	m_b3 = 10.0f;
	m_a4 = 1.0f;
	m_b5 = 10.0f;
	m_a6 = 1.0f;
	m_b7 = 10.0f;
	m_a8 = 1.0f;
	m_b9 = 10.0f;
	m_nThreshold = 1;
	m_bThreshold = FALSE;
	m_sparkdensity = 2.0f;
	m_bspark = false;
	m_Init = 0;
	m_icChess = FALSE;
	m_icRand = FALSE;
	m_r1Density = 20.0f;
	m_r2Density = 10.0f;
	m_NumPartition = 10;

	m_nStates = 8;
	m_nbr = 8;

	//}}AFX_DATA_INIT
}


void ParaDlg_Cyclic::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ParaDlg_Cyclic)
	DDX_Control(pDX, IDC_COMBO_Nbr, m_nbrsize);
	DDX_Control(pDX, IDC_COMBO_NumStates, m_numstates);
	DDX_Control(pDX, IDC_EDIT_IC_R2DENS, m_Dens2);
	DDX_Control(pDX, IDC_EDIT_IC_R1DENS, m_Dens1);
	DDX_Control(pDX, IDC_EDIT_IC_Part, m_Partition);
	DDX_Control(pDX, IDC_CHECK_IC_RAND, m_Rand);
	DDX_Control(pDX, IDC_CHECK_IC_CHESS, m_Chess);
	DDX_Text(pDX, IDC_EDIT1, m_a0);
	DDX_Text(pDX, IDC_EDIT2, m_b1);
	DDX_Text(pDX, IDC_EDIT3, m_a2);
	DDX_Text(pDX, IDC_EDIT4, m_b3);
	DDX_Text(pDX, IDC_EDIT5, m_a4);
	DDX_Text(pDX, IDC_EDIT6, m_b5);
	DDX_Text(pDX, IDC_EDIT7, m_a6);
	DDX_Text(pDX, IDC_EDIT8, m_b7);
	DDX_Text(pDX, IDC_EDIT9, m_a8);
	DDX_Text(pDX, IDC_EDIT10, m_b9);
	DDX_Text(pDX, IDC_EDIT11, m_nThreshold);
	DDX_Check(pDX, IDC_CHECK1, m_bThreshold);
	DDX_Text(pDX, IDC_SPARKDENSITY, m_sparkdensity);
	DDX_Check(pDX, IDC_CHECK_IC_CHESS, m_icChess);
	DDX_Check(pDX, IDC_CHECK_IC_RAND, m_icRand);
	DDX_Text(pDX, IDC_EDIT_IC_R1DENS, m_r1Density);
	DDX_Text(pDX, IDC_EDIT_IC_R2DENS, m_r2Density);
	DDX_Text(pDX, IDC_EDIT_IC_Part, m_NumPartition);
	

	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ParaDlg_Cyclic, CDialog)
	//{{AFX_MSG_MAP(ParaDlg_Cyclic)
//	ON_BN_CLICKED(IDC_RADIO2, OnThreshold)
	ON_BN_CLICKED(IDC_SPARK, OnSpark)
	ON_BN_CLICKED(IDC_CHECK_IC_RAND, OnCheckIcRand)
	ON_BN_CLICKED(IDC_CHECK_IC_CHESS, OnCheckIcChess)
	ON_CBN_SELCHANGE(IDC_COMBO_NumStates, OnSelchangeNumStates)
	ON_BN_CLICKED(IDC_CHECK1, OnThreshold)
	ON_CBN_SELCHANGE(IDC_COMBO_Nbr, OnSelchangeNbrSize)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedButton1)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ParaDlg_Cyclic message handlers

  

BOOL ParaDlg_Cyclic::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_numstates.AddString("4");
	m_numstates.AddString("6");
	m_numstates.AddString("8");
	m_numstates.AddString("10");
	m_numstates.SetCurSel((m_nStates-4) / 2);

	m_nbrsize.AddString("Four Direct");
	m_nbrsize.AddString("Eight Squre");
	m_nbrsize.AddString("24 Neighbors");
	if (m_nbr == 4) 
		m_nbrsize.SetCurSel(0);
	else if (m_nbr == 8)
		m_nbrsize.SetCurSel(1);
	else if (m_nbr == 24)
		m_nbrsize.SetCurSel(2);

	m_icRand = TRUE;
	m_Rand.SetCheck(TRUE);

	if (m_Init == 0)
	{
		m_Chess.SetCheck(FALSE);
		m_Partition.EnableWindow(FALSE);
		m_Dens1.EnableWindow(FALSE);
		m_Dens2.EnableWindow(FALSE);
	}

	if (m_Init == 1)
	{
		m_Rand.SetCheck(FALSE);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}



void ParaDlg_Cyclic::OnBnClickedButton1()
{
	m_a0 = 1.0f;
	m_b1 = 10.0f;
	m_a2 = 1.0f;
	m_b3 = 10.0f;
	m_a4 = 1.0f;
	m_b5 = 10.0f;
	m_a6 = 1.0f;
	m_b7 = 10.0f;
	m_a8 = 1.0f;
	m_b9 = 10.0f;
	m_nStates = 8;
	m_nbr = 8;
	
	m_numstates.SetCurSel((m_nStates-4) / 2);
	if (m_nbr == 4) 
		m_nbrsize.SetCurSel(0);
	else if (m_nbr == 8)
		m_nbrsize.SetCurSel(1);
	else if (m_nbr == 24)
		m_nbrsize.SetCurSel(2);
	CDialog::OnInitDialog();

}

void ParaDlg_Cyclic::OnThreshold() 
{
	m_bThreshold = !m_bThreshold;	
}

void ParaDlg_Cyclic::OnSpark() 
{
	m_bspark = true;
	
}



void ParaDlg_Cyclic::OnCheckIcRand() 
{
	m_Init = 0;
	
	m_icRand = TRUE;
	m_icChess = FALSE;
	m_Chess.SetCheck(FALSE);
	m_Rand.SetCheck(TRUE);
	
	m_Partition.EnableWindow(FALSE);
	m_Dens1.EnableWindow(FALSE);
	m_Dens2.EnableWindow(FALSE);
		
}

void ParaDlg_Cyclic::OnCheckIcChess() 
{
	m_Init = 1;
	m_icChess = TRUE;
	
	m_icRand = FALSE;
	m_Rand.SetCheck(FALSE);
	m_Chess.SetCheck(TRUE);

	m_Partition.EnableWindow();
	m_Dens1.EnableWindow();
	m_Dens2.EnableWindow();
	
}

void ParaDlg_Cyclic::OnSelchangeNumStates() 
{
	switch(m_numstates.GetCurSel())
	{
	case 0: m_nStates = 4;
		break;
	case 1: m_nStates = 6;
		break;
	case 2: m_nStates = 8;
		break;
	case 3: m_nStates = 10;
		break;
	}	
}

void ParaDlg_Cyclic::OnSelchangeNbrSize() 
{
	switch(m_nbrsize.GetCurSel())
	{
	case 0: m_nbr = 4;
		break;
	case 1: m_nbr = 8;
		break;
	case 2: m_nbr = 24;
		break;
	}	
}
