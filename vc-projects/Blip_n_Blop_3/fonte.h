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

#pragma once

#include <vector>
#include <memory>

#include "picture.h"
#include "dd_gfx.h"

//-----------------------------------------------------------------------------
//		Définition de la classe Fonte
//-----------------------------------------------------------------------------

class /* Poele en */ Fonte
{
private:
        std::vector<std::unique_ptr<Picture>> pictab_;
	int			spc;		// Largeur d'un espace
	int			h;			// Hauteur d'un saut de ligne
	char *		nom_fic;
	int			flag_fic;

public:
	Fonte();


	//	Charge un ficher FNT
	//
	bool load(const char * f, int flags = DDSURF_BEST);


	// Affiche du texte normal
	//
	void print(SDL::Surface * surf, int x, int y, const char * txt);


	// Affiche texte justifié à droite
	//
	void printR(SDL::Surface * surf, int x, int y, const char * txt);


	// Affiche texte centré
	//
	void printC(SDL::Surface * surf, int xtaille, int y, const char * txt);


	// Affiche texte multiligne
	//
	void printM(SDL::Surface * surf, int x, int y, const char * txt, int ym);


	// Affiche texte multiligne sans couper les mots
	//
	void printMW(SDL::Surface * surf, int x, int y, const char * txt, int ym);


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
