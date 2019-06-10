/******************************************************************
*
*
*		-----------------------
*		   GoreGiclure.h
*		-----------------------
*
*		Giclure de Luigi & Lara
*
*		Mephisto / LOADED -   V 0.1 - 01 Mars 2001
*
*
*
******************************************************************/


#ifndef _GoreGiclure_
#define _GoreGiclure_

//-----------------------------------------------------------------------------
//		Headers
//-----------------------------------------------------------------------------

#include "sprite.h"


//-----------------------------------------------------------------------------
//		Définition de la classe GoreGiclure
//-----------------------------------------------------------------------------

// FIXME: shouldn't it inherit Giclure?
class GoreGiclure : public Sprite
{
public:
	int		dx;

	GoreGiclure(int vx , int vy);

	virtual void update();

};

#endif
