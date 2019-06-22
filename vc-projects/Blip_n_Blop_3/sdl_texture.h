#pragma once
#include <SDL2/SDL.h>

namespace SDL
{

	class Texture
	{
		private:
		char filename[256];
		SDL_Texture *surface;
		
		public:
		Texture();
		Texture(SDL_Texture*);
		Texture(SDL_Texture*,char* fn);
		
	};
	
}
