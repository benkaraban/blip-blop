/******************************************************************
*
*
*		-------------------
*		  SoundBankBB.cpp
*		-------------------
*
*		Classe SoundBankBB
*
*		Cette classe est presque identique à la classe SoundBank.
*		Elle ne fait qu'ajouter le fait qu'on puisse avoir le son
*		on/off. (cf. config.h)
*
*
*		Prosper / LOADED -   V 0.1 - 16 Juillet 2000
*
*
*
******************************************************************/

#include <string.h>
#include "sound_bank_bb.h"
#include "config.h"
#include "ben_debug.h"

void SoundBankBB::play(int n, int flags)
{
	if (!sound_on)
		return;

	if (n >= tab_.size()) {
		debug << "Tentative de jouer son " << n << "\n";
		return;
	}

	tab_[n]->play(flags);
}


void SoundBankBB::setVolume(int n, int vol)
{
	if (!sound_on)
		return;

	tab_[n]->setVolume(vol);
}


void SoundBankBB::stop(int n)
{
	if (!sound_on)
		return;

	tab_[n]->stop();
}


bool SoundBankBB::loadSFX(const char * nom_fic)
{
	if (!sound_on) {
		filename_ = nom_fic;
		return true;
	}

	return SoundBank::loadSFX(nom_fic);
}
