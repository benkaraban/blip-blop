/******************************************************************
*
*
*		-------------------
*		  EventMeteo.h
*		-------------------
*
*		Classe Evenement Set Flag
*
*
*		Prosper / LOADED -   2 Aout 2000
*
*
*
******************************************************************/

#ifndef _EventMeteo_
#define _EventMeteo_

#include "Event.h"
#include "BenDebug.h"

class EventMeteo : public Event {
public:

	int		intensite;
	int		type;

	virtual void doEvent() {
		intensite_meteo = intensite;
		type_meteo = type;
	};
};

#endif
