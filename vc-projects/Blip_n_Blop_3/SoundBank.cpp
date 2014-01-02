/******************************************************************
*
*
*		------------------
*		  SoundBank.cpp
*		------------------
*
*		Classe SoundBank
*
*		Représente un tableau/une banque de sons (Sound).
*
*
*		Prosper / LOADED -   V 0.1 - 16 Juillet 2000
*
*
*
******************************************************************/

//-----------------------------------------------------------------------------
//		Headers
//-----------------------------------------------------------------------------

#include <malloc.h>
#include <io.h>
#include <fcntl.h>
#include <string.h>
#include "bendebug.h"
#include "soundbank.h"
#include "sound.h"

//-----------------------------------------------------------------------------
//		Méthodes
//-----------------------------------------------------------------------------

SoundBank::SoundBank() : tab(NULL), nb_snd(0), nom_f(NULL)
{
}


SoundBank::~SoundBank()
{
	if (nom_f != NULL) {
		delete [] nom_f;
		nom_f = NULL;
	}

	if (tab != NULL)
		debug << "SoundBank non desallouée\n";
}



void SoundBank::close()
{
	if (tab == NULL)
		return;

	for (int i = 0; i < nb_snd; i++) {
		delete tab[i];
	}

	delete [] tab;
	tab = NULL;
	nb_snd = 0;
}


void SoundBank::reload()
{
	if (nom_f != NULL) {
		loadSFX(nom_f);
	}
}

void SoundBank::reinit()
{
	if (nom_f != NULL) {
		delete [] nom_f;
		nom_f = NULL;
	}
}


bool SoundBank::loadSFX(const char * nom_fic)
{
	int		fh;		// File Handle
	int		n_buff;	// Nombre de buffers
	int		taille;	// Taille d'un WAV
	void *	ptr;

	if (tab != NULL) {
		debug << "SoundBank::loadSFX() -> SoundBank déjà ouverte!\n";
		return false;
	}

	fh = _open(nom_fic, _O_RDONLY | _O_BINARY);

	if (fh == -1) {
		debug << "SoundBank::loadSFX() -> Impossible d'ouvrir le fichier " << nom_fic << "\n";
		return false;
	}

	_read(fh, &nb_snd, sizeof(nb_snd));

	if (nb_snd < 1) {
		debug << "SoundBank::loadSFX() -> Fichier " << nom_fic << " corrompu\n";
		_close(fh);
		return false;
	}


	tab = new Sound * [nb_snd];


	for (int i = 0; i < nb_snd; i++) {
		_read(fh, &n_buff, sizeof(n_buff));	// Nombre de buffers
		_read(fh, &taille, sizeof(taille));	// Taille


		ptr = malloc(taille);

		if (ptr == NULL) {
			debug << "SoundBank::loadSFX() -> Pas assez de mémoire\n";
			_close(fh);
			return false;
		}

		// Copie le schnuf en mémoire
		//
		_read(fh, ptr, taille);

		tab[i] = new Sound;
		tab[i]->loadFromMem(ptr, taille);


		free(ptr);
	}

	_close(fh);

	if (nom_f != NULL)
		delete [] nom_f;

	nom_f = new char[strlen(nom_fic) + 1];
	strcpy(nom_f, nom_fic);

	return true;
}