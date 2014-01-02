/******************************************************************
*
*
*		----------------
*		  Fonte.h
*		----------------
*
*		Classe Fonte
*
*		Affiche du joli texte
*
*
*		Prosper / LOADED -   V 0.2
*
*
*
******************************************************************/

#ifndef _Fonte_
#define _Fonte_

//-----------------------------------------------------------------------------
//		Headers
//-----------------------------------------------------------------------------

#include "Picture.h"
#include "DD_gfx.h"

//-----------------------------------------------------------------------------
//		Définition de la classe Fonte
//-----------------------------------------------------------------------------

class Fonte
{
private:
	Picture **	pictab;		// Tableau de Picture
	int			spc;		// Largeur d'un espace
	int			h;			// Hauteur d'un saut de ligne
	char *		nom_fic;
	int			flag_fic;

public:
	Fonte();
	~Fonte();


	//	Charge un ficher FNT
	//
	bool load(const char * f, int flags = DDSURF_BEST);


	// Affiche du texte normal
	//
	void print(IDirectDrawSurface7 * surf, int x, int y, const char * txt);


	// Affiche texte justifié à droite
	//
	void printR(IDirectDrawSurface7 * surf, int x, int y, const char * txt);


	// Affiche texte centré
	//
	void printC(IDirectDrawSurface7 * surf, int xtaille, int y, const char * txt);


	// Affiche texte multiligne
	//
	void printM(IDirectDrawSurface7 * surf, int x, int y, const char * txt, int ym);


	// Affiche texte multiligne sans couper les mots
	//
	void printMW(IDirectDrawSurface7 * surf, int x, int y, const char * txt, int ym);


	// Renvoie la longueur en pixels d'un texte donné
	//
	int width(const char * txt);


	// What's the fuck up ?
	//
	bool restoreAll();

	// Ferme le tout
	//
	void close();
};

#endif
