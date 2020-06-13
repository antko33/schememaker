
// SCADAPIX_DemoDlg.h : header file
//

#pragma once


// CSCADAPIX_DemoDlg dialog
class CSCADAPIX_DemoDlg : public CDialog
{
// Construction
public:
	CSCADAPIX_DemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_SCADAPIX_DEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonTest();
	afx_msg void OnBnClickedButtonTest2();
	afx_msg void OnBnClickedButtonTest3();
};
