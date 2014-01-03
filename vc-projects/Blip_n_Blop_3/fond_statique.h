
#ifndef _FondStatique_
#define _FondStatique_

#include "Sprite.h"

class FondStatique : public Sprite
{
public:

	virtual void update()
	{
		if (x < 320)
			a_detruire = true;
	};
};

#endif
