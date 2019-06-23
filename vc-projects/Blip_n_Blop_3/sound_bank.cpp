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

#include "sound_bank.h"
#include <fcntl.h>
#include "Engine/io.h"
#include <malloc.h>
#include <string.h>
#include "ben_debug.h"
#include "sound.h"

//-----------------------------------------------------------------------------
//		Méthodes
//-----------------------------------------------------------------------------

void SoundBank::reload() {
    if (!filename_.empty()) {
        loadSFX(filename_.c_str());
    }
}

bool SoundBank::loadSFX(const char* nom_fic) {
    int fh;      // File Handle
    int n_buff;  // Nombre de buffers
    int taille;  // Taille d'un WAV
    void* ptr;

    fh = _open(nom_fic, _O_RDONLY | _O_BINARY);

    if (fh == -1) {
        debug << "SoundBank::loadSFX() -> Impossible d'ouvrir le fichier "
              << nom_fic << "\n";
        return false;
    }

    int nb_snd;
    _read(fh, &nb_snd, sizeof(nb_snd));

    if (nb_snd < 1) {
        debug << "SoundBank::loadSFX() -> Fichier " << nom_fic << " corrompu\n";
        _close(fh);
        return false;
    }
    tab_.resize(nb_snd);

    for (int i = 0; i < nb_snd; i++) {
        _read(fh, &n_buff, sizeof(n_buff));  // Nombre de buffers
        _read(fh, &taille, sizeof(taille));  // Taille

        ptr = malloc(taille);

        if (ptr == NULL) {
            debug << "SoundBank::loadSFX() -> Pas assez de mémoire\n";
            _close(fh);
            return false;
        }

        // Copie le schnuf en mémoire
        //
        _read(fh, ptr, taille);

        tab_[i] = std::make_unique<Sound>();
        tab_[i]->loadFromMem(ptr, taille);

        free(ptr);
    }

    _close(fh);

    filename_ = nom_fic;

    return true;
}
