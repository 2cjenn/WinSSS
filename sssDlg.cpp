// sssDlg.cpp : implementation file
//

#include "StdAfx.h"
#include "sss.h"
#include "sssDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSssDlg dialog

CSssDlg::CSssDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSssDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSssDlg)
	m_nRecordCount = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	nShowPortrait = 0;
	done = true;
	pause = false;

	nLinesPos = 0;
	dLinesDist = 1.331;
	dMapDist = 1.5;
	
	m_nRowCol = 200;
	
	Para_Cyclic = new ParaDlg_Cyclic;
	Para_Contact = new ParaDlg_Contact;
	Para_EP = new ParaDlg_Ep;
	Para_GH = new ParaDlg_GH;

	Para_RSP = new ParaDlg_RSP;
	Para_Voter = new ParaDlg_Voter;
	Para_MultiCont = new ParaDlg_MultiCont;

	pM_MultiCont = new Model_MultiContact(m_nRowCol, (void *) Para_MultiCont);
	pM_Cyclic = new Model_Cyclic(m_nRowCol, (void *) Para_Cyclic);
	pM_Contact = new Model_Contact(m_nRowCol, (void *) Para_Contact);
	pM_EP = new Model_EP(m_nRowCol, (void *) Para_EP);
	pM_RSP = new Model_RSP(m_nRowCol, (void *) Para_RSP);

	pM_LV = new Model_LVoter(m_nRowCol, (void *) Para_Voter);
	pM_GH = new Model_GH(m_nRowCol, (void *) Para_GH);

	readfromfile = 0;
	record = false;
	fp = NULL;
	m_nRecordCount = 0;

	pSpatial = new SpatialWnd;
	
}

void CSssDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSssDlg)
	DDX_Control(pDX, IDC_Record, m_EditRecord);
	DDX_Control(pDX, IDC_BUTTON_TSR, m_tsr);
	DDX_Control(pDX, IDC_FILE_SAVE, m_filesave);
	DDX_Control(pDX, IDC_FILE_LOAD, m_fileload);
	DDX_Control(pDX, IDC_COMBO_MapSize, m_mapsize);
	DDX_Control(pDX, IDC_COMBO_ModelList, m_modellist);
	DDX_Control(pDX, IDC_MultiView, m_MultiView);
	DDX_Control(pDX, IDC_Line, m_line);
	DDX_Control(pDX, IDC_Frame, m_view);
	DDX_Control(pDX, IDC_LEGEND, m_legend);
	DDX_Control(pDX, IDC_PAUSE, m_pause);
	DDX_Control(pDX, IDC_PARAMETER, m_para);
	DDX_Control(pDX, IDC_SPEEDSLIDER, m_speed);
	DDX_Control(pDX, IDC_RUN, m_run);
	DDX_Text(pDX, IDC_Record, m_nRecordCount);
	//}}AFX_DATA_MAP

	
}

BEGIN_MESSAGE_MAP(CSssDlg, CDialog)
	//{{AFX_MSG_MAP(CSssDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_RUN, OnRun)
	ON_BN_CLICKED(IDC_PAUSE, OnPause)
	ON_BN_CLICKED(IDC_PARAMETER, OnParameter)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_LinesShiftUp, OnLinesShiftUp)
	ON_BN_CLICKED(IDC_LinesShiftDn, OnLinesShiftDn)
	ON_BN_CLICKED(IDC_LinesEnlargeDn, OnLinesEnlargeDn)
	ON_BN_CLICKED(IDC_LinesEnlargeUp, OnLinesEnlargeUp)
	ON_BN_CLICKED(IDC_MapEnlargeUp, OnMapEnlargeUp)
	ON_BN_CLICKED(IDC_MapEnlargeDn, OnMapEnlargeDn)
	ON_NOTIFY(TCN_SELCHANGE, IDC_MultiView, OnSelchangeMultiView)
	ON_CBN_SELCHANGE(IDC_COMBO_MapSize, OnSelchangeMapSize)
	ON_BN_CLICKED(IDC_FILE_SAVE, OnFileSave)
	ON_BN_CLICKED(IDC_FILE_LOAD, OnFileLoad)
	ON_BN_CLICKED(ID_HELP, OnHelp)
	ON_BN_CLICKED(IDC_BUTTON_TSR, OnTSR)
	ON_CBN_SELCHANGE(IDC_COMBO_ModelList, OnSelchangeModelList)
	ON_BN_CLICKED(IDC_SPATIAL_WND, OnSpatialWnd)
	//}}AFX_MSG_MAP
	
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSssDlg message handlers

BOOL CSssDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	m_EditRecord.EnableWindow(FALSE);

	TC_ITEM TabCtrlItem;
	TabCtrlItem.mask = TCIF_TEXT;
	TabCtrlItem.pszText = "IPS Animation";
	m_MultiView.InsertItem( 0, &TabCtrlItem );
	TabCtrlItem.pszText = "Phase Portrait";
	m_MultiView.InsertItem( 1, &TabCtrlItem );

	
	m_modellist.AddString("Cyclic Resource-Species");
	m_modellist.AddString("Epidemic");
	m_modellist.AddString("Contact Process");
	m_modellist.AddString("Multi-Contact Process");
	m_modellist.AddString("Rock-Scissors-Paper");
	m_modellist.AddString("Voter Model");
	m_modellist.AddString("Greenberg-Hastings");
	m_modellist.SetCurSel(0);
	

	m_mapsize.AddString("100 x 100");
	m_mapsize.AddString("150 x 150");
	m_mapsize.AddString("200 x 200");
	m_mapsize.AddString("250 x 250");
	m_mapsize.AddString("300 x 300");
	m_mapsize.AddString("400 x 400");
	m_mapsize.AddString("500 x 500");
	
	m_mapsize.SetCurSel(2);

	m_speed.SetRange(1,10);
	m_speed.SetTicFreq(1);
	m_speed.SetPos(1);

	m_legend.EnableOpenGL();
	m_line.EnableOpenGL();
	m_view.EnableOpenGL();

	SetWindowText("Stochastic Spatial Simulator");
	

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSssDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSssDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSssDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CSssDlg::OnRun() 
{	
	done = !done;
	if (done == true)
	{
		m_run.SetWindowText("RUN");
		m_modellist.EnableWindow(TRUE);
		m_pause.EnableWindow(FALSE);
		m_mapsize.EnableWindow(TRUE);
		m_para.EnableWindow(TRUE);
		nStepCount = 0;
		pause = false;
		
		switch(m_modellist.GetCurSel())
		{
		case 0: 
			if(!readfromfile)
				pM_Cyclic->Initialization();
			else
			{
				readfromfile = false;
			}
			wglMakeCurrent( m_view.hDC, m_view.hRC );
			switch(nShowPortrait)
			{
			case 0:
				m_view.Paint(pM_Cyclic, dMapDist);
				break;
			case 1:
				m_view.DrawPhasePortrait(pM_Cyclic, dMapDist, pSpatial->m_steplength,pSpatial->m_sp1, pSpatial->m_sp2);
				break;
			}	
			break;

		case 1:
			pM_EP->Initialization();
			wglMakeCurrent( m_view.hDC, m_view.hRC );
			switch(nShowPortrait)
			{
			case 0:
				m_view.Paint(pM_EP, dMapDist);
				break;
			case 1:
				m_view.DrawPhasePortrait(pM_EP, dMapDist, pSpatial->m_steplength, pSpatial->m_sp1, pSpatial->m_sp2);
				break;
			}	
			break;

		case 2:
			pM_Contact->Initialization();
			wglMakeCurrent( m_view.hDC, m_view.hRC );
			switch(nShowPortrait)
			{
			case 0:
				m_view.Paint(pM_Contact, dMapDist);
				break;
			case 1:
				m_view.DrawPhasePortrait(pM_Contact, dMapDist, pSpatial->m_steplength,pSpatial->m_sp1, pSpatial->m_sp2);
				break;
			}	
			break;

		case 3:
			pM_MultiCont->Initialization();
			wglMakeCurrent( m_view.hDC, m_view.hRC );
			switch(nShowPortrait)
			{
			case 0:
				m_view.Paint(pM_MultiCont, dMapDist);
				break;
			case 1:
				m_view.DrawPhasePortrait(pM_MultiCont, dMapDist, pSpatial->m_steplength,pSpatial->m_sp1, pSpatial->m_sp2);
				break;
			}	
			break;
		case 4:
			pM_RSP->Initialization();
			wglMakeCurrent( m_view.hDC, m_view.hRC );
			switch(nShowPortrait)
			{
			case 0:
				m_view.Paint(pM_RSP, dMapDist);
				break;
			case 1:
				m_view.DrawPhasePortrait(pM_RSP, dMapDist, pSpatial->m_steplength,pSpatial->m_sp1, pSpatial->m_sp2);
				break;
			}	
			break;

		case 5:
			pM_LV->Initialization();
			wglMakeCurrent( m_view.hDC, m_view.hRC );
			switch(nShowPortrait)
			{
			case 0:
				m_view.Paint(pM_LV, dMapDist);
				break;
			case 1:
				m_view.DrawPhasePortrait(pM_LV, dMapDist, pSpatial->m_steplength,pSpatial->m_sp1, pSpatial->m_sp2);
				break;
			}	
			break;
		case 6:
			pM_GH->Initialization();
			wglMakeCurrent( m_view.hDC, m_view.hRC );
			switch(nShowPortrait)
			{
			case 0:
				m_view.Paint(pM_GH, dMapDist);
				break;
			case 1:
				m_view.DrawPhasePortrait(pM_GH, dMapDist, pSpatial->m_steplength,pSpatial->m_sp1, pSpatial->m_sp2);
				break;
			}	
			break;
		}
	
	
	}
	
	else {

		nStepCount = 0;
		m_modellist.EnableWindow(FALSE);
		m_run.SetWindowText("STOP");
		m_pause.EnableWindow(TRUE);
		m_para.EnableWindow(FALSE);
		m_mapsize.EnableWindow(FALSE);
		
		switch(m_modellist.GetCurSel())
		{
		case 0: 
			if (!readfromfile)
				pM_Cyclic->Initialization();
			
			break;
		case 1:
			pM_EP->Initialization();
			break;
		case 2:
			pM_Contact->Initialization();
			break;
		case 3:
			pM_MultiCont->Initialization();
			break;
		case 4:
			pM_RSP->Initialization();
			break;
		case 5:
			pM_LV->Initialization();
			break;
		case 6: 
			pM_GH->Initialization();
		}
		go();
	}
	
	
	
	
}

void CSssDlg::OnPause() 
{
	m_para.EnableWindow(TRUE);
	m_mapsize.EnableWindow(FALSE);
	pause = !pause;
	if(pause == true)
	{
		m_pause.SetWindowText("CONTINUE");
		m_run.EnableWindow(FALSE);
		m_para.EnableWindow(TRUE);
	}
	else
	{
		m_pause.SetWindowText("PAUSE");
		m_run.EnableWindow(TRUE);
		m_para.EnableWindow(FALSE);
		
	}
	go();
	
}

void CSssDlg::OnParameter() 
{
	switch (m_modellist.GetCurSel())
	{
	case 0: 
		Para_Cyclic->DoModal();
		break;
	case 1:
		Para_EP->DoModal();
		break;
	case 2:
		Para_Contact->DoModal();
		break;
	case 3:
		Para_MultiCont->DoModal();
		break;
	case 4:
		Para_RSP->DoModal();
		break;
	case 5:
		Para_Voter->DoModal();
		break;
	case 6:
		Para_GH->DoModal();
		break;

	
	}
	
}





void CSssDlg::go()
{
		
	switch (m_modellist.GetCurSel())
	{
	case 0:

		while(!done && !pause) 
		{	
			int speed = m_speed.GetPos();
			pM_Cyclic->Simulation(speed, record, fp, m_nRecordCount, pSpatial);
			if (record == true)
			{	
				m_nRecordCount++;
				UpdateData(FALSE);
			}
			if (m_nRecordCount >= pSpatial->m_steplength)
			{
				record = false;
				m_nRecordCount = 0;
				fclose(fp);
				m_tsr.SetWindowText("Record");
				m_run.EnableWindow();
				m_pause.EnableWindow();
			}

			wglMakeCurrent( m_view.hDC, m_view.hRC );
	//		for (i = 0; i <= speed * speed / 5; i++)
			{
				switch(nShowPortrait)
				{
				case 0:
					m_view.Paint(pM_Cyclic, dMapDist);
					break;
				case 1:
					m_view.DrawPhasePortrait(pM_Cyclic, dMapDist, pSpatial->m_steplength,pSpatial->m_sp1, pSpatial->m_sp2);
					break;
				}	
			}
			
			wglMakeCurrent( m_line.hDC, m_line.hRC );
			m_line.Drawlines(pM_Cyclic, nStepCount++, nLinesPos, dLinesDist);
			wglMakeCurrent( m_legend.hDC, m_legend.hRC );
			m_legend.DrawLegend(pM_Cyclic, Para_Cyclic->m_nStates);
			
		}

		break;

	case 1:
	
		while(!done && !pause ) 
		{
			int speed = m_speed.GetPos();
			pM_EP->Simulation(pSpatial, speed);

		
			wglMakeCurrent( m_view.hDC, m_view.hRC );
		//	for (i = 0; i <= speed * speed / 5; i++)
			{
				switch(nShowPortrait)
				{
				case 0:
					m_view.Paint(pM_EP, dMapDist);
					break;
				case 1:
					m_view.DrawPhasePortrait(pM_EP, dMapDist, pSpatial->m_steplength, pSpatial->m_sp1, pSpatial->m_sp2);
					break;
				}	
			}
			
			
			
			wglMakeCurrent( m_line.hDC, m_line.hRC );
			m_line.Drawlines(pM_EP, nStepCount++, nLinesPos, dLinesDist);//nStepCount++, dFreq, nLinesPos, dLinesDist, nStates);
			
			wglMakeCurrent( m_legend.hDC, m_legend.hRC );
			m_legend.DrawLegend(pM_Cyclic, 3);
		
		}

		break;

	case 2:
		while(!done && !pause ) 
		{
			int speed = m_speed.GetPos();
			pM_Contact->Simulation(pSpatial, 4 * speed);

		
			wglMakeCurrent( m_view.hDC, m_view.hRC );
		//	for (i = 0; i <= speed * speed / 5; i++)
			{
				switch(nShowPortrait)
				{
				case 0:
					m_view.Paint(pM_Contact, dMapDist);
					break;
				case 1:
					m_view.DrawPhasePortrait(pM_Contact, dMapDist, pSpatial->m_steplength,pSpatial->m_sp1, pSpatial->m_sp2);
					break;
				}	
			}
			
			
		
			wglMakeCurrent( m_line.hDC, m_line.hRC );
			m_line.Drawlines(pM_Contact, nStepCount++, nLinesPos, dLinesDist);//nStepCount++, dFreq, nLinesPos, dLinesDist, nStates);
			
			wglMakeCurrent( m_legend.hDC, m_legend.hRC );
			m_legend.DrawLegend(pM_Contact, 2);
		
		}

		break;

	case 3:
		while(!done && !pause ) 
		{
			int speed = m_speed.GetPos();
			pM_MultiCont->Simulation(pSpatial, speed);

		
			wglMakeCurrent( m_view.hDC, m_view.hRC );
		//	for (i = 0; i <= speed * speed / 5; i++)
			{
				switch(nShowPortrait)
				{
				case 0:
					m_view.Paint(pM_MultiCont, dMapDist);
					break;
				case 1:
					m_view.DrawPhasePortrait(pM_MultiCont, dMapDist, pSpatial->m_steplength,pSpatial->m_sp1, pSpatial->m_sp2);
					break;
				}	
			}
			
		
			wglMakeCurrent( m_line.hDC, m_line.hRC );
			m_line.Drawlines(pM_MultiCont, nStepCount++, nLinesPos, dLinesDist);//nStepCount++, dFreq, nLinesPos, dLinesDist, nStates);
			
			wglMakeCurrent( m_legend.hDC, m_legend.hRC );
			m_legend.DrawLegend(pM_MultiCont, 4);
		
		}

		break;

	case 4:
		while(!done && !pause ) 
		{
			int speed = m_speed.GetPos();
			pM_RSP->Simulation(pSpatial, speed);

		
			wglMakeCurrent( m_view.hDC, m_view.hRC );
		//	for (i = 0; i <= speed * speed / 5; i++)
			{
				switch(nShowPortrait)
				{
				case 0:
					m_view.Paint(pM_RSP, dMapDist);
					break;
				case 1:
					m_view.DrawPhasePortrait(pM_RSP, dMapDist, pSpatial->m_steplength,pSpatial->m_sp1, pSpatial->m_sp2);
					break;
				}	
			}

			wglMakeCurrent( m_line.hDC, m_line.hRC );
			m_line.Drawlines(pM_RSP, nStepCount++, nLinesPos, dLinesDist);//nStepCount++, dFreq, nLinesPos, dLinesDist, nStates);
		
			wglMakeCurrent( m_legend.hDC, m_legend.hRC );
			m_legend.DrawLegend(pM_RSP, Para_RSP->m_nStates);
		}
	
		break;

	case 5:
		while(!done && !pause ) 
		{
			int speed = m_speed.GetPos();
			pM_LV->Simulation(pSpatial, 4 * speed);

		
			wglMakeCurrent( m_view.hDC, m_view.hRC );
	//		for (i = 0; i <= speed * speed / 5; i++)
			{
				switch(nShowPortrait)
				{
				case 0:
					m_view.Paint(pM_LV, dMapDist);
					break;
				case 1:
					m_view.DrawPhasePortrait(pM_LV, dMapDist, pSpatial->m_steplength,pSpatial->m_sp1, pSpatial->m_sp2);
					break;
				}	
			}

			wglMakeCurrent( m_line.hDC, m_line.hRC );
			m_line.Drawlines(pM_LV, nStepCount++, nLinesPos, dLinesDist);//nStepCount++, dFreq, nLinesPos, dLinesDist, nStates);
			
			wglMakeCurrent( m_legend.hDC, m_legend.hRC );
			m_legend.DrawLegend(pM_LV, Para_Voter->m_nStates);
		}
	
		break;

	case 6:
		while(!done && !pause ) 
		{
			int speed = m_speed.GetPos();
			pM_GH->Simulation(pSpatial, speed);

		
			wglMakeCurrent( m_view.hDC, m_view.hRC );
		//	for (i = 0; i <= speed * speed / 5; i++)
			{
				switch(nShowPortrait)
				{
				case 0:
					m_view.Paint(pM_GH, dMapDist);
					break;
				case 1:
					m_view.DrawPhasePortrait(pM_GH, dMapDist, pSpatial->m_steplength,pSpatial->m_sp1, pSpatial->m_sp2);
					break;
				}	
			}

			wglMakeCurrent( m_line.hDC, m_line.hRC );
			m_line.Drawlines(pM_GH, nStepCount++, nLinesPos, dLinesDist);//nStepCount++, dFreq, nLinesPos, dLinesDist, nStates);
		
			wglMakeCurrent( m_legend.hDC, m_legend.hRC );
			m_legend.DrawLegend(pM_GH, 8);
		}
	
		
	}

}

void CSssDlg::OnClose() 
{
	done = true;
	CDialog::OnClose();
}




void CSssDlg::OnLinesShiftUp() 
{
	nLinesPos += 1;
	if ( done || pause)
	{
		wglMakeCurrent( m_line.hDC, m_line.hRC );
		switch (m_modellist.GetCurSel())
		{
		case 0:
			m_line.Drawlines(pM_Cyclic, nStepCount++, nLinesPos, dLinesDist);
			break;
		case 1:
			m_line.Drawlines(pM_EP, nStepCount++, nLinesPos, dLinesDist);
			break;
		case 2:
			m_line.Drawlines(pM_Contact, nStepCount++, nLinesPos, dLinesDist);
			break;
		case 3:
			m_line.Drawlines(pM_MultiCont, nStepCount++, nLinesPos, dLinesDist);
			break;
		case 4:
			m_line.Drawlines(pM_RSP, nStepCount++, nLinesPos, dLinesDist);
			break;
		case 5:
			m_line.Drawlines(pM_LV, nStepCount++, nLinesPos, dLinesDist);
			break;

		}

	}
	
}

void CSssDlg::OnLinesShiftDn() 
{
	nLinesPos -= 1;	
	if (done || pause)
	{
		wglMakeCurrent( m_line.hDC, m_line.hRC );
		switch (m_modellist.GetCurSel())
		{
		case 0:
			m_line.Drawlines(pM_Cyclic, nStepCount++, nLinesPos, dLinesDist);
			break;
		case 1:
			m_line.Drawlines(pM_EP, nStepCount++, nLinesPos, dLinesDist);
			break;
		case 2:
			m_line.Drawlines(pM_Contact, nStepCount++, nLinesPos, dLinesDist);
			break;
		case 3:
			m_line.Drawlines(pM_MultiCont, nStepCount++, nLinesPos, dLinesDist);
			break;
		case 4:
			m_line.Drawlines(pM_RSP, nStepCount++, nLinesPos, dLinesDist);
			break;
		case 5:
			m_line.Drawlines(pM_LV, nStepCount++, nLinesPos, dLinesDist);
			break;

		}
	}
}

void CSssDlg::OnLinesEnlargeDn() 
{
	dLinesDist *= 1.1;
	if (done || pause)
	{
		wglMakeCurrent( m_line.hDC, m_line.hRC );
		switch (m_modellist.GetCurSel())
		{
		case 0:
			m_line.Drawlines(pM_Cyclic, nStepCount++, nLinesPos, dLinesDist);
			break;
		case 1:
			m_line.Drawlines(pM_EP, nStepCount++, nLinesPos, dLinesDist);
			break;
		case 2:
			m_line.Drawlines(pM_Contact, nStepCount++, nLinesPos, dLinesDist);
			break;
		case 3:
			m_line.Drawlines(pM_MultiCont, nStepCount++, nLinesPos, dLinesDist);
			break;
			break;
		case 4:
			m_line.Drawlines(pM_RSP, nStepCount++, nLinesPos, dLinesDist);
			break;
		case 5:
			m_line.Drawlines(pM_LV, nStepCount++, nLinesPos, dLinesDist);
			break;
		}
	}
	
}

void CSssDlg::OnLinesEnlargeUp() 
{
	dLinesDist /= 1.1;	
	if (done || pause)
	{
		wglMakeCurrent( m_line.hDC, m_line.hRC );
		switch (m_modellist.GetCurSel())
		{
		case 0:
			m_line.Drawlines(pM_Cyclic, nStepCount++, nLinesPos, dLinesDist);
			break;
		case 1:
			m_line.Drawlines(pM_EP, nStepCount++, nLinesPos, dLinesDist);
			break;
		case 2:
			m_line.Drawlines(pM_Contact, nStepCount++, nLinesPos, dLinesDist);
			break;
		case 3:
			m_line.Drawlines(pM_MultiCont, nStepCount++, nLinesPos, dLinesDist);
			break;
		case 4:
			m_line.Drawlines(pM_RSP, nStepCount++, nLinesPos, dLinesDist);
			break;
		case 5:
			m_line.Drawlines(pM_LV, nStepCount++, nLinesPos, dLinesDist);
			break;

		}
	}
}

void CSssDlg::OnMapEnlargeUp() 
{
	dMapDist /= 1.1;
	
	if (done || pause)
	{
	
		wglMakeCurrent( m_view.hDC, m_view.hRC );
		switch (m_modellist.GetCurSel())
		{
			case 0: 
				m_view.Paint(pM_Cyclic, dMapDist);
				break;
			case 1:
				m_view.Paint(pM_EP, dMapDist);
				break;
			case 2:
				m_view.Paint(pM_Contact, dMapDist);
				break;
			case 3:
				m_view.Paint(pM_MultiCont, dMapDist);
				break;
			case 4:
				m_view.Paint(pM_RSP, dMapDist);
				break;
			case 5:
				m_view.Paint(pM_LV, dMapDist);
				break;


		}
	}
	

}

void CSssDlg::OnMapEnlargeDn() 
{
	dMapDist *= 1.1;	
	if (done || pause)
	{
	
		wglMakeCurrent( m_view.hDC, m_view.hRC );
		
		switch (m_modellist.GetCurSel())
		{
		case 0:
			m_view.Paint(pM_Cyclic, dMapDist);
			break;
		case 1:
			m_view.Paint(pM_EP, dMapDist);
			break;
		case 2:
			m_view.Paint(pM_Contact, dMapDist);
			break;
		case 3:
			m_view.Paint(pM_MultiCont, dMapDist);
			break;
		case 4:
			m_view.Paint(pM_RSP, dMapDist);
			break;
		case 5:
			m_view.Paint(pM_LV, dMapDist);
			break;

		}
	}

}




void CSssDlg::OnSelchangeMultiView(NMHDR* pNMHDR, LRESULT* pResult) 
{
	nShowPortrait = m_MultiView.GetCurSel();
	*pResult = 0;
}





void CSssDlg::OnSelchangeMapSize() 
{
	switch(m_mapsize.GetCurSel())
	{
	case 0: 
		m_nRowCol = 100;
		break;
	case 1: 
		m_nRowCol = 150;
		break;
	case 2: 
		m_nRowCol = 200;
        break;
	case 3: 
		m_nRowCol = 250;
		break;
	case 4: 
		m_nRowCol = 300;
        break;
	case 5:
		m_nRowCol = 400;
		break;
	case 6:
		m_nRowCol = 500;
		break;
	}

	delete pM_Cyclic;
	delete pM_Contact;
	delete pM_EP;
	delete pM_RSP;
	delete pM_LV;
	delete pM_GH;
	delete pM_MultiCont; 

	pM_MultiCont = new Model_MultiContact(m_nRowCol, (void *) Para_MultiCont);
	pM_Cyclic = new Model_Cyclic(m_nRowCol, (void *) Para_Cyclic);
	pM_Contact = new Model_Contact(m_nRowCol, (void *) Para_Contact);
	pM_EP = new Model_EP(m_nRowCol, (void *) Para_EP);
	pM_RSP = new Model_RSP(m_nRowCol, (void *) Para_RSP);

	pM_LV = new Model_LVoter(m_nRowCol, (void *) Para_Voter);
	pM_GH = new Model_GH(m_nRowCol, (void *) Para_GH);

	
}




using namespace std;
#include <fstream>

void CSssDlg::OnFileLoad() 
{
	CFileDialog * pfd;
	ifstream infile;
	
	pfd = new CFileDialog(TRUE, "ips", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "ips", NULL);
	pfd->m_ofn.lpstrFilter = "IPS File \0 *.ips\0";
	pfd->DoModal();
	
	CString str(pfd->GetPathName());
	if (!str.IsEmpty())
	{
		infile.open(str, ios::in);
		
		if (!infile.good())
		{
			MessageBox("file open error", "File Handling Message", MB_OK);
			return;
		}
	}


	char * p;
	char buffer[256];
	char * delimit = ";, '\t'";
	int nRow, nCol, nStates, nNbr;
	float rate[10];
	bool bThreshold;
	int nThreshold;

	if (!str.IsEmpty() && infile.good())
	{
		readfromfile = true;
		if (m_modellist.GetCurSel() > 0)
		{
			MessageBox("Not Implement For This Model :(", NULL, MB_OK);
			return;
		}
		//read in first line, nRow;
		infile.getline(buffer, 255, '\n');
		p = strtok(buffer, delimit);
		nRow = atoi(p);
		if(nRow % 50 != 0)
		{
			MessageBox("File Error, Please Check File Format!", NULL, MB_OK);
			return;
		}
		

		//read in second line, nCol;
		infile.getline(buffer, 255, '\n');
		p = strtok(buffer, delimit);
		nCol = atoi(p);
		if(nCol % 50 != 0)
		{
			MessageBox("File Error, Please Check File Format!", NULL, MB_OK);
			return;
		}
		

		if (nRow != pM_Cyclic->GetRow())
		{ 
			delete pM_Cyclic;
			pM_Cyclic = new Model_Cyclic(nRow, (void *) Para_Cyclic);
			switch(nRow)
			{
			case 100: 
				m_mapsize.SetCurSel(0);
				break;
			case 150:
				m_mapsize.SetCurSel(1);
				break;
			case 200:
				m_mapsize.SetCurSel(2);
				break;
			case 250:
				m_mapsize.SetCurSel(3);
				break;
			case 300:
				m_mapsize.SetCurSel(4);
				break;
			case 400:
				m_mapsize.SetCurSel(5);
				break;
			case 500:
				m_mapsize.SetCurSel(6);
				break;

			}
		}
		

		//read in third line, number of states;
		infile.getline(buffer, 255, '\n');
		p = strtok(buffer, delimit);
		nStates = atoi(p);
		if(nStates % 2 != 0)
		{
			MessageBox("File Error, Please Check File Format!", NULL, MB_OK);
			return;
		}

		// fourth line, number of neighborhood;
		infile.getline(buffer, 255, '\n');
		p = strtok(buffer, delimit);
		nNbr = atoi(p);
		if(nStates % 4 != 0)
		{
			MessageBox("File Error, Please Check File Format!", NULL, MB_OK);
			return;
		}
	
		// fifth line, birth-death rate;
		rate[10];
		infile.getline(buffer, 255, '\n');
		p = strtok(buffer, delimit);
		rate[0] = atof(p);

		for(int ii=1; ii<10; ii++)
		{
			p = strtok(NULL, delimit);
			rate[ii] = atof(p);
		}

		// sixth line, threshold para;
		infile.getline(buffer, 255, '\n');
		p = strtok(buffer, delimit);
		bThreshold = atoi(p)>0? true:false ;
		p = strtok(NULL, delimit);
		nThreshold = atoi(p);
		
		char * buff = new char[nRow * 4];
		for (int i = 0; i < nCol; i++)
		{
			infile.getline(buff, nRow * 4, '\n');
			p = strtok(buff, delimit); 
			pM_Cyclic->State(i, 0) = atoi(p);
			for (int j = 1; j < nRow; j++)
			{
				p = strtok(NULL, delimit);
				pM_Cyclic->State(i, j) = atoi(p);
								
			}
		
		}
	
		Para_Cyclic->m_nStates = nStates;
		Para_Cyclic->m_nbr = nNbr;
		Para_Cyclic->m_a0 = rate[0];
		Para_Cyclic->m_b1 = rate[1];
		Para_Cyclic->m_a2 = rate[2];
		Para_Cyclic->m_b3 = rate[3];
		Para_Cyclic->m_a4 = rate[4];
		Para_Cyclic->m_b5 = rate[5];
		Para_Cyclic->m_a6 = rate[6];
		Para_Cyclic->m_b7 = rate[7];
		Para_Cyclic->m_a8 = rate[8];
		Para_Cyclic->m_b9 = rate[9];

	}
}





void CSssDlg::OnFileSave() 
{
	CFileDialog * pfd;
	FILE * fp = NULL;
	pfd = new CFileDialog(FALSE, "ips", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "ips, tsr", NULL);
	pfd->m_ofn.lpstrFilter = "IPS FILE \0 *.ips\0";
	pfd->DoModal();

	CString str(pfd->GetPathName());
	if (!str.IsEmpty())
	{
		fp = fopen(str, "w");
		if (fp == NULL)
		{
			MessageBox("file open error", "File Handling Message", MB_OK);
			return;
		}
	}

	if (fp != NULL)
	{
		if (m_modellist.GetCurSel() > 0)
		{
			MessageBox("Not Implement For This Model :(", NULL, MB_OK);
			exit(0);
		}
		int nRow = pM_Cyclic->GetRow();
		int nCol = pM_Cyclic->GetCol();
		
		fprintf(fp, "%d ; number of row \n", nRow);
		fprintf(fp, "%d ; number of colum \n", nCol);

		fprintf(fp, "%d ; number of states \n", Para_Cyclic->m_nStates);
		fprintf(fp, "%d ; neighborhood size \n", Para_Cyclic->m_nbr);
		fprintf(fp, "%4.2f; %4.2f; %4.2f; %4.2f; %4.2f; %4.2f; %4.2f; %4.2f; %4.2f; %4.2f; Birth-Death Rates \n",
			Para_Cyclic->m_a0,Para_Cyclic->m_b1,Para_Cyclic->m_a2,Para_Cyclic->m_b3,Para_Cyclic->m_a4, Para_Cyclic->m_b5,
			Para_Cyclic->m_a6,Para_Cyclic->m_b7,Para_Cyclic->m_a8,Para_Cyclic->m_b9);
		
		fprintf(fp, "%d; %d; Threshold Parameters\n", Para_Cyclic->m_bThreshold, Para_Cyclic->m_nThreshold);
		 
		for (int i = 0; i < nRow; i++)
		{
			for (int j = 0; j < nCol; j++)
			{
				fprintf(fp, "%d;", pM_Cyclic->State(i,j));
			
			}
			fprintf(fp, "\n");
		}


		fclose(fp);
	}
	
}


void CSssDlg::OnHelp() 
{
	::WinHelp(NULL, "SSSHELP.hlp", HELP_CONTENTS, NULL);	
}

void CSssDlg::OnTSR() 
{
	if (done || pause)
	{
		MessageBox("Dude, You need to run simulation to record", NULL, MB_OK);
		return;
	}

	if (m_modellist.GetCurSel() > 0)
	{
		MessageBox("Not Implement For This Model :(", NULL, MB_OK);
		return;
	}

	record = !record;
	if (record == true)
	{
		m_nRecordCount = 0;
	
		CFileDialog * pfd;
		pfd = new CFileDialog(FALSE, "tsr", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "tsr", NULL);
		pfd->m_ofn.lpstrFilter = "*.tsr";
		pfd->DoModal();

		CString str(pfd->GetPathName());
		if (!str.IsEmpty())
		{
			fp = fopen(str, "w");
			if (fp == NULL)
			{
				MessageBox("file open error", "File Handling Message", MB_OK);
				record = false;
				return;

			}
		}

		else
		{
			record = false;
			return;
		}

		m_tsr.SetWindowText("Finish");
		m_run.EnableWindow(FALSE);
		m_pause.EnableWindow(FALSE);

	}

	else {
			fclose(fp);
			m_tsr.SetWindowText("Record");
			m_run.EnableWindow();
			m_pause.EnableWindow();
	}
	

	
}


void CSssDlg::OnSelchangeModelList() 
{
	if(m_modellist.GetCurSel() == 0)
	{
		m_tsr.EnableWindow();
		m_filesave.EnableWindow();
		m_fileload.EnableWindow();

	}

	else
	{
		m_tsr.EnableWindow(FALSE);
		m_filesave.EnableWindow(FALSE);
		m_fileload.EnableWindow(FALSE);

	}
	
}

void CSssDlg::OnSpatialWnd() 
{
	pSpatial->DoModal();
	
}
