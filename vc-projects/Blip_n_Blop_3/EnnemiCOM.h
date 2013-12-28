
#ifndef _EnnemiCOM_
#define _EnnemiCOM_

#include "Ennemi.h"

class EnnemiCOM : public Ennemi {
public:
	EnnemiCOM();
	virtual void update();
	virtual void onAvance();
	virtual void onMeure();
};

#endif
