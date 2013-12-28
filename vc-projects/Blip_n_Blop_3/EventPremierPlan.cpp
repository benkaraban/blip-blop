/******************************************************************
*
*
*		------------------------
*		  EventPremierPlan.cpp
*		------------------------
*
*
*
*		Prosper / LOADED -   2 Aout 2000
*
*
*
******************************************************************/

#include "EventPremierPlan.h"
#include "Sprite.h"

class PPlan : public Sprite {
public:
	virtual void update() {
	};
};

void EventPremierPlan::doEvent() {
	PPlan * s = new PPlan();

	s->x = x;
	s->y = y;
	s->pic = pbk_niveau[id_fond];

	list_premiers_plans.ajoute((void*) s);

}
