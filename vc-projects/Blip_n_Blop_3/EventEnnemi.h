/******************************************************************
*
*
*		-----------------
*		  EventEnnemi.h
*		-----------------
*
*		Classe Evenement Ennemi
*
*		La classe evenement qui crée un ennemi
*
*
*		Prosper / LOADED -   2 Aout 2000
*
*
*
******************************************************************/

#ifndef _EventEnnemi_
#define _EventEnnemi_


#include "Event.h"
#include "Globals.h"


class EventEnnemi : public Event
{
public:
	int		x;
	int		y;
	int		id_ennemi;
	int		sens;


	virtual void doEvent();
};

#endif
