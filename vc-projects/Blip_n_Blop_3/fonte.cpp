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

//-----------------------------------------------------------------------------
//		Headers
//-----------------------------------------------------------------------------

#include <ddraw.h>
#include <string.h>
#include <fstream>
#include <io.h>
#include <fcntl.h>
#include <stdio.h>
#include "lgx_packer.h"
#include "ben_debug.h"
#include "fonte.h"


//-----------------------------------------------------------------------------

Fonte::Fonte() : pictab(NULL), nom_fic(NULL)
{
}


//-----------------------------------------------------------------------------

Fonte::~Fonte()
{
	if (pictab != NULL)
		debug << "Fonte non fermée!\n";
}


//-----------------------------------------------------------------------------

bool Fonte::load(const char * fic, int flags)
{
	IDirectDrawSurface7 *	surf;

	int			taille;
	int			fh;
	void *		ptr;

	if (pictab != NULL) {
		debug << "Fonte::load->Objet déjà ouvert!\n";
		return false;
	}

	fh = _open(fic, _O_RDONLY | _O_BINARY);

	if (fh == -1) {
		debug << "Fonte::load->Ne peut pas ouvrir " << fic << "\n";
		return false;
	}

	pictab = new Picture * [256];
	if (pictab == NULL) {
		debug << "Fonte::load->Pas assez de mémoire pour " << fic << "\n";
		_close(fh);
		return false;
	}

	for (int i = 0; i < 256; i++)
		pictab[i] = NULL;

	_read(fh, &h, sizeof(h));
	_read(fh, &spc, sizeof(spc));


	for (int i = 1; i < 256; i++) {

		_read(fh, &taille, sizeof(taille));

		if (taille == 0) {
			continue;
		}

		ptr = malloc(taille);

		if (ptr == NULL) {
			debug << "Fonte::load() - Impossible d'allouer " << taille << " octets \n";
			_close(fh);
			for (int j = 0; j < i; j++)
				delete pictab[j];
			delete [] pictab;
			pictab = NULL;
			return false;
		}


		_read(fh, ptr, taille);

		surf = LGXpaker.loadLGX(ptr, flags);

		free(ptr);

		if (surf == NULL) {
			debug << "Pas assez de mémoire pour le " << i << " de " << fic << "\n";
			_close(fh);
			for (int j = 0; j < i; j++)
				delete pictab[j];
			delete [] pictab;
			pictab = NULL;
			return false;
		}

		pictab[i] = new Picture;
		pictab[i]->SetSurface(surf);
		pictab[i]->SetSpot(0, 0);
//		pictab[i]->SetColorKey( RGB( 250, 212, 152));
//		pictab[i]->SetColorKey(RGB( 246, 205, 148));
		pictab[i]->SetColorKey(RGB(250, 206, 152));
	}

	nom_fic = new char[strlen(fic) + 1];
	strcpy(nom_fic, fic);
	flag_fic = flags;
	_close(fh);
	return true;
}

//-----------------------------------------------------------------------------

void Fonte::print(IDirectDrawSurface7 * surf, int x, int y, const char * txt)
{
	if (txt == NULL)
		return;

	int		curx;	// X courant
	int		c;

	curx = x;

	for (unsigned int i = 0; i < strlen(txt); i++) {
		c = unsigned char(txt[i]);
		if (c == ' ') {
			curx += spc;
		} else if (pictab[c] != NULL) {
			pictab[c]->BlitTo(surf, curx, y);
			curx += pictab[c]->xSize();
		}
	}
}


//-----------------------------------------------------------------------------

void Fonte::printM(IDirectDrawSurface7 * surf, int x, int y, const char * txt, int ym)
{
	if (txt == NULL)
		return;

	int		curx;	// X courant
	int		cury;	// Y courant
	int		nx;		// Next x (pour ne pas le calculer 2 fois)
	unsigned int		c;

	curx = x;
	cury = y;


	for (unsigned int i = 0; i < strlen(txt); i++) {
		c = unsigned char(txt[i]);

		if (c == ' ') {
			curx += spc;
		} else if (pictab[c] != NULL) {
			// Calcul du X suivant
			nx = curx + pictab[c]->xSize();

			// Ligne suivante ?
			if (nx >= ym) {
				cury += h;
				pictab[c]->BlitTo(surf, x, cury);
				curx = x + pictab[c]->xSize();
			} else {	// Non, on continue..
				pictab[c]->BlitTo(surf, curx, cury);
				curx = nx;
			}
		}
	}
}


//-----------------------------------------------------------------------------

void Fonte::printR(IDirectDrawSurface7 * surf, int x, int y, const char * txt)
{
	if (txt == NULL)
		return;

	int		l = 0;	// Longueur en pixels de la chaîne
	int		c;

	for (unsigned int i = 0; i < strlen(txt); i++) {
		c = unsigned char(txt[i]);

		if (c == ' ')
			l += spc;
		else if (pictab[c] != NULL)
			l += pictab[c]->xSize();
	}

	print(surf, x - l, y, txt);
}


//-----------------------------------------------------------------------------

void Fonte::printC(IDirectDrawSurface7 * surf, int xtaille, int y, const char * txt)
{
	if (txt == NULL)
		return;

	int		l = 0;	// Longueur en pixels de la chaîne
	int		c;

	for (unsigned int i = 0; i < strlen(txt); i++) {
		c = unsigned char(txt[i]);

		if (c == ' ')
			l += spc;
		else if (pictab[c] != NULL)
			l += pictab[c]->xSize();
	}

	print(surf, xtaille - (l >> 1), y, txt);
}


//-----------------------------------------------------------------------------

void Fonte::close()
{
	if (pictab == NULL)
		return;

	// Ferme les PICs et détruit les trucs dynamiques...
	for (int i = 0; i < 256; i++) {
		if (pictab[i] != 0) {
			pictab[i]->Close();
			delete pictab[i];
			pictab[i] = NULL;
		}
	}

	if (pictab != NULL) {
		delete [] pictab;
		pictab = NULL;
	}

	if (nom_fic != NULL) {
		delete [] nom_fic;
		nom_fic = NULL;
	}
}



//-----------------------------------------------------------------------------

void Fonte::printMW(IDirectDrawSurface7 * surf, int x, int y, const char * srctxt, int ym)
{
	static const char delim [] = " ";

	if (srctxt == NULL)
		return;

	int		curx;	// X courant
	int		cury;	// Y courant
	int		nx;		// Next x (pour ne pas le calculer 2 fois)

	curx = x;
	cury = y;

	char * txt = new char[strlen(srctxt) + 1];
	char * token;

	strcpy(txt, srctxt);
	token = strtok(txt, delim);

	while (token != NULL) {
		nx = width(token);

		if (curx + nx > ym) {
			cury += h;
			print(surf, x, cury, token);
			curx = x + nx;
		} else {
			print(surf, curx, cury, token);
			curx += nx;
		}

		curx += spc;

		token = strtok(NULL, delim);
	}
}


//-----------------------------------------------------------------------------

int Fonte::width(const char * txt)
{
	if (txt == NULL)
		return 0;

	int		l = 0;	// Longueur en pixels de la chaîne
	int		c;

	for (unsigned int i = 0; i < strlen(txt); i++) {
		c = unsigned char(txt[i]);

		if (c == ' ')
			l += spc;
		else if (pictab[c] != NULL)
			l += pictab[c]->xSize();
	}

	return l;
}

//-----------------------------------------------------------------------------

bool Fonte::restoreAll()
{
	if (nom_fic == NULL)
		return true;

	IDirectDrawSurface7 *	surf;

	int			taille;
	int			fh;
	void *		ptr;


	fh = _open(nom_fic, _O_RDONLY | _O_BINARY);

	if (fh == -1) {
		debug << "Fonte::restoreAll()->Ne peut pas ouvrir " << nom_fic << "\n";
		return false;
	}


	_read(fh, &h, sizeof(h));
	_read(fh, &spc, sizeof(spc));


	for (int i = 1; i < 256; i++) {

		_read(fh, &taille, sizeof(taille));

		if (taille == 0) {
			continue;
		}

		ptr = malloc(taille);

		if (ptr == NULL) {
			debug << "Fonte::restoreAll() - Impossible d'allouer " << taille << " octets \n";
			_close(fh);
			for (int j = 0; j < i; j++)
				delete pictab[j];
			delete [] pictab;
			pictab = NULL;
			return false;
		}


		_read(fh, ptr, taille);

		surf = LGXpaker.loadLGX(ptr, flag_fic);

		free(ptr);

		if (surf == NULL) {
			debug << "Pas assez de mémoire pour le " << i << " de " << nom_fic << "\n";
			_close(fh);
			for (int j = 0; j < i; j++)
				delete pictab[j];
			delete [] pictab;
			pictab = NULL;
			return false;
		}

		pictab[i]->SetSurface(surf);
		pictab[i]->SetSpot(0, 0);
		pictab[i]->SetColorKey(RGB(250, 206, 152));
	}

	_close(fh);
	return true;
}