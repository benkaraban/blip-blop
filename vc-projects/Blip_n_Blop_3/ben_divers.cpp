/******************************************************************
*
*
*		----------------
*		   BenDivers.cpp
*		----------------
*
*
*		Fonction très diverses
*
*
*		Prosper / LOADED -   V 0.2
*
*
*
******************************************************************/

//-----------------------------------------------------------------------------
//		Headers
//-----------------------------------------------------------------------------

bool active = false;
bool app_killed = false;
bool want_to_kill_app = false;

//-----------------------------------------------------------------------------

#if defined(_WIN32) || defined(__MINGW32__)

#include <windows.h>

int manageMsg()
{
	MSG		msg;

	if (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE)) {
		if (!GetMessage(&msg, NULL, 0, 0))
			return msg.wParam;
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}
#else
int manageMsg() {
    return 0;
}
#endif

