
#ifndef _Bulle_
#define _Bulle_

#include "Sprite.h"

class Bulle : public Sprite
{
public:
	int		xbase;
	int		phi;
	int		dphi;

	Bulle();
	virtual void update();
};

#endif
