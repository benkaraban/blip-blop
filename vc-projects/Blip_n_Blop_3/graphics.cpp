#pragma once

#include "graphics.h"

extern SDL::Surface	*	primSurface;

class Graphics
{

	SDL_Window *window=0;
	SDL_Renderer *renderer=0;
	
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
		
		window = SDL_CreateWindow("Blip&Blop", 100, 100, x, y, SDL_WINDOW_SHOWN);
		if (window == 0){
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
	
	SDL::Surface *	CreatePrimary()
	{
		return 0;
	}
	
	SDL::Surface *	CreatePrimary(SDL::Surface * & back)
	{
		return 0;
	}
	
	SDL::Surface *	CreateSurface(int x, int y)
	{
		return new SDL::Surface(SDL_CreateTexture(renderer,SDL_PIXELFORMAT_ARGB8888,SDL_TEXTUREACCESS_STREAMING,x,y));
	}
	
	SDL::Surface *	CreateSurface(int x, int y, int flags)
	{
		return new SDL::Surface(SDL_CreateTexture(renderer,SDL_PIXELFORMAT_ARGB8888,SDL_TEXTUREACCESS_STREAMING,x,y));
	}
	
	SDL::Surface *	LoadBMP(char * file)
	{
		return this->LoadBMP(file,0);
	}
	
	SDL::Surface *	LoadBMP(char * file, int flags)
	{
		/*SDL_Surface *bmp = 0;
		bmp = SDL_LoadBMP(file);
		if (bmp == 0){
				std::cout << SDL_GetError() << std::endl;
				return 0;
		}
		SDL_Texture *tex = 0;
		tex = SDL_CreateTextureFromSurface(ren, bmp);
		SDL_FreeSurface(bmp);
		return new SDL::Surface(tex);*/
		SDL_Surface *bmp = 0;
		bmp = SDL_LoadBMP(file);
		if (bmp == 0){
			std::cout << SDL_GetError() << std::endl;
			return 0;
		}
		return new SDL::Surface(bmp);
	}
	
	HRESULT					CopyBMP(SDL::Surface *surf, HBITMAP hbm)
	{
		//Seems not used
		return 0;
	}
	
	void *	LoadPalette(char * file)
	{
		//Seems not used
		return 0;
	}
	
	DWORD					FindColor(SDL::Surface *surf, COLORREF rgb)
	{
		//Seems not used
		return 0;
	}
	
	HRESULT					SetColorKey(SDL::Surface *surf, COLORREF rgb)
	{
		
	}
	
	void					Flip()
	{

		SDL_Texture *tex = 0;
		tex = SDL_CreateTextureFromSurface(renderer, primSurface->Get());
		SDL_RenderCopy(renderer, tex, NULL, NULL);
		SDL_RenderPresent(renderer);

		SDL_DestroyTexture(tex);
	}
	
	void					FlipV()
	{
		Flip();
		//SDL_RenderPresent(renderer);
	}

	void Clear(int r,int g,int b)
	{
		SDL_SetRenderDrawColor(renderer, r, g, b, 255);
		SDL_RenderClear(renderer);
		SDL_RenderPresent(renderer);
	}

	void Clear(int c)
	{
		int r = (c>>16)&0xFF;
		int g = (c >> 8) & 0xFF;
		int b = (c >> 0) & 0xFF;

		SDL_SetRenderDrawColor(renderer, r, g, b, 255);
		SDL_RenderClear(renderer);
		SDL_RenderPresent(renderer);
	}

	void Clear(RenderRect r2)
	{
		int r = (r2.dwFillColor >> 16) & 0xFF;
		int g = (r2.dwFillColor >> 8) & 0xFF;
		int b = (r2.dwFillColor >> 0) & 0xFF;

		SDL_Rect rect;
		rect.x = r2.left;
		rect.y = r2.top;
		rect.w = r2.right-r2.left;
		rect.h = r2.bottom-r2.top;


		SDL_SetRenderDrawColor(renderer, r, g, b, 255);
		SDL_RenderDrawRect(renderer, &rect);

	}
};