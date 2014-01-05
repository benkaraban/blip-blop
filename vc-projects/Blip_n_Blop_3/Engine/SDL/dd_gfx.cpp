/******************************************************************
*
*
*		----------------
*		  DD_gfx.cpp
*		----------------
*
*
*
******************************************************************/


//-----------------------------------------------------------------------------
//		Protection pour ne pas déclarer 'ddraw' 2 fois (une fois dans le .h)
//-----------------------------------------------------------------------------

#define GFX_CPP_FILE

//-----------------------------------------------------------------------------
//		Headers
//-----------------------------------------------------------------------------

#include <stdio.h>
#include "lgx_packer.h"
#include "dd_gfx.h"
#include "globals.h"
#include "ben_debug.h"
#include "config.h"
#include "l_timer.h"

//-----------------------------------------------------------------------------
//		Objet 'ddraw' global REEL
//-----------------------------------------------------------------------------

IDirectDraw7 *	ddraw	= NULL;

static int	oldRefreshRate	= -1;

//-----------------------------------------------------------------------------
// Nom: DDInitDirectDraw
// Desc: Ouvre DirectDraw
//-----------------------------------------------------------------------------

bool DDInitDirectDraw()
{
	return SDL::Init();
}


//-----------------------------------------------------------------------------
// Nom: DDCloseDirectDraw()
// Desc: Ferme Direct Draw
//-----------------------------------------------------------------------------

void DDCloseDirectDraw()
{
	SDL::Close();
}

//-----------------------------------------------------------------------------
// Nom: DDSetCooperativeLevel
// Desc: Règle la priorité graphique à celle par défaut (GROS BILL)
//-----------------------------------------------------------------------------

bool DDSetCooperativeLevel(HWND wh)
{
	return SDL::SetCooperativeLevel(wh, DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN);
}


//-----------------------------------------------------------------------------
// Nom: DDSetCooperativeLevel
// Desc: Règle la priorité graphique
//-----------------------------------------------------------------------------

bool DDSetCooperativeLevel(HWND wh, int flags)
{
	return SDL::SetCooperativeLevel(wh, flags);
}


//-----------------------------------------------------------------------------
// Nom: DDSetGfxMode
// Desc: Règle la résolution graphique X Y NbBits/Pixel
//-----------------------------------------------------------------------------

bool DDSetGfxMode(int x, int y, int d)
{
	return SDL::SetGfxMode(x,y,d);
}

//-----------------------------------------------------------------------------
// Nom: DDCreateSurface
// Desc: Crée une Surface de taille X*Y
//-----------------------------------------------------------------------------

SDL::Texture * DDCreateSurface(int x, int y)
{
	return SDL::CreateSurface(x, y, DDSURF_BEST);
}

//-----------------------------------------------------------------------------
// Nom: DDCreateSurface
// Desc: Crée une Surface de taille X*Y en mém VIDEO / SYSTEM (cf DDOpenBMP)
//-----------------------------------------------------------------------------

SDL::Texture * DDCreateSurface(int x, int y, int flags)
{
	return SDL::CreateSurface(x,y,flags);
}

//-----------------------------------------------------------------------------
// Nom: DDCreatePrimary
// Desc: Crée une Primary Surface sans double buffer
//-----------------------------------------------------------------------------

SDL::Texture * DDCreatePrimary()
{
	return SDL::CreatePrimary();

}


//-----------------------------------------------------------------------------
// Nom: DDCreatePrimary
// Desc: Crée une Primary Surface avec double buffer (le paramètre)
//-----------------------------------------------------------------------------

SDL::Texture * DDCreatePrimary(SDL::Texture * & back)
{
	return SDL::CreatePrimary(back);
}


//-----------------------------------------------------------------------------
// Nom: DDLoadBMP
// Desc: Crée une surface ayant pour contenu une image (BMP)
//-----------------------------------------------------------------------------

IDirectDrawSurface7 * DDLoadBMP(char * file)
{
	return SDL::LoadBMP(file, DDSURF_BEST);
}


//-----------------------------------------------------------------------------
// Nom: DDLoadBMP
// Desc: Crée une surface ayant pour contenu l'image
//-----------------------------------------------------------------------------

IDirectDrawSurface7 * DDLoadBMP(char * file, int flags)
{
	return SDL::LoadBMP(file,flags);
}


//-----------------------------------------------------------------------------
// Nom: DDCopyBMP
// Desc: Copie une image Bitmap dans une surface
//-----------------------------------------------------------------------------

HRESULT	DDCopyBMP(SDL::Texture *pdds, HBITMAP hbm)
{
	return SDL::CopyBMP(pdds,hbm);
}


//-----------------------------------------------------------------------------
// Nom: DDFindColor
// Desc: Trouve la couleur correspondant à un RGB
//-----------------------------------------------------------------------------

DWORD DDFindColor(SDL::Texture *pdds, COLORREF rgb)
{
	return SDL::FindColor(pdds,rgb);

}


//-----------------------------------------------------------------------------
// Nom: DDSetColorKey
// Desc: Règle la couleur transparente d'une surface
//-----------------------------------------------------------------------------

HRESULT DDSetColorKey(SDL::Texture *surf, COLORREF rgb)
{
	return SDL::SetColorKey(surf,rgb);

}


//-----------------------------------------------------------------------------
// Nom: DDLoadPalette
// Desc: Charge une palette d'un fichier
//-----------------------------------------------------------------------------

IDirectDrawPalette * DDLoadPalette(char * file)
{
	return SDL::LoadPalette(file);

}


void DDFlip()
{
	SDL::Flip();
}

void DDFlipV()
{
	SDL::FlipV();
}
