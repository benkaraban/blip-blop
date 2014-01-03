/******************************************************************
*
*
*		----------------------
*		  EventGenEnnemi.cpp
*		----------------------
*
*		Classe Evenement Ennemi
*
*		La classe evenement qui crée un ennemi
*
*
*		Prosper / LOADED -   5 Aout 2000
*
*
*
******************************************************************/

#include "EventGenennemi.h"
#include "gen_ennemi_tmp.h"
#include "Genennemi.h"

void EventGenEnnemi::doEvent()
{
	GenEnnemi *	gen;

	if (tmp)
		gen = new GenEnnemiTMP();
	else
		gen = new GenEnnemi();

	gen->id_ennemi = id_ennemi;
	gen->x = x;
	gen->y = y;
	gen->sens = sens;
	gen->periode = periode;
	gen->capacite = capacite;

	list_gen_ennemis.ajoute((void*) gen);
}
