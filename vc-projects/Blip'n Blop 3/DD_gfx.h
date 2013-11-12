/******************************************************************
*
* 
*		----------------
*		  DD_gfx.h
*		----------------
*			
*
*		Fonctions graphiques PROPRES
*
*
*		Prosper / LOADED -   V 0.1
*
*
*
******************************************************************/


#ifndef _GFX_UTIL_
#define _GFX_UTIL_


//-----------------------------------------------------------------------------
//		Constantes pour la création des surfaces
//-----------------------------------------------------------------------------

#define DDSURF_VIDEO	1	// Mettre la surface en mémoire VIDEO
#define DDSURF_SYSTEM	2	// Mettre la surface en mémoire SYSTEM
#define DDSURF_BEST		4	// Mettre la surf en VIDEO si possible, SYSTEM sinon

//-----------------------------------------------------------------------------
//		Headers
//-----------------------------------------------------------------------------

#include <ddraw.h>

//-----------------------------------------------------------------------------
//		Objet 'ddraw' global (avec protection pour gfxutil.cpp)
//-----------------------------------------------------------------------------

#ifndef GFX_CPP_FILE
	extern IDirectDraw7 *	ddraw;
#endif

//-----------------------------------------------------------------------------
//		Prototypes
//-----------------------------------------------------------------------------

bool					DDInitDirectDraw();
bool					DDSetCooperativeLevel(HWND wh);
bool					DDSetCooperativeLevel(HWND wh, int flags);
bool					DDSetGfxMode(int x, int y, int d);
void					DDCloseDirectDraw();
IDirectDrawSurface7 *	DDCreatePrimary();
IDirectDrawSurface7 *	DDCreatePrimary(IDirectDrawSurface7 * & back);
IDirectDrawSurface7 *	DDCreateSurface(int x, int y);
IDirectDrawSurface7 *	DDCreateSurface(int x, int y, int flags);
IDirectDrawSurface7 *	DDLoadBMP(char * file);
IDirectDrawSurface7 *	DDLoadBMP(char * file, int flags);
HRESULT					DDCopyBMP(IDirectDrawSurface7 *surf, HBITMAP hbm);
IDirectDrawPalette *	DDLoadPalette(char * file);
DWORD					DDFindColor(IDirectDrawSurface7 *surf, COLORREF rgb);
HRESULT					DDSetColorKey(IDirectDrawSurface7 *surf, COLORREF rgb);
void					DDFlip();
void					DDFlipV();

#endif