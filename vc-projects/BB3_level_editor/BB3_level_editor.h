// BB3_level_editor.h : main header file for the BB3_LEVEL_EDITOR application
//

#if !defined(AFX_BB3_LEVEL_EDITOR_H__D9A8CEE4_4D23_11D4_8760_00A024851A35__INCLUDED_)
#define AFX_BB3_LEVEL_EDITOR_H__D9A8CEE4_4D23_11D4_8760_00A024851A35__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CBB3_level_editorApp:
// See BB3_level_editor.cpp for the implementation of this class
//

class CBB3_level_editorApp : public CWinApp
{
public:
	CBB3_level_editorApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBB3_level_editorApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CBB3_level_editorApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BB3_LEVEL_EDITOR_H__D9A8CEE4_4D23_11D4_8760_00A024851A35__INCLUDED_)
