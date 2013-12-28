/******************************************************************
*
*
*		--------------------
*		  EventFondAnime.h
*		--------------------
*
*
*
*		Prosper / LOADED -   2 Aout 2000
*
*
*
******************************************************************/

#ifndef _EventFondAnime_
#define _EventFondAnime_


#include "Event.h"
#include "Globals.h"


class EventFondAnime : public Event {
public:
	int		x;
	int		y;
	int		id_fond;

	virtual void doEvent();
};

#endif
