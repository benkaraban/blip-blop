
#include "vehicule.h"

Vehicule::Vehicule() : joueur(NULL), ctrl(NULL), can_be_used(true)
{
}


void Vehicule::update()
{
	if (joueur == NULL) {
		if (can_be_used)
			joueur = scanne();

		if (joueur != NULL) {
			joueur->lockVehicule(canFire(), canChangeDir());
			ctrl = joueur->ctrl;
		} else {
			updateNotUsed();
			updateADetruire();
		}
	} else {
		if (joueur->etat != ETAT_LOCKEDV || joueur->a_detruire) {
			joueur = NULL;
			updateNotUsed();
			return;
		}

		updateUsed();
	}
}


Couille * Vehicule::scanne()
{
	Couille *	c;
	int			ddx;
	int			ddy;

        for (Couille* c: list_joueurs) {
		ddx = c->x - x;
		ddy = c->y - y;

		if (ddx > -20 && ddx < 20 && ddy > -20 && ddy < 20
		        && c->etat != ETAT_MEURE && c->etat != ETAT_COME_BACK
		        && !c->a_detruire && c->etat != ETAT_LOCKEDV)
			return c;
	}

//	debug<<"nothing!\n";
	return NULL;
}
