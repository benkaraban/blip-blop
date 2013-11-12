// FNT Editor.h : main header file for the FNT EDITOR application
//

#if !defined(AFX_FNTEDITOR_H__0F907866_5B29_11D4_8760_00A024851A35__INCLUDED_)
#define AFX_FNTEDITOR_H__0F907866_5B29_11D4_8760_00A024851A35__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CFNTEditorApp:
// See FNT Editor.cpp for the implementation of this class
//

class CFNTEditorApp : public CWinApp
{
public:
	CFNTEditorApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFNTEditorApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CFNTEditorApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FNTEDITOR_H__0F907866_5B29_11D4_8760_00A024851A35__INCLUDED_)
