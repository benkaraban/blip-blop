#include <SDL_main.h>

#include "sdl_surface.h"

namespace SDL
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
	IDirectDrawPalette *	LoadPalette(char * file);
	DWORD					FindColor(SDL::Surface *surf, COLORREF rgb);
	HRESULT					SetColorKey(SDL::Surface *surf, COLORREF rgb);
	void					Flip();
	void					FlipV();

};