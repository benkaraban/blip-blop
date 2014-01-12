#pragma once
#include <SDL.h>

namespace SDL
{

	class Surface
	{
		private:
		SDL_Surface *surface;
		
		public:
		Surface();
		Surface(SDL_Surface*);
		
		inline SDL_Surface *Get(){ return surface; };
		inline void BltFast(int x, int y, SDL::Surface *surf, RECT *r, int flags=0)
		{
			SDL_Rect rect,position;
			position.x = x;
			position.y = y;
			if (r == 0)
			{
				SDL_BlitSurface(surf->Get(), 0, surface, &position);
			}
			else
			{
				rect.x = r->left;
				rect.y = r->top;
				rect.w = r->right - r->left;
				rect.h = r->bottom - r->top;
				/*SDL_BlitSurface(SDL_Surface*    src,
				const SDL_Rect* srcrect,
				SDL_Surface*    dst,
				SDL_Rect*       dstrect)*/
				SDL_BlitSurface(surf->Get(), &rect, surface, &position);
			}
			
		}

		inline void Blt(RECT *src, SDL::Surface *surf, RECT *dest, int flags = 0, void *pad = 0 )
		{
			/*
			TODO: IF flags contains DDBLT_COLORFILL then i must fill the surface with the color of 
			*/
			SDL_Rect *rect=0, *position=0;
			if (src)
			{
				rect = new SDL_Rect;
				rect->x = src->left;
				rect->y = src->top;
				rect->w = src->right - src->left;
				rect->h = src->bottom - src->top;
			}
			if (dest)
			{
				position = new SDL_Rect;
				position->x = dest->left;
				position->y = dest->top;
				position->w = dest->right - dest->left;
				position->h = dest->bottom - dest->top;
			}
			if (surf)
			{
				SDL_BlitSurface(surf->Get(), rect, surface, position);
			}
			else
			{
				SDL_BlitSurface(0, rect, surface, position);
			}
			
			/*if (src!=0&&dest!=0)
			{
				SDL_Rect rect, position;
				rect.x = src->left;
				rect.y = src->top;
				rect.w = src->right - src->left;
				rect.h = src->bottom - src->top;
				position.x = dest->left;
				position.y = dest->top;
				position.w = dest->right - dest->left;
				position.h = dest->bottom - dest->top;
				SDL_BlitSurface(surface, &rect, surf->Get(), &position);
			}
			else if (src!=0)
			{
				SDL_Rect rect, position;
				position.x = dest->left;
				position.y = dest->top;
				position.w = dest->right - dest->left;
				position.h = dest->bottom - dest->top;
				SDL_BlitSurface(surface, 0, surf->Get(), &position);
			}
			else if (dest != 0)
			{
				SDL_Rect rect, position;
				rect.x = src->left;
				rect.y = src->top;
				rect.w = src->right - src->left;
				rect.h = src->bottom - src->top;
				SDL_BlitSurface(surf->Get(), &rect, surface, 0);
			}
			else
			{
				SDL_BlitSurface(surf->Get(), 0, surface, 0);
			}*/
		}

		inline void Blt(RECT *src, SDL::Surface *surf, RECT *dest, void *pad = 0, int flags = 0)
		{
			//Call the original function with the last 2 arguments swapped
			Blt(src, surf, dest, flags,pad);
		}

		inline void Release()
		{
			delete surface;
			delete this;
		}
		inline bool Restore()
		{
			return true;
		}

		inline void FillRect(RECT *r,unsigned int color)
		{
			if (!r)
			{
				SDL_FillRect(surface, 0, color);
			}
			else
			{
				SDL_Rect rect;
				rect.x = r->left;
				rect.y = r->top;
				rect.w = r->right - r->left;
				rect.h = r->bottom - r->top;
				SDL_FillRect(surface, &rect, color);
			}
			
		}
	};
	
};