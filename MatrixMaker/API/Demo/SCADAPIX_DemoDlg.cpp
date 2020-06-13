
// SCADAPIX_DemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SCADAPIX_Demo.h"
#include "SCADAPIX_DemoDlg.h"

#include "SCADAPIX.hxx"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#pragma comment(lib, "SCADAPIX.lib" )

#ifdef _DEBUG

#ifdef _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' "            \
	"name='" __LIBRARIES_ASSEMBLY_NAME_PREFIX ".CRT' "              \
	"version='" _CRT_ASSEMBLY_VERSION "' "                          \
	"processorArchitecture='x86' "                                  \
	"publicKeyToken='" _VC_ASSEMBLY_PUBLICKEYTOKEN "'\"")

#pragma comment(linker,"/manifestdependency:\"type='win32' "        \
	"name='" __LIBRARIES_ASSEMBLY_NAME_PREFIX ".MFC' "              \
	"version='" _MFC_ASSEMBLY_VERSION "' "                          \
	"processorArchitecture='x86' "                                  \
	"publicKeyToken='" _VC_ASSEMBLY_PUBLICKEYTOKEN "'\"")

#else
#pragma comment(linker,"/manifestdependency:\"type='win32' "            \
	"name='" __LIBRARIES_ASSEMBLY_NAME_PREFIX ".CRT' "              \
	"version='" _CRT_ASSEMBLY_VERSION "' "                          \
	"processorArchitecture='amd64' "                                \
	"publicKeyToken='" _VC_ASSEMBLY_PUBLICKEYTOKEN "'\"")

#pragma comment(linker,"/manifestdependency:\"type='win32' "        \
	"name='" __LIBRARIES_ASSEMBLY_NAME_PREFIX ".MFC' "              \
	"version='" _MFC_ASSEMBLY_VERSION "' "                          \
	"processorArchitecture='amd64' "                                \
	"publicKeyToken='" _VC_ASSEMBLY_PUBLICKEYTOKEN "'\"")
#endif

#endif

// CSCADAPIX_DemoDlg dialog

CSCADAPIX_DemoDlg::CSCADAPIX_DemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSCADAPIX_DemoDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSCADAPIX_DemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSCADAPIX_DemoDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_Test, &CSCADAPIX_DemoDlg::OnBnClickedButtonTest)
	ON_BN_CLICKED(IDC_BUTTON_Test2, &CSCADAPIX_DemoDlg::OnBnClickedButtonTest2)
	ON_BN_CLICKED(IDC_BUTTON_Test3, &CSCADAPIX_DemoDlg::OnBnClickedButtonTest3)
END_MESSAGE_MAP()


// CSCADAPIX_DemoDlg message handlers

BOOL CSCADAPIX_DemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSCADAPIX_DemoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

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

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSCADAPIX_DemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void APITestNewProject( );
void APITestReadProject( );
void APITestResultProject( );

void CSCADAPIX_DemoDlg::OnBnClickedButtonTest()
{
	APITestNewProject( );
}

void CSCADAPIX_DemoDlg::OnBnClickedButtonTest2()
{
	APITestReadProject( );
}

void CSCADAPIX_DemoDlg::OnBnClickedButtonTest3()
{
	APITestResultProject( );
}
