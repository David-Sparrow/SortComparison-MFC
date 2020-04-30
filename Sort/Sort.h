
// Sort.h : main header file for the Sort application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CSortApp:
// See Sort.cpp for the implementation of this class
//

class CSortApp : public CWinApp
{
public:
	CSortApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CSortApp theApp;
