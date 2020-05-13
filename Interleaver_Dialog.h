// Interleaver_Dialog.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols



// CInterleaver_DialogApp:
// See Interleaver_Dialog.cpp for the implementation of this class
//

class CInterleaver_DialogApp : public CWinApp
{
public:
	CInterleaver_DialogApp();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CInterleaver_DialogApp theApp;