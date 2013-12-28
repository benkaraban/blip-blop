/******************************************************************
*
*
*			    LOADED corporation
*
*
*
*			(= CONFIDENTIAL DOCUMENT  =)
*
*
*
*			  	   Blip'n Blop 3
*
*
******************************************************************/

#define NAME			"Blip'n Blop"
#define CONFIG_FILE		"data\\bb.cfg"
#define	HISCORES_FILE	"data\\bb.scr"

#define WIN32_LEAN_AND_MEAN

#include <ddraw.h>
// #include <mmsystem.h> TODO?
#include <stdio.h>
#include <string.h>

#include "LTimer.h"
#include "Scroll.h"
#include "Picture.h"
#include "BenDebug.h"
#include "Input.h"
#include "DD_gfx.h"
#include "bendivers.h"
#include "Fonte.h"
#include "Globals.h"
#include "LGXpacker.h"
#include "PictureBank.h"
#include "SoundBankBB.h"
#include "Game.h"
#include "BenMaths.h"
#include "TxtData.h"
#include "Config.h"
#include "MusicBank.h"
#include "fmod.h"

Game	game;

HWND	WinHandle;

//FSOUND_SAMPLE * samp_test = NULL;

static bool safeMode	= false;

/************************************
 *   ReleaseAll
 */
void ReleaseAll(void) {
	if (ddraw != NULL) {
		fnt_menu.close();
		fnt_menus.close();
		fnt_cool.close();
		fnt_rpg.close();

		pbk_inter.close();

		LGXpaker.closePaker();

		if (videoA != NULL) {
			videoA->Release();
			videoA = NULL;
		}


		if (systemSurface != NULL) {
			systemSurface->Release();
			systemSurface = NULL;
		}

		if (primSurface != NULL) {
			primSurface->Release();
			primSurface = NULL;
		}

		DDCloseDirectDraw();
	}

	freeTxtData();
	freeMathsFunctions();

	mbk_inter.close();
	mbk_interl.close();

	FSOUND_Close();

	in.close();

	ChangeDisplaySettings(NULL, 0);

} // ReleaseAll ---------------------


/************************************
 *   Bug
 */
void Bug(const char * txt) {
	MessageBox(WinHandle, txt, "Blip'n Blop : Error reporting", MB_OK | MB_ICONERROR);
} // Bug ----------------------------


/************************************
 *   Warning
 */
void Warning(const char * txt) {
	MessageBox(WinHandle, txt, "Blip'n Blop : Warning", MB_OK | MB_ICONWARNING);

} // Bug ----------------------------

bool Question(const char * txt) {
	return (MessageBox(WinHandle, txt, "Blip'n Blop", MB_YESNO | MB_ICONQUESTION) == IDYES);
}

/************************************
 *   Win Proc
 */
long WINAPI WinProc(HWND WinHandle, UINT Msg, WPARAM wParam, LPARAM lParam) {
	switch (Msg) {
		case WM_SETCURSOR:			// CURSEUR --------
			SetCursor(NULL);
			return TRUE;
			break;

		case WM_ACTIVATE:
			active = !((BOOL)HIWORD(wParam));

			if (!active && winSet) {
				ChangeDisplaySettings(NULL, 0);
			}

			break;

		case WM_CLOSE:
			app_killed = TRUE;
//		want_to_kill_app = true;
			return 0;
			break;

		case WM_DESTROY:			// ARG! -----------
			app_killed = TRUE;
			PostQuitMessage(0);
			break;

		case WM_TIMER:
			fps_count = fps_current_count;
			fps_current_count = 0;
			break;
	}

	return DefWindowProc(WinHandle, Msg, wParam, lParam);

} // WinProc ----------------------

static void analyseCmdLine(char * cmd) {
	static const char sep [] = " ";
	char * token;

	token = strtok(cmd, sep);

	while (token != NULL) {
		if (strcmp(token, "/safe") == 0)
			safeMode = true;

		if (strcmp(token, "/cheat") == 0)
			cheat_on = true;

		if (strcmp(token, "/quiet") == 0)
			music_on = false;

		token = strtok(NULL, sep);
	}
}

/************************************
 *   Init
 */
static bool InitApp(HINSTANCE hInstance, int nCmdShow) {
	WNDCLASS			WinClass;

	//------------------------------------------------------------------
	//			Histoire d'avoir un joli fichier log
	//------------------------------------------------------------------

	debug << "---------------------------------------------------------------\n";
	debug << "Blip & Blop - (c) LOADED Studio - " << __DATE__ << "\n";
	debug << "---------------------------------------------------------------\n";

	//------------------------------------------------------------------
	//			Crée une fenêtre plein écran
	//------------------------------------------------------------------

	WinClass.style = CS_HREDRAW | CS_VREDRAW;
	WinClass.lpfnWndProc = WinProc;
	WinClass.cbClsExtra = 0;
	WinClass.cbWndExtra = 0;
	WinClass.hInstance = hInstance;
	WinClass.hIcon = 0; //TODO
	WinClass.hCursor = 0; //TODO
	WinClass.hbrBackground = 0; //TODO
	WinClass.lpszMenuName = NAME;
	WinClass.lpszClassName = NAME;
	RegisterClass(&WinClass);

	WinHandle = CreateWindowEx(
	                0,
	                NAME,
	                NAME,
	                WS_POPUP,
	                0,
	                0,
	                GetSystemMetrics(SM_CXSCREEN),
	                GetSystemMetrics(SM_CYSCREEN),
	                NULL,
	                NULL,
	                hInstance,
	                NULL);

	if (!WinHandle) {
		Bug("Cannot open a window. Reboot your system and try again.");
		ReleaseAll();
		return false;
	}

	ShowWindow(WinHandle, nCmdShow);
	UpdateWindow(WinHandle);

	for (int i = 0; i < 10; i++)
		manageMsg();



	//------------------------------------------------------------------
	//			Precalculs mathématiques
	//------------------------------------------------------------------

	preCalcMathsFunctions();


	//------------------------------------------------------------------
	//			FMOD / Sons
	//------------------------------------------------------------------

	if (!FSOUND_Init(44100, CHANNEL_NUMBER, 0)) {
		Warning("Cannot initialise FMOD. Sound will be turned off.");
		sound_on = false;
		music_on = false;
	} else {
		// Pour éviter que les musiques ne se fassent écraser par les sons
		//
		FSOUND_SetPriority(0, 255);
	}


	//------------------------------------------------------------------
	//			Timer
	//------------------------------------------------------------------

	LInitTimer();


	//------------------------------------------------------------------
	//			Charge la configuration
	//------------------------------------------------------------------

	load_BB3_config(CONFIG_FILE);

	//------------------------------------------------------------------
	//			Charge les hi scores
	//------------------------------------------------------------------

	hi_scores.init();

	if (!hi_scores.load(HISCORES_FILE)) {
		debug << "Cannot load hi-scores file. Use default hi-scores\n";
		hi_scores.init();
	} else {
		debug << "Using " << HISCORES_FILE << " as hiscores file\n";
	}


	//------------------------------------------------------------------
	//			Les fichiers textes
	//------------------------------------------------------------------

	if (lang_type == LANG_UK) {
		if (!loadTxtData("data\\uk.dat")) {
			Bug("Cannot open the file 'data\\uk.dat'");
			ReleaseAll();
			return false;
		}
	} else {
		if (!loadTxtData("data\\fr.dat")) {
			Bug("Cannot open the file 'data\\fr.dat'");
			ReleaseAll();
			return false;
		}
	}


	//------------------------------------------------------------------
	//			Direct Input
	//------------------------------------------------------------------

	if (!in.open(WinHandle, hInstance)) {
		Bug("Cannot initialise DirectInput. Make sure DirectX 7 or better is installed.");
		ReleaseAll();
		return false;
	}

	//------------------------------------------------------------------
	//			Direct Draw (1ère partie)
	//------------------------------------------------------------------

	if (!DDInitDirectDraw()) {
		Bug("Cannot initialise DirectDraw. Make sure DirectX 7 or better is installed.");
		ReleaseAll();
		return false;
	}

	/*
		// -------- Mode Windows ----------

		ddraw->SetCooperativeLevel(WinHandle, DDSCL_NORMAL);


		DDSURFACEDESC2 ddsd;
		ZeroMemory(&ddsd, sizeof(ddsd));

		ddsd.dwSize = sizeof( ddsd );
		ddsd.dwFlags = DDSD_CAPS;
		ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;

		if ( ddraw->CreateSurface( &ddsd, &primSurface, NULL) != DD_OK)
		{
			debug<<"Shit!\n";
			return false;
		}

		ZeroMemory(&ddsd, sizeof(ddsd));

		ddsd.dwSize = sizeof( ddsd );
		ddsd.dwFlags = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT;
		ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;
		ddsd.dwWidth = 640;  // whatever you want
		ddsd.dwHeight = 480; // whatever you want

		if ( ddraw->CreateSurface( &ddsd, &backSurface, NULL) != DD_OK)
		{
			debug<<"Shit2!\n";
			return false;
		}

	*/

	// Mode EXCLUSIF (bourrin quoi...)

	if (!DDSetCooperativeLevel(WinHandle)) {
		Bug("Cannot get EXCLUSIVE MODE. Close all other applications and launch Blip'n Blop again");
		ReleaseAll();
		return false;
	}

	static const int BEST_RATE = 85;

	if (safeMode) {
		debug << "Safe mode enabled, using default 640x480x16 refresh rate.\n";
		winSet = false;

		if (!DDSetGfxMode(640, 480, 16)) {
			Bug("Cannot set display mode to 640x480x16. Are you sure your video card meets the requirements ?");
			ReleaseAll();
			return false;
		}
	} else {
		DEVMODE dm;

		ZeroMemory(&dm, sizeof(dm));
		dm.dmSize = sizeof(dm);
		dm.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFREQUENCY;
		dm.dmPelsWidth	= 640;
		dm.dmPelsHeight = 480;
		dm.dmBitsPerPel = 16;
		dm.dmDisplayFrequency = BEST_RATE;

		if (ChangeDisplaySettings(&dm, CDS_TEST) != DISP_CHANGE_SUCCESSFUL ||
		        ChangeDisplaySettings(&dm, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL) {
			debug << "Cannot set 640x480x16 at " << BEST_RATE << " Hz.\n";
			winSet = false;

			if (!DDSetGfxMode(640, 480, 16)) {
				Bug("Cannot set display mode to 640x480x16. Are you sure your video card meets the requirements ?");
				ReleaseAll();
				return false;
			}

			debug << "Using default 640x480x16 refresh rate.\n";
			vSyncOn = true;
		} else {
			debug << "Set 640x480x16 at " << BEST_RATE << " Hz.\n";
			winSet = true;
			vSyncOn = true;
		}
	}


	DDSCAPS2		ddscaps2dummy;
	DWORD			vid_mem1;
	DWORD			vid_mem2;

	ZeroMemory(&ddscaps2dummy, sizeof(ddscaps2dummy));
	ddscaps2dummy.dwCaps = DDSCAPS_VIDEOMEMORY;
	ddraw->GetAvailableVidMem(&ddscaps2dummy, &vid_mem1, &vid_mem2);
	debug << "Available video memory : " << (vid_mem2 >> 10) << " Ko\n";
	mem_flag = DDSURF_BEST;
	video_buffer_on = true;

	if (vid_mem2 >> 10 >= 20) {
		mustFixGforceBug = true;
	}

	//------------------------------------------------------------------
	//			Direct Draw (suite)
	//------------------------------------------------------------------

	// Crée la surface primaire avec double buffer

	primSurface = DDCreatePrimary(backSurface);

	if (primSurface == NULL || backSurface == NULL) {
		Bug("Cannot get a primary surface. Please reboot your PC and try to launch Blip'n Blop again.\nBe sure you have at least 2 Mb of video memory on your video card.");
		ReleaseAll();
		return false;
	}


	//------------------------------------------------------------------
	//			Surface système
	//------------------------------------------------------------------

	systemSurface = DDCreateSurface(640, 480, DDSURF_SYSTEM);

	if (systemSurface == NULL) {
		Bug("Not enough memory. Blip'n Blop needs 32 Mo of free memory. Try to close all other applications and launch Blip'n Blop again.");
		ReleaseAll();
		return false;
	}



	//------------------------------------------------------------------
	//			LGX paker
	//------------------------------------------------------------------

	if (!LGXpaker.init(primSurface)) {
		Bug("Cannot initialise LGX paker. Please get the latest drivers for your video card.");
		ReleaseAll();
		return false;
	}


	//------------------------------------------------------------------
	//			Scroll buffers
	//------------------------------------------------------------------

	debug << "Creating video buffer of size " << (WANTED_VBUFFER_WIDE) << "...";
	videoA = DDCreateSurface(WANTED_VBUFFER_WIDE, 480, DDSURF_VIDEO);

	if (videoA == NULL) {
		debug << "Failed\n";
		debug << "Creating video buffer of size " << (WANTED_VBUFFER_WIDE - 100) << "...";
		videoA = DDCreateSurface(WANTED_VBUFFER_WIDE - 100, 480, DDSURF_VIDEO);

		if (videoA == NULL) {
			debug << "Failed\n";
			debug << "Creating video buffer (" << (WANTED_VBUFFER_WIDE - 200) << ")...";
			videoA = DDCreateSurface(WANTED_VBUFFER_WIDE - 200, 480, DDSURF_VIDEO);

			if (videoA == NULL) {
				debug << "Failed\n";
				videoA = DDCreateSurface(WANTED_VBUFFER_WIDE, 480, DDSURF_SYSTEM);

				if (videoA == NULL) {
					Bug("Not enough memory. Blip'n Blop needs 32 Mo of free memory. Try to close all other applications and launch Blip'n Blop again.");
					ReleaseAll();
					return false;
				}

				debug << "Cannot create video buffer. Use system buffer instead.\n";
				vbuffer_wide = WANTED_VBUFFER_WIDE;
				mem_flag = DDSURF_SYSTEM;
				video_buffer_on = false;
			} else {
				debug << "Ok\n";
				vbuffer_wide = WANTED_VBUFFER_WIDE - 200;
			}
		} else {
			debug << "Ok\n";
			vbuffer_wide = WANTED_VBUFFER_WIDE - 100;
		}
	} else {
		debug << "Ok\n";
		vbuffer_wide = WANTED_VBUFFER_WIDE;
	}


	//------------------------------------------------------------------
	//			Chargement des fontes
	//------------------------------------------------------------------

	if (!fnt_menu.load("data\\menu.lft", mem_flag)) {
		Bug("Cannot open the file data\\menu.lft");
		ReleaseAll();
		return false;
	}

	if (!fnt_menus.load("data\\menus.lft", mem_flag)) {
		Bug("Cannot open the file data\\menus.lft");
		ReleaseAll();
		return false;
	}

	if (!fnt_cool.load("data\\cool.lft", mem_flag)) {
		Bug("Cannot open the file data\\cool.lft");
		ReleaseAll();
		return false;
	}

	if (!fnt_rpg.load("data\\rpg.lft", mem_flag)) {
		Bug("Cannot open the file data\\rpg.lft");
		ReleaseAll();
		return false;
	}
	/*
		if ( !fnt_score_blip.load( "data\\scorei.lft", mem_flag))
		{
			Bug("Cannot open the file data\\scorei.lft");
			ReleaseAll();
			return false;
		}

		if ( !fnt_score_blop.load( "data\\scoreo.lft", mem_flag))
		{
			Bug("Cannot open the file data\\scoreo.lft");
			ReleaseAll();
			return false;
		}
	*/
	//------------------------------------------------------------------
	//			Chargement de l'interface
	//------------------------------------------------------------------

	if (!pbk_inter.loadGFX("data\\inter.gfx", DDSURF_BEST)) {
		debug << "Cannot load interface.\n";
		return false;
	} else {
		debug << "Successfully loaded interface.\n";
	}

	if (!mbk_inter.open("data\\inter.mbk", false)) {
		debug << "Cannot load interface musics.\n";
		return false;
	}

	if (!mbk_interl.open("data\\interl.mbk", true)) {
		debug << "Cannot load interface musics (p2).\n";
		return false;
	}

	//------------------------------------------------------------------
	//			Mémoire video restante
	//------------------------------------------------------------------

	ZeroMemory(&ddscaps2dummy, sizeof(ddscaps2dummy));
	ddscaps2dummy.dwCaps = DDSCAPS_VIDEOMEMORY;
	ddraw->GetAvailableVidMem(&ddscaps2dummy, &vid_mem1, &vid_mem2);
	debug << "Available video memory : " << (vid_mem2 >> 10) << " Ko\n";

	//------------------------------------------------------------------
	//			Mise en place du TIMER pour obtenir les FPS
	//------------------------------------------------------------------

	SetTimer(WinHandle, 1, 1000, NULL);

	return true; // C'est fini!

} // Init ---------------------------


/************************************
 *   WinMain
 */

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nCmdShow) {
	//------------------------------------------------------------------
	//			Safe mode ?
	//------------------------------------------------------------------

	analyseCmdLine(lpCmdLine);

	//------------------------------------------------------------------
	//			Initialise l'application
	//------------------------------------------------------------------

	if (!InitApp(hInstance, nCmdShow))
		return -1;

	//------------------------------------------------------------------
	//			Joue la partie
	//------------------------------------------------------------------

	game.go();

	//------------------------------------------------------------------
	//			On quitte plus ou moins proprement
	//------------------------------------------------------------------

	debug << "---------------------------------------------------------------\n";
	debug << "Releasing Blip & Blop\n";
	debug << "---------------------------------------------------------------\n";

	// Désalloue tout ce qu'il faut (en théorie)
	//
	ReleaseAll();

	// Sauvegarde les hi-scores
	//
	if (!hi_scores.save(HISCORES_FILE)) {
		debug << "Cannot save hi-scores\n";
	} else {
		debug << "Saving " << HISCORES_FILE << " as hi-scores file.\n";
	}

	// Sauvegarde la configuration
	//
	save_BB3_config(CONFIG_FILE);

	// Détruit la fenêtre
	//
	DestroyWindow(WinHandle);

	return 0;

} // WinMain ------------------------
