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
#include <string.h>
#include <fstream>

#include "ben_debug.h"
#include "sound.h"
#include "sound_bank.h"

//-----------------------------------------------------------------------------
//		Méthodes
//-----------------------------------------------------------------------------

void SoundBank::reload() {
    if (!filename_.empty()) {
        loadSFX(filename_.c_str());
    }
}

bool SoundBank::loadSFX(const char* nom_fic) {
    int n_buff;  // Nombre de buffers
    int taille;  // Taille d'un WAV
    void* ptr;

    std::ifstream fh(nom_fic, std::ios::binary);

    if (!fh.good()) {
        debug << "SoundBank::loadSFX() -> Impossible d'ouvrir le fichier "
              << nom_fic << "\n";
        return false;
    }

    int nb_snd;
    fh.read(reinterpret_cast<char*>(&nb_snd), sizeof(nb_snd));

    if (nb_snd < 1) {
        debug << "SoundBank::loadSFX() -> Fichier " << nom_fic << " corrompu\n";
        return false;
    }
    tab_.resize(nb_snd);

    for (int i = 0; i < nb_snd; i++) {
        // Nombre de buffers
        fh.read(reinterpret_cast<char*>(&n_buff), sizeof(n_buff));
        fh.read(reinterpret_cast<char*>(&taille), sizeof(taille));  // Taille

        ptr = malloc(taille);

        if (ptr == NULL) {
            debug << "SoundBank::loadSFX() -> Pas assez de mémoire\n";
            return false;
        }

        // Copie le schnuf en mémoire
        //
        fh.read(reinterpret_cast<char*>(ptr), taille);

        tab_[i] = std::make_unique<Sound>();
        tab_[i]->loadFromMem(ptr, taille);

        free(ptr);
    }

    filename_ = nom_fic;

    return true;
}
