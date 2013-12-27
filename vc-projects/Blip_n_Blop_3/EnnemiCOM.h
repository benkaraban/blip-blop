
#ifndef _EnnemiCOM_
#define _EnnemiCOM_

#include "ennemi.h"

class EnnemiCOM : public Ennemi
{
public:
	EnnemiCOM();
	virtual void update();
	virtual void onAvance();
	virtual void onMeure();
};

#endif