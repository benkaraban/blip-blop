#include <SDL.h>

#include "sdl_surface.h"
#include "sdl_texture.h"

namespace SDL
{

public:
	
	bool					Init();
	bool					SetCooperativeLevel(HWND wh);
	bool					SetCooperativeLevel(HWND wh, int flags);
	bool					SetGfxMode(int x, int y, int d);
	void					Close();
	SDL::Texture *	CreatePrimary();
	SDL::Texture *	CreatePrimary(SDL::Texture * & back);
	SDL::Texture *	CreateSurface(int x, int y);
	SDL::Texture *	CreateSurface(int x, int y, int flags);
	SDL::Texture *	LoadBMP(char * file);
	SDL::Texture *	LoadBMP(char * file, int flags);
	HRESULT					CopyBMP(SDL::Texture *surf, HBITMAP hbm);
	IDirectDrawPalette *	LoadPalette(char * file);
	DWORD					FindColor(SDL::Texture *surf, COLORREF rgb);
	HRESULT					SetColorKey(SDL::Texture *surf, COLORREF rgb);
	void					Flip();
	void					FlipV();

};