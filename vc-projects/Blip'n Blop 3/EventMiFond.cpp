
#include "globals.h"
#include "eventmifond.h"
#include "fondstatique.h"

void EventMiFond::doEvent()
{
	Sprite * s = new FondStatique();

	s->x = x;
	s->y = y;
	s->pic = pbk_niveau[id];

	list_fonds_statiques.ajoute( (void*) s);
}