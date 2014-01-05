#include <SDL.h>

namespace SDL
{

public:

	class Surface
	{
		private:
		SDL_Surface *surface;
		
		public:
		Surface();
		Surface(SDL_Surface*);
		
	};
	
}