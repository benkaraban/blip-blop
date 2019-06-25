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

#include <fstream>

#include "graphics.h"
#include <string.h>
#include <fstream>
#include <fcntl.h>
#include <stdio.h>

#include "lgx_packer.h"
#include "ben_debug.h"
#include "fonte.h"


//-----------------------------------------------------------------------------

Fonte::Fonte() : nom_fic(NULL)
{
}



//-----------------------------------------------------------------------------

bool Fonte::load(const char * fic, int flags)
{
	if (!pictab_.empty()) {
		debug << "Fonte::load->Objet déjà ouvert!\n";
		return false;
	}

        std::ifstream fh(fic, std::ios::binary);

	if (!fh.good()) {
		debug << "Fonte::load->Ne peut pas ouvrir " << fic << "\n";
		return false;
	}

        fh.read(reinterpret_cast<char*>(&h), sizeof(h));
        fh.read(reinterpret_cast<char*>(&spc), sizeof(spc));


        pictab_.resize(256);
        for (int i = 1; i < 256; i++) {
            int taille;
            fh.read(reinterpret_cast<char*>(&taille), sizeof(taille));

            if (taille == 0) {
                continue;
            }

            void* ptr = malloc(taille);

            fh.read(reinterpret_cast<char*>(ptr), taille);

            SDL::Surface* surf = LGXpaker.loadLGX(ptr, flags);

            free(ptr);

            pictab_[i] = std::make_unique<Picture>();
            pictab_[i]->SetSurface(surf);
            pictab_[i]->SetSpot(0, 0);
            //		pictab[i]->SetColorKey( RGB( 250, 212, 152));
            pictab_[i]->SetColorKey(RGB( 246, 205, 148));
            //pictab[i]->SetColorKey(RGB(250, 206, 152));

            /*static int test_i = 1;
              char buf[128];
              sprintf(buf, "test/%d.bmp", test_i);
              SDL_SaveBMP(surf->Get(), buf);
              test_i++;*/

        }

	nom_fic = new char[strlen(fic) + 1];
	strcpy(nom_fic, fic);
	flag_fic = flags;
	return true;
}

//-----------------------------------------------------------------------------

void Fonte::print(SDL::Surface * surf, int x, int y, const char * txt)
{
	if (txt == NULL)
		return;

	int		curx;	// X courant
	int		c;

	curx = x;

	for (unsigned int i = 0; i < strlen(txt); i++) {
		c = (unsigned char) txt[i];
		if (c == ' ') {
			curx += spc;
		} else if (pictab_[c] != NULL) {
			pictab_[c]->BlitTo(surf, curx, y);
			curx += pictab_[c]->xSize();
		}
	}
}


//-----------------------------------------------------------------------------

void Fonte::printM(SDL::Surface * surf, int x, int y, const char * txt, int ym)
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
		c = (unsigned char) txt[i];

		if (c == ' ') {
			curx += spc;
		} else if (pictab_[c] != NULL) {
			// Calcul du X suivant
			nx = curx + pictab_[c]->xSize();

			// Ligne suivante ?
			if (nx >= ym) {
				cury += h;
				pictab_[c]->BlitTo(surf, x, cury);
				curx = x + pictab_[c]->xSize();
			} else {	// Non, on continue..
				pictab_[c]->BlitTo(surf, curx, cury);
				curx = nx;
			}
		}
	}
}


//-----------------------------------------------------------------------------

void Fonte::printR(SDL::Surface * surf, int x, int y, const char * txt)
{
	if (txt == NULL)
		return;

	int		l = 0;	// Longueur en pixels de la chaîne
	int		c;

	for (unsigned int i = 0; i < strlen(txt); i++) {
		c = (unsigned char) txt[i];

		if (c == ' ')
			l += spc;
		else if (pictab_[c] != NULL)
			l += pictab_[c]->xSize();
	}

	print(surf, x - l, y, txt);
}


//-----------------------------------------------------------------------------

void Fonte::printC(SDL::Surface * surf, int xtaille, int y, const char * txt)
{
	if (txt == NULL)
		return;

	int		l = 0;	// Longueur en pixels de la chaîne
	int		c;

	for (unsigned int i = 0; i < strlen(txt); i++) {
		c = (unsigned char) txt[i];

		if (c == ' ')
			l += spc;
		else if (pictab_[c] != NULL)
			l += pictab_[c]->xSize();
	}

	print(surf, xtaille - (l >> 1), y, txt);
}


//-----------------------------------------------------------------------------

void Fonte::close()
{
	if (nom_fic != NULL) {
		delete [] nom_fic;
		nom_fic = NULL;
	}
}



//-----------------------------------------------------------------------------

void Fonte::printMW(SDL::Surface * surf, int x, int y, const char * srctxt, int ym)
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
		c = (unsigned char) txt[i];

		if (c == ' ')
			l += spc;
		else if (pictab_[c] != NULL)
			l += pictab_[c]->xSize();
	}

	return l;
}

//-----------------------------------------------------------------------------

bool Fonte::restoreAll()
{
	if (nom_fic == NULL)
		return true;

	SDL::Surface *	surf;

	int			taille;
	void *		ptr;


        std::fstream fh(nom_fic, std::ios::binary);

	if (!fh.good()) {
		debug << "Fonte::restoreAll()->Ne peut pas ouvrir " << nom_fic << "\n";
		return false;
	}


        fh.read(reinterpret_cast<char*>(&h), sizeof(h));
        fh.read(reinterpret_cast<char*>(&spc), sizeof(spc));


	for (int i = 1; i < 256; i++) {

                fh.read(reinterpret_cast<char*>(&taille), sizeof(taille));

		if (taille == 0) {
			continue;
		}

		ptr = malloc(taille);

                fh.read(reinterpret_cast<char*>(ptr), taille);

		surf = LGXpaker.loadLGX(ptr, flag_fic);

		free(ptr);

		pictab_[i]->SetSurface(surf);
		pictab_[i]->SetSpot(0, 0);
		pictab_[i]->SetColorKey(RGB(250, 206, 152));
	}

	return true;
}
