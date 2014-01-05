#include "sdl.h"

namespace SDL
{

	SDL_Window *window=0;
	SDL_Renderer *renderer==;

public:
	
	bool Init()
	{
		if (SDL_Init(SDL_INIT_EVERYTHING) == -1){
			std::cout << SDL_GetError() << std::endl;
			return false;
		}
		return true;
	}
	
	
	bool SetCooperativeLevel(HWND wh)
	{
	
	}
	
	bool SetCooperativeLevel(HWND wh, int flags)
	{
	
	}
	
	bool SetGfxMode(int x, int y, int d)
	{
		if(renderer!=0)
		{
			SDL_DestroyRenderer(renderer);
			renderer=0;
		}
		if(window!=0)
		{
			SDL_DestroyWindow(window);
			window = 0;
		}
		
		win = SDL_CreateWindow("Blip&Blop", 100, 100, x, y, SDL_WINDOW_SHOWN);
		if (win == 0){
			std::cout << SDL_GetError() << std::endl;
			return false;
		}
		
		renderer = 0;
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (renderer == 0){
			std::cout << SDL_GetError() << std::endl;
			return false;
		}
		
		
		
		return true;
	}
	
	void Close()
	{
		if(renderer!=0)
		{
			SDL_DestroyRenderer(renderer);
			renderer=0;
		}
		if(window!=0)
		{
			SDL_DestroyWindow(window);
			window = 0;
		}
	}
	
	SDL::Texture *	CreatePrimary()
	{
		return 0;
	}
	
	SDL::Texture *	CreatePrimary(SDL::Texture * & back)
	{
		return 0;
	}
	
	SDL::Texture *	CreateSurface(int x, int y)
	{
		return new SDL::Texture(SDL_CreateTexture(renderer,SDL_PIXELFORMAT_ARGB8888,SDL_TEXTUREACCESS_STREAMING,x,y));
	}
	
	SDL::Texture *	CreateSurface(int x, int y, int flags)
	{
		return new SDL::Texture(SDL_CreateTexture(renderer,SDL_PIXELFORMAT_ARGB8888,SDL_TEXTUREACCESS_STREAMING,x,y));
	}
	
	SDL::Texture *	LoadBMP(char * file)
	{
		return SDL::LoadBMP(file,0);
	}
	
	SDL::Texture *	LoadBMP(char * file, int flags)
	{
		SDL_Surface *bmp = 0;
		bmp = SDL_LoadBMP(file);
		if (bmp == 0){
				std::cout << SDL_GetError() << std::endl;
				return 0;
		}
		SDL_Texture *tex = 0;
		tex = SDL_CreateTextureFromSurface(ren, bmp);
		SDL_FreeSurface(bmp);
		return new SDL::Texture(tex);
	}
	
	HRESULT					CopyBMP(SDL::Texture *surf, HBITMAP hbm)
	{
		//Seems not used
		return 0;
	}
	
	IDirectDrawPalette *	LoadPalette(char * file)
	{
		//Seems not used
		return 0;
	}
	
	DWORD					FindColor(SDL::Texture *surf, COLORREF rgb)
	{
		//Seems not used
		return 0;
	}
	
	HRESULT					SetColorKey(SDL::Texture *surf, COLORREF rgb)
	{
		
	}
	
	void					Flip()
	{
		SDL_RenderPresent(renderer);
	}
	
	void					FlipV()
	{
		
	}

};