#include "music_bank.h"
#include <fcntl.h>
#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include "ben_debug.h"
#include "config.h"
#include "fmod__errors.h"

#define TYPE_MOD 0
#define TYPE_MP3 1

bool MusicBank::open(const char* file, bool loop) {
    if (!music_on) return true;

    std::ifstream f(file, std::ios::in);

    if (f.is_open() == 0) {
        debug << "MusicBank::load() -> Impossible d'ouvrir le fichier " << file
              << "\n";
        return false;
    }

    int nb_musics;
    f >> nb_musics;

    if (nb_musics < 1) {
        f.close();
        debug << "MusicBank::load() -> Fichier " << file << " corrompu ("
              << nb_musics << ")\n";
        return false;
    }

    musics_.resize(nb_musics);

    for (int i = 0; i < nb_musics; i++) {
        int type;
        f >> type;
        std::string fname;
        f >> fname;
        std::replace(fname.begin(), fname.end(), '\\', '/');

        if (type == TYPE_MOD) {
            musics_[i].reset(new ModMusic(fname));
        } else {  // TYPE_MP3
            musics_[i].reset(new Mp3Music(fname, loop));
        }
    }

    f.close();
    return true;
}

void MusicBank::play(int n) {
    if (!music_on) return;

    if (n < 0 || n >= musics_.size()) {
        debug << "MusicBank::play() -> Tentative de jouer une musique non "
                 "chargée : "
              << n << "\n";
        return;
    }

    musics_[n]->Play();
}

void MusicBank::stop(int n) {
    if (!music_on) return;

    if (n < 0 || n >= musics_.size()) {
        debug << "MusicBank::stop() -> Tentative de stoper une musique non "
                 "chargée : "
              << n << "\n";
        return;
    }

    musics_[n]->Stop();
}

void MusicBank::stop() {
    for (int i = 0; i < musics_.size(); i++) {
        stop(i);
    }
}

void MusicBank::setVol(int v) {
    if (!music_on) return;

    for (int i = 0; i < musics_.size(); i++) {
        musics_[i]->set_volume(v);
    }
}
