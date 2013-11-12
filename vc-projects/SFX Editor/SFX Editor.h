// SFX Editor.h : main header file for the SFX EDITOR application
//

#if !defined(AFX_SFXEDITOR_H__099615A7_58DB_11D4_8760_00A024851A35__INCLUDED_)
#define AFX_SFXEDITOR_H__099615A7_58DB_11D4_8760_00A024851A35__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSFXEditorApp:
// See SFX Editor.cpp for the implementation of this class
//

class CSFXEditorApp : public CWinApp
{
public:
	CSFXEditorApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSFXEditorApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSFXEditorApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SFXEDITOR_H__099615A7_58DB_11D4_8760_00A024851A35__INCLUDED_)
