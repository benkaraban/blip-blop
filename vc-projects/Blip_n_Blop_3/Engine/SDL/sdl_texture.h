#include <SDL.h>

namespace SDL
{

public:

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