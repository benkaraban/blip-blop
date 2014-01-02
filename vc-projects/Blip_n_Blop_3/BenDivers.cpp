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

#include <windows.h>

bool active = false;
bool app_killed = false;
bool want_to_kill_app = false;

//-----------------------------------------------------------------------------

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

//-----------------------------------------------------------------------------

void wait(int t)
{
	unsigned int i = GetTickCount();

	while (GetTickCount() < (i + t));
}


