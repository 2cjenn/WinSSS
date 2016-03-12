#if !defined(AFX_SPATIALWND_H__82FBA9E9_075A_4096_9C0C_E13C89585DAE__INCLUDED_)
#define AFX_SPATIALWND_H__82FBA9E9_075A_4096_9C0C_E13C89585DAE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SpatialWnd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SpatialWnd dialog

class SpatialWnd : public CDialog
{
// Construction
public:
	SpatialWnd(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(SpatialWnd)
	enum { IDD = IDD_SPATIAL_WND_DLG };
	int		m_sp1;
	int		m_sp2;
	int		m_steplength;
	int		m_posx;
	int		m_posy;
	int		m_wndsize;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SpatialWnd)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(SpatialWnd)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPATIALWND_H__82FBA9E9_075A_4096_9C0C_E13C89585DAE__INCLUDED_)
