#pragma once

#include <SDL.h>

#include <iostream>
#include <windows.h>

#include "sdl_surface.h"
#include "sdl_texture.h"

/*Nulled dd flags*/
#define DDBLTFAST_WAIT 0
#define DDBLTFAST_NOCOLORKEY 0
#define DDBLTFAST_SRCCOLORKEY 0

#define DD_OK true
/**/

using namespace std;

struct RenderRect
{
	int left;
	int right;
	int top;
	int bottom;
	unsigned int dwFillColor;
	int dwSize;
};

typedef RenderRect DDBLTFX;

class Graphics
{
	
public:

	bool					Init();
	bool					SetCooperativeLevel(HWND wh);
	bool					SetCooperativeLevel(HWND wh, int flags);
	bool					SetGfxMode(int x, int y, int d);
	void					Close();
	SDL::Surface *	CreatePrimary();
	SDL::Surface *	CreatePrimary(SDL::Surface * & back);
	SDL::Surface *	CreateSurface(int x, int y);
	SDL::Surface *	CreateSurface(int x, int y, int flags);
	SDL::Surface *	LoadBMP(char * file);
	SDL::Surface *	LoadBMP(char * file, int flags);
	HRESULT					CopyBMP(SDL::Surface *surf, HBITMAP hbm);
	void *	LoadPalette(char * file);
	DWORD					FindColor(SDL::Surface *surf, COLORREF rgb);
	HRESULT					SetColorKey(SDL::Surface *surf, COLORREF rgb);
	void					Flip();
	void					FlipV();

	void Clear(int r = 0, int g = 0, int b = 0);
	void Clear(int);
	void Clear(RenderRect);

	void RestoreAllSurfaces(){};
};