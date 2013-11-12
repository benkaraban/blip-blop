// BB3_level_editor.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "BB3_level_editor.h"
#include "BB3_level_editorDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBB3_level_editorApp

BEGIN_MESSAGE_MAP(CBB3_level_editorApp, CWinApp)
	//{{AFX_MSG_MAP(CBB3_level_editorApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBB3_level_editorApp construction

CBB3_level_editorApp::CBB3_level_editorApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CBB3_level_editorApp object

CBB3_level_editorApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CBB3_level_editorApp initialization

BOOL CBB3_level_editorApp::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CBB3_level_editorDlg dlg;
	m_pMainWnd = &dlg;

	int nResponse = dlg.DoModal();
	
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
