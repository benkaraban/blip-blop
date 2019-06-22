/******************************************************************
 *
 *
 *		------------------
 *		  PictureBank.cpp
 *		------------------
 *
 *		Classe PictureBank
 *
 *		Représente un tableau/une banque d'images.
 *
 *
 *		Prosper / LOADED -   V 0.2 - 13 Juillet 2000
 *
 *
 *
 ******************************************************************/

#include "picture_bank.h"

#include <fstream>

#include <io.h>
#include <stdio.h>
#include <string.h>
#include "ben_debug.h"
#include "dd_gfx.h"
#include "lgx_packer.h"

PictureBank::PictureBank() : flag_fic(0) {}

bool PictureBank::loadGFX(const char* file, int flag, bool trans) {
    SDL::Surface* surf;
    int xspot;
    int yspot;
    int version;

    std::ifstream fic(file, std::ios::binary);
    if (!fic.good()) {
        debug << "PictureBank::loadGFX() - Impossible de charger le fichier "
              << file << "\n";
        return false;
    }

    int nb_pic;
    fic.read(reinterpret_cast<char*>(&nb_pic), sizeof(nb_pic));
    tab_.resize(nb_pic);

    for (int i = 0; i < nb_pic; i++) {
        int size;
        // Coordonnées du point chaud
        fic.read(reinterpret_cast<char*>(&xspot), sizeof(xspot));
        fic.read(reinterpret_cast<char*>(&yspot), sizeof(yspot));

        fic.read(reinterpret_cast<char*>(&size), sizeof(size));

        void* ptr;
        ptr = malloc(size);

        fic.read(static_cast<char*>(ptr), size);
        surf = LGXpaker.loadLGX(ptr, flag, &version);

        free(ptr);

        if (surf == NULL) {
            debug << "PictureBank::loadGFX() - surface à NULL\n";
            return false;
        }

        tab_[i] = std::make_unique<Picture>();

        tab_[i]->SetSpot(xspot, yspot);
        tab_[i]->SetSurface(surf);

        if (trans) {
            if (version == 1) {
                tab_[i]->SetColorKey(RGB(246, 205, 148));
            } else {
                tab_[i]->SetColorKey(RGB(246, 210, 148));
            }
        }
    }

    filename_ = file;
    flag_fic = flag;
    trans_fic = trans;
    return true;
}

bool PictureBank::restoreAll() {
    if (filename_.empty()) {
        return true;
    }
    SDL::Surface* surf;
    int fic;
    int xspot;
    int yspot;
    int taille;
    int version;
    void* ptr;

    fic = _open(filename_.c_str(), _O_BINARY | _O_RDONLY);
    if (fic == -1) {
        debug << "PictureBank::restoreAll() - Impossible de charger le "
                 "fichier "
              << filename_ << "\n";
        return false;
    }

    int nb_pic;
    _read(fic, &nb_pic, sizeof(nb_pic));

    for (int i = 0; i < nb_pic; i++) {
        // Libère l'ancienne surface
        //
        surf = tab_[i]->Surf();
        surf->Release();

        _read(fic, &xspot, sizeof(xspot));  // Coordonnées du point chaud
        _read(fic, &yspot, sizeof(yspot));

        _read(fic, &taille, sizeof(taille));

        ptr = malloc(taille);

        if (ptr == NULL) {
            debug << "PictureBank::restoreAll() - Impossible d'allouer "
                  << taille << " octets \n";
            _close(fic);
            return false;
        }

        _read(fic, ptr, taille);
        surf = LGXpaker.loadLGX(ptr, flag_fic, &version);

        free(ptr);

        if (surf == NULL) {
            debug << "PictureBank::restoreAll() - surface à NULL\n";
            _close(fic);
            return false;
        }

        tab_[i]->SetSpot(xspot, yspot);
        tab_[i]->SetSurface(surf);

        if (trans_fic) {
            if (version == 1)
                tab_[i]->SetColorKey(RGB(250, 206, 152));
            else
                tab_[i]->SetColorKey(RGB(250, 214, 152));
        }
    }

    _close(fic);

    return true;
}
