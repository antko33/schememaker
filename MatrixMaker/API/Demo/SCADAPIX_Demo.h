
// SCADAPIX_Demo.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CSCADAPIX_DemoApp:
// See SCADAPIX_Demo.cpp for the implementation of this class
//

class CSCADAPIX_DemoApp : public CWinAppEx
{
public:
	CSCADAPIX_DemoApp();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CSCADAPIX_DemoApp theApp;