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
	if (ddraw != NULL) {
		debug << "DDInitDirectDraw / BenGfx.cpp->Direct Draw déjà initialisé!!!\n";
		return false;
	}
	if (DirectDrawCreateEx(NULL, (void **) &ddraw, IID_IDirectDraw7, NULL) != DD_OK) {
		debug << "DDInitDirectDraw / BenGfx.cpp->Ne peut pas créer DDraw\n";
		return false;
	}

	return true;
}


//-----------------------------------------------------------------------------
// Nom: DDCloseDirectDraw()
// Desc: Ferme Direct Draw
//-----------------------------------------------------------------------------

void DDCloseDirectDraw()
{
	if (ddraw == NULL) {
		debug << "DDCloseDirectDraw / BenGfx.cpp->DDraw déjà fermé!\n";
	} else {
		ddraw->Release();
		ddraw = NULL;
	}
}

//-----------------------------------------------------------------------------
// Nom: DDSetCooperativeLevel
// Desc: Règle la priorité graphique à celle par défaut (GROS BILL)
//-----------------------------------------------------------------------------

bool DDSetCooperativeLevel(HWND wh)
{
	return DDSetCooperativeLevel(wh, DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN);
}


//-----------------------------------------------------------------------------
// Nom: DDSetCooperativeLevel
// Desc: Règle la priorité graphique
//-----------------------------------------------------------------------------

bool DDSetCooperativeLevel(HWND wh, int flags)
{
	if (ddraw == NULL) {
		debug << "ddraw non initialisé pour (DDSetCooperativeLevel / BenGfx.cpp)\n";
		return false;
	}

	if (ddraw->SetCooperativeLevel(wh, flags) != DD_OK) {
		debug << "Erreur! (DDSetCooperativeLevel / BenGfx.cpp)\n";
		return false;
	} else
		return true;
}


//-----------------------------------------------------------------------------
// Nom: DDSetGfxMode
// Desc: Règle la résolution graphique X Y NbBits/Pixel
//-----------------------------------------------------------------------------

bool DDSetGfxMode(int x, int y, int d)
{
	if (ddraw == NULL) {
		debug << "DDSetGfxMode / BenGfx.cpp->ddraw non initialisé\n";
		return false;
	}

	if (ddraw->SetDisplayMode(x, y, d, 0, 0) != DD_OK) {
		debug << "DDSetGfxMode / BenGfx.cpp->";
		debug << "Ne peut pas utiliser le mode " << x << "x" << y << "x" << d << "\n";
		return false;
	} else
		return true;

}

//-----------------------------------------------------------------------------
// Nom: DDCreateSurface
// Desc: Crée une Surface de taille X*Y
//-----------------------------------------------------------------------------

IDirectDrawSurface7 * DDCreateSurface(int x, int y)
{
	return DDCreateSurface(x, y, DDSURF_BEST);
}

//-----------------------------------------------------------------------------
// Nom: DDCreateSurface
// Desc: Crée une Surface de taille X*Y en mém VIDEO / SYSTEM (cf DDOpenBMP)
//-----------------------------------------------------------------------------

IDirectDrawSurface7 * DDCreateSurface(int x, int y, int flags)
{
	// Pour éviter d'ecrire 10.000 fois le message "pas assez de vidéo"
	//
	static bool not_enough_video_prompt = false;

	IDirectDrawSurface7* surf;
	DDSURFACEDESC2       ddsd;

	if (ddraw == NULL) {
		debug << "DDCreateSurface()/BenGfx.cpp->ddraw non initialisé\n";
		return NULL;
	}


	ZeroMemory(&ddsd, sizeof(ddsd));
	ddsd.dwSize = sizeof(ddsd);
	ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
	ddsd.dwWidth = x;
	ddsd.dwHeight = y;

	// Création de la surface selon les flags

	if (!(flags & DDSURF_SYSTEM)) {
		// On essaye de créer la surface en Vidéo

		ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_VIDEOMEMORY ;

		if (ddraw->CreateSurface(&ddsd, &surf, NULL) != DD_OK) {
			// Impossible de la créer en VIDEO. Si on est en VIDEO->BUG
			// Si on est en BEST, on essaye en SYSTEM

			if (flags & DDSURF_BEST) {
				ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_SYSTEMMEMORY ;

				if (ddraw->CreateSurface(&ddsd, &surf, NULL) != DD_OK) {
					debug << "Ne peut pas créer de surface VIDEO/SYSTEME de" << x << "*" << y;
					debug << "(DDCreateSurface / BenGfx.cpp)\n";
					return NULL;
				} else if (!not_enough_video_prompt) {
					debug << "Ok. Pas assez de mem VIDEO pour" << x << "*" << y << " -> mem SYSTEM\n";
					not_enough_video_prompt = true;
				}

			} else {
				debug << "Ne peut pas créer de surface VIDEO de taille" << x << "*" << y << "DDCreateDurface / BenGfx.cpp)\n";
				return NULL;
			}
		}
	}	// Fin VIDEO / BEST
	else {
		// Là, on essaye directement en SYSTEM

		ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_SYSTEMMEMORY ;

		if (ddraw->CreateSurface(&ddsd, &surf, NULL) != DD_OK) {
			debug << "Ne peut pas créer de surface SYSTEM de taille" << x << "*" << y << "DDCreateDurface / BenGfx.cpp)\n";
			return NULL;
		}
	}

	return surf;
}

//-----------------------------------------------------------------------------
// Nom: DDCreatePrimary
// Desc: Crée une Primary Surface sans double buffer
//-----------------------------------------------------------------------------

IDirectDrawSurface7 * DDCreatePrimary()
{
	IDirectDrawSurface7* first;
	DDSURFACEDESC2       ddsd;

	if (ddraw == NULL) {
		debug << "DDCreatePrimary()/BenGfx.cpp->ddraw non initialisé\n";
		return NULL;
	}

	ddsd.dwSize = sizeof(ddsd);
	ddsd.dwFlags = DDSD_CAPS;
	ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE |
	                      DDSCAPS_VIDEOMEMORY |
	                      DDSCAPS_COMPLEX;
	ddsd.dwBackBufferCount = 0;

	if (ddraw->CreateSurface(&ddsd, &first, NULL) != DD_OK) {
		debug << "Ne peut pas ouvrir de surface PRIMAIRE!\n";
		return NULL;
	}

	return first;

}


//-----------------------------------------------------------------------------
// Nom: DDCreatePrimary
// Desc: Crée une Primary Surface avec double buffer (le paramètre)
//-----------------------------------------------------------------------------

IDirectDrawSurface7 * DDCreatePrimary(IDirectDrawSurface7 * & back)
{
	IDirectDrawSurface7* first;
	DDSURFACEDESC2       ddsd;
	DDSCAPS2			 ddsc;

	if (ddraw == NULL) {
		debug << "DDCreatePrimary()/BenGfx.cpp->ddraw non initialisé\n";
		return NULL;
	}

	ZeroMemory(&ddsd, sizeof(ddsd));
	ddsd.dwSize = sizeof(ddsd);
	ddsd.dwFlags = DDSD_CAPS |
	               DDSD_BACKBUFFERCOUNT;
	ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE |
	                      DDSCAPS_FLIP |
	                      DDSCAPS_VIDEOMEMORY |
	                      DDSCAPS_COMPLEX;
	ddsd.dwBackBufferCount = 1;

	if (ddraw->CreateSurface(&ddsd, &first, NULL) != DD_OK) {
		debug << "Ne peut pas ouvrir de surface PRIMAIRE!\n";
		back = NULL;
		return NULL;
	}

	ZeroMemory(&ddsc, sizeof(ddsc));
	ddsc.dwCaps = DDSCAPS_BACKBUFFER |
	              DDSCAPS_VIDEOMEMORY;

	if (first->GetAttachedSurface(&ddsc, &back) != DD_OK) {
		debug << "Ne peut pas créer de DOUBLE BUFFER!\n";

		first->Release();
		back = NULL;
		return NULL;
	}

	return first;
}


//-----------------------------------------------------------------------------
// Nom: DDLoadBMP
// Desc: Crée une surface ayant pour contenu une image (BMP)
//-----------------------------------------------------------------------------

IDirectDrawSurface7 * DDLoadBMP(char * file)
{
	return DDLoadBMP(file, DDSURF_BEST);
}


//-----------------------------------------------------------------------------
// Nom: DDLoadBMP
// Desc: Crée une surface ayant pour contenu l'image
//-----------------------------------------------------------------------------

IDirectDrawSurface7 * DDLoadBMP(char * file, int flags)
{
	HBITMAP             hbm;
	BITMAP              bm;
	IDirectDrawSurface7 *pdds;

	if (ddraw == NULL) {
		debug << "ddraw non initialisé pour " << file << " (DDLoadBMP / BenGfx.cpp)\n";
		return NULL;
	}

	hbm = (HBITMAP)LoadImage(GetModuleHandle(NULL), file, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);

	if (hbm == NULL)
		hbm = (HBITMAP)LoadImage(NULL, file, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

	if (hbm == NULL) {
		debug << "Ne peut pas ouvrir le fichier " << file << " (DDLoadBMP / BenGfx.cpp)\n";
		return NULL;
	}

	GetObject(hbm, sizeof(bm), &bm);

	pdds = DDCreateSurface(bm.bmWidth, bm.bmHeight, flags);
	if (pdds == NULL) {
		debug << "ERREUR : " << file << "\n";
		return NULL;
	}

	DDCopyBMP(pdds, hbm);

	DeleteObject(hbm);

	return pdds;

}


//-----------------------------------------------------------------------------
// Nom: DDCopyBMP
// Desc: Copie une image Bitmap dans une surface
//-----------------------------------------------------------------------------

HRESULT	DDCopyBMP(IDirectDrawSurface7 *pdds, HBITMAP hbm)
{
	HDC                 hdcImage;
	HDC                 hdc;
	BITMAP              bm;
	DDSURFACEDESC2      ddsd;
	HRESULT             hr;

	if (hbm == NULL || pdds == NULL) {
		debug << "Mauvais paramètres passés à DDCopyBMP (BenGfx.cpp) \n";
		return E_FAIL;
	}

	pdds->Restore();

	hdcImage = CreateCompatibleDC(NULL);
	if (!hdcImage)
		debug << "Ne peut pas créer de CompatibleDC (DDCopyBMP dans BenGfx.cpp)\n";

	SelectObject(hdcImage, hbm);

	GetObject(hbm, sizeof(bm), &bm);

	ddsd.dwSize = sizeof(ddsd);
	ddsd.dwFlags = DDSD_HEIGHT | DDSD_WIDTH;
	pdds->GetSurfaceDesc(&ddsd);

	if ((hr = pdds->GetDC(&hdc)) == DD_OK) {
		StretchBlt(hdc, 0, 0, ddsd.dwWidth, ddsd.dwHeight, hdcImage, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);
		pdds->ReleaseDC(hdc);
	}

	DeleteDC(hdcImage);

	return hr;
}


//-----------------------------------------------------------------------------
// Nom: DDFindColor
// Desc: Trouve la couleur correspondant à un RGB
//-----------------------------------------------------------------------------

DWORD DDFindColor(IDirectDrawSurface7 *pdds, COLORREF rgb)
{
	if (pdds == NULL) {
		debug << "surface NULL pour DDFindColor / BenGfx.cpp \n";
		return 0;
	}

	COLORREF		rgbT;
	HDC				hdc;
	DWORD			dw = CLR_INVALID;
	DDSURFACEDESC2	ddsd;
	HRESULT			hres;

	if (rgb != CLR_INVALID && pdds->GetDC(&hdc) == DD_OK) {
		rgbT = GetPixel(hdc, 0, 0);
		SetPixelV(hdc, 0, 0, rgb);
		pdds->ReleaseDC(hdc);
	} else {
		debug << "Ne peut pas obtenir le GDI dans DDFindColor / BenGfx.cpp\n";
		return 0;
	}

	ZeroMemory(&ddsd, sizeof(ddsd));
	ddsd.dwSize = sizeof(ddsd);

	while ((hres = pdds->Lock(NULL, &ddsd, DDLOCK_SURFACEMEMORYPTR | DDLOCK_WAIT, NULL)) == DDERR_WASSTILLDRAWING);

	if (hres == DD_OK) {
		dw  = *(WORD *)ddsd.lpSurface;                     // get DWORD
		dw &= 0xFFFF;//(1 << ddsd.ddpfPixelFormat.dwRGBBitCount)-1;  // mask it to bpp
		pdds->Unlock(NULL);
	} else {
		debug << "Ne peut pas locker la surface dans DDFindColor / BenGfx.cpp\n";
		return 0;
	}

	if (rgb != CLR_INVALID && pdds->GetDC(&hdc) == DD_OK) {
		SetPixel(hdc, 0, 0, rgbT);
		pdds->ReleaseDC(hdc);
	} else {
		debug << "Ne peut pas obtenir le GDI2 dans DDFindColor / BenGfx.cpp\n";
		return 0;
	}

	char buff[20];
	sprintf(buff, "%X", dw);
	debug << buff << "\n";

	return dw;

}


//-----------------------------------------------------------------------------
// Nom: DDSetColorKey
// Desc: Règle la couleur transparente d'une surface
//-----------------------------------------------------------------------------

HRESULT DDSetColorKey(IDirectDrawSurface7 *surf, COLORREF rgb)
{
	DDCOLORKEY          ddck;

	ddck.dwColorSpaceLowValue  = LGXpaker.findColor(rgb);
	ddck.dwColorSpaceHighValue = ddck.dwColorSpaceLowValue;

	return surf->SetColorKey(DDCKEY_SRCBLT, &ddck);

}


//-----------------------------------------------------------------------------
// Nom: DDLoadPalette
// Desc: Charge une palette d'un fichier
//-----------------------------------------------------------------------------

IDirectDrawPalette * DDLoadPalette(char * file)
{
	IDirectDrawPalette* ddpal;
	int                 i;
	int                 n;
	HANDLE              fh;
	HRSRC               h;
	LPBITMAPINFOHEADER  lpbi;
	PALETTEENTRY        ape[256];
	RGBQUAD *           prgb;
	DWORD               dwRead;

	for (i = 0; i < 256; i++) {
		ape[i].peRed   = (BYTE)(((i >> 5) & 0x07) * 255 / 7);
		ape[i].peGreen = (BYTE)(((i >> 2) & 0x07) * 255 / 7);
		ape[i].peBlue  = (BYTE)(((i >> 0) & 0x03) * 255 / 3);
		ape[i].peFlags = (BYTE)0;
	}

	if (file && (h = FindResource(NULL, file, RT_BITMAP))) {
		lpbi = (LPBITMAPINFOHEADER)LockResource(LoadResource(NULL, h));

		if (!lpbi) {
			debug << "DDLoadPalette / BenGfx.cpp -> Ne peut pas ouvrir " << file;
			return NULL;
		}
		prgb = (RGBQUAD*)((BYTE*)lpbi + lpbi->biSize);

		if (lpbi == NULL || lpbi->biSize < sizeof(BITMAPINFOHEADER))
			n = 0;
		else if (lpbi->biBitCount > 8)
			n = 0;
		else if (lpbi->biClrUsed == 0)
			n = 1 << lpbi->biBitCount;
		else
			n = lpbi->biClrUsed;

		//
		//  a DIB color table has its colors stored BGR not RGB
		//  so flip them around.
		//
		for (i = 0; i < n; i++) {
			ape[i].peRed   = prgb[i].rgbRed;
			ape[i].peGreen = prgb[i].rgbGreen;
			ape[i].peBlue  = prgb[i].rgbBlue;
			ape[i].peFlags = 0;
		}
	} else if (file && (fh = CreateFile(file, GENERIC_READ, FILE_SHARE_READ,
	                                    NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL,
	                                    NULL)) != INVALID_HANDLE_VALUE) {
		BITMAPFILEHEADER bf;
		BITMAPINFOHEADER bi;

		ReadFile(fh, &bf, sizeof(bf), &dwRead, NULL);
		ReadFile(fh, &bi, sizeof(bi), &dwRead, NULL);
		ReadFile(fh, ape, sizeof(ape), &dwRead, NULL);
		CloseHandle(fh);

		if (bi.biSize != sizeof(BITMAPINFOHEADER))
			n = 0;
		else if (bi.biBitCount > 8)
			n = 0;
		else if (bi.biClrUsed == 0)
			n = 1 << bi.biBitCount;
		else
			n = bi.biClrUsed;

		for (i = 0; i < n; i++) {
			BYTE r = ape[i].peRed;
			ape[i].peRed  = ape[i].peBlue;
			ape[i].peBlue = r;
		}
	}

	ddraw->CreatePalette(DDPCAPS_8BIT, ape, &ddpal, NULL);

	return ddpal;

}


void DDFlip()
{
	static DWORD lastTime = 0;

	if (vSyncOn) {
		primSurface->Flip(NULL, DDFLIP_WAIT);
	} else {
		primSurface->Flip(NULL, DDFLIP_WAIT | DDFLIP_NOVSYNC);
	}

	lastTime = LGetTime();
}

void DDFlipV()
{
	primSurface->Flip(NULL, DDFLIP_WAIT);
}
