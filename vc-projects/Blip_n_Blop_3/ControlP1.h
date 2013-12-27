/******************************************************************
*
*
*		----------------
*		  ControlP1.h
*		----------------
*
*		Classe ControlorP1
*
*		Sert d'intermédiaire entre Blip/Blop et le joueur 1
*
*
*		Prosper / LOADED -   V 0.1
*
*
*
******************************************************************/

#ifndef _ControlP1_
#define _ControlP1_

//-----------------------------------------------------------------------------
//		Headers
//-----------------------------------------------------------------------------

#include "Input.h"
#include "Controlor.h"
#include "ControlAlias.h"

//-----------------------------------------------------------------------------
//		Définition de la classe ControlP1
//-----------------------------------------------------------------------------

class ControlP1 : public Controlor {
protected:
public:
	virtual int gauche() const {
		return in.scanAlias(ALIAS_P1_LEFT);
	};

	virtual int haut() const {
		return in.scanAlias(ALIAS_P1_UP);
	};

	virtual int droite() const {
		return in.scanAlias(ALIAS_P1_RIGHT);
	};

	virtual int bas() const {
		return in.scanAlias(ALIAS_P1_DOWN);
	};

	virtual int fire() const {
		return in.scanAlias(ALIAS_P1_FIRE);
	};

	virtual int saut() const {
		return in.scanAlias(ALIAS_P1_JUMP);
	};

	virtual int super() const {
		return in.scanAlias(ALIAS_P1_SUPER);
	};
};


#endif

