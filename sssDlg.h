// sssDlg.h : header file
//


#if !defined(AFX_SSSDLG_H__B1A74BE4_F5F0_4A71_85E0_6EAF2BFE3A64__INCLUDED_)
#define AFX_SSSDLG_H__B1A74BE4_F5F0_4A71_85E0_6EAF2BFE3A64__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSssDlg dialog


#include "sssWnd.h"	// Added by ClassView
#include "ModelTemplate.h"
#include "Model_EP.h"
#include "Model_Contact.h"
#include "Model_Cyclic.h"

#include "Model_RSP.h"
#include "Model_LVoter.h"
#include "Model_GH.h"
#include "Model_MultiContact.h"
#include "afxwin.h"

#include "ParaDlg_Cyclic.h"
#include "ParaDlg_Contact.h"
#include "ParaDlg_EP.h"
#include "ParaDlg_GH.h"

#include "ParaDlg_RSP.h"
#include "ParaDlg_Voter.h"
#include "ParaDlg_MultiCont.h"

#include "SpatialWnd.h"

class CSssDlg : public CDialog
{
// Construction
public:

	FILE * fp;
	bool record;

	SpatialWnd * pSpatial;

	ParaDlg_Cyclic * Para_Cyclic;
	ParaDlg_Contact * Para_Contact;
	ParaDlg_Ep * Para_EP;
	ParaDlg_GH * Para_GH;

	ParaDlg_RSP * Para_RSP;
	ParaDlg_Voter * Para_Voter;
	ParaDlg_MultiCont * Para_MultiCont;

	Model_MultiContact * pM_MultiCont;

	Model_EP * pM_EP;
	Model_Contact * pM_Contact;
	Model_RSP * pM_RSP;
	Model_LVoter * pM_LV;
	Model_GH * pM_GH;
	Model_Cyclic * pM_Cyclic;
	
public:
	friend class sssWnd;
	CSssDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CSssDlg)
	enum { IDD = IDD_SSS_DIALOG };
	CEdit	m_EditRecord;
	CButton	m_tsr;
	CButton	m_filesave;
	CButton	m_fileload;
	CComboBox	m_mapsize;
	CComboBox	m_modellist;
	CTabCtrl	m_MultiView;
	sssWnd	m_line;
	sssWnd	m_view;
	sssWnd  m_legend;
	CButton	m_pause;
	CButton	m_para;
	CSliderCtrl	m_speed;
	CButton	m_run;
	int		m_nRecordCount;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSssDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSssDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnRun();
	afx_msg void OnPause();
	afx_msg void OnParameter();
	afx_msg void OnClose();
	afx_msg void OnLinesShiftUp();
	afx_msg void OnLinesShiftDn();
	afx_msg void OnLinesEnlargeDn();
	afx_msg void OnLinesEnlargeUp();
	afx_msg void OnMapEnlargeUp();
	afx_msg void OnMapEnlargeDn();
	afx_msg void OnSelchangeMultiView(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangeMapSize();
	afx_msg void OnFileSave();
	afx_msg void OnFileLoad();
	afx_msg void OnHelp();
	afx_msg void OnTSR();
	afx_msg void OnSelchangeModelList();
	afx_msg void OnSpatialWnd();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	double dMapDist;
	double dLinesDist;
	int nLinesPos;
	int nStepCount;
	int m_nRowCol;
	
	bool pause;
	bool done;
	void go();

	int nShowPortrait; 
	bool readfromfile;
	
//	CListBox m_listbox_mapsize;
public:
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SSSDLG_H__B1A74BE4_F5F0_4A71_85E0_6EAF2BFE3A64__INCLUDED_)
