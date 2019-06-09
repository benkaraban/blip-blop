#pragma once

#include <vector>

#include "fmod.h"

#define CHANNEL_NUMBER 32

class MusicBank {
   protected:
    std::vector<int> type_;

    //	FSOUND_SAMPLE **	mp3;
    std::vector<FSOUND_STREAM*> mp3_;

    std::vector<FMUSIC_MODULE*> mod_;
    std::vector<void*> mp3Data_;

    std::vector<bool> playing_;
    std::vector<int> channel_;

    int nb_musiques;

   public:
    MusicBank();
    ~MusicBank();

    void setVol(int v);
    bool open(const char* file, bool loop = true);
    void close();
    void play(int n);
    void stop(int n);
    void stop();  // Stoppe TOUTES les musiques
};
