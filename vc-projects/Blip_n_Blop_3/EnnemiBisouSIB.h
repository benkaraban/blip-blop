
#ifndef _EnnemiBisouSIB_
#define _EnnemiBisouSIB_

#include "ennemi.h"

class EnnemiBisouSIB : public Ennemi
{
public:

	int		encaisse;

	EnnemiBisouSIB();

	virtual void update();
	virtual void estTouche( Tir * tir);
};

#endif