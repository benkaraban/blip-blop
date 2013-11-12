// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__099615AB_58DB_11D4_8760_00A024851A35__INCLUDED_)
#define AFX_STDAFX_H__099615AB_58DB_11D4_8760_00A024851A35__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls

#include <mmsystem.h>	// Pour PlaySound()
#include <io.h>			// Pour _open
#include <fcntl.h>		// Pour _O_BINARY
#include <fstream.h>	// Pour les fichiers (C++)
#include <sys/stat.h>
#include "infossound.h"

#endif // _AFX_NO_AFXCMN_SUPPORT


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__099615AB_58DB_11D4_8760_00A024851A35__INCLUDED_)
