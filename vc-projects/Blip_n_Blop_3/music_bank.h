#pragma once

#include <memory>
#include <vector>

#include "ben_debug.h"
#include "fmod.h"

#define CHANNEL_NUMBER 32

class Music {
   public:
    virtual ~Music() {}
    virtual void Play() const = 0;
    virtual void Stop() const = 0;
    virtual void set_volume(int v) = 0;
};

// TODO: ModMusic appears to be unused. Make sure it can safely be removed to
// simplify the code.
class ModMusic : public Music {
   public:
    ModMusic(const std::string& path) {
        if ((mod_ = FMUSIC_LoadSong(path.c_str())) == 0) {
            debug << "ModMusic(\"" << path << "\") failed\n";
            throw std::runtime_error("ModMusic failed loading");
        }
    }

    ~ModMusic() override { FMUSIC_FreeSong(mod_); }
    void Play() const override { FMUSIC_PlaySong(mod_); }
    void Stop() const override { FMUSIC_StopSong(mod_); }
    void set_volume(int v) override { FMUSIC_SetMasterVolume(mod_, v); }

   private:
    FMUSIC_MODULE* mod_;
};

class Mp3Music : public Music {
   public:
    Mp3Music(const std::string& fname, bool loop = true) {
        int loopflag = loop ? FSOUND_LOOP_NORMAL : FSOUND_LOOP_OFF;
        mp3_ = FSOUND_Stream_OpenFile(
            fname.c_str(), FSOUND_LOOP_NORMAL | loopflag, 0);
        if (!mp3_) {
            debug << "Mp3Music(\"" << fname << "\") failed\n";
            throw std::runtime_error("Mp3Music failed loading");
        }
    }

    ~Mp3Music() override { FSOUND_Stream_Close(mp3_); }
    void Play() const override { FSOUND_Stream_Play(0, mp3_); }
    void Stop() const override { FSOUND_Stream_Stop(mp3_); }
    void set_volume(int) override {
        debug << "Mp3Music::set_volume is a noop\n";
    }

   private:
    FSOUND_STREAM* mp3_;
};

class MusicBank {
   protected:
    std::vector<std::unique_ptr<Music>> musics_;

   public:
    void setVol(int v);
    bool open(const char* file, bool loop = true);
    void play(int n);
    void stop(int n);
    void stop();  // Stoppe TOUTES les musiques
};
