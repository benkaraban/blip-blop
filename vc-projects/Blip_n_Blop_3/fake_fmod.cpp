#include "fmod.h"

#include <SDL2/SDL_mixer.h>

extern "C" {
struct FMUSIC_MODULE {};
struct FSOUND_STREAM {
    Mix_Music* music;
};
struct FSOUND_SAMPLE {
    Mix_Chunk* chunk;
    int loop;
};

typedef struct FMUSIC_MODULE FMUSIC_MODULE;
typedef struct FSOUND_STREAM FSOUND_STREAM;
typedef struct FSOUND_SAMPLE FSOUND_SAMPLE;

FSOUND_SAMPLE* FSOUND_Sample_Load(int index,
                                  const char* buffer,
                                  unsigned int mode,
                                  int memlength) {
    FSOUND_SAMPLE* sample = new FSOUND_SAMPLE;

    sample->loop = 0;
    sample->chunk = Mix_LoadWAV_RW(SDL_RWFromConstMem(buffer, memlength), 1);
    if (!sample->chunk) {
        printf("Mix_LoadWAV_RW: %s\n", Mix_GetError());
    }

    return sample;
}
int FSOUND_PlaySound(int channel, FSOUND_SAMPLE* sptr) {
    return Mix_PlayChannel(channel, sptr->chunk, sptr->loop);
}
signed char FSOUND_Sample_SetLoopMode(FSOUND_SAMPLE* sptr,
                                      unsigned int loopmode) {
    if (loopmode = FSOUND_LOOP_NORMAL) {
        sptr->loop = 0;
    } else {
        sptr->loop = 0;
    }
}

signed char FSOUND_StopSound(int channel) { Mix_HaltChannel(channel); }

void FSOUND_Sample_Free(FSOUND_SAMPLE* sptr) {
    Mix_FreeChunk(sptr->chunk);
    delete sptr;
}

FSOUND_STREAM* FSOUND_Stream_OpenFile(const char* filename,
                                      unsigned int mode,
                                      int memlength) {
    FSOUND_STREAM* stream = new FSOUND_STREAM;
    stream->music = Mix_LoadMUS(filename);
    if (!stream->music) {
        printf("Mix_LoadMUS(\"%s\"): %s\n", filename, Mix_GetError());
    }
    return stream;
}
int FSOUND_Stream_Play(int channel, FSOUND_STREAM* stream) {
    Mix_PlayMusic(stream->music, 0);
}
signed char FSOUND_Stream_Stop(FSOUND_STREAM* stream) { Mix_HaltMusic(); }
signed char FSOUND_Stream_Close(FSOUND_STREAM* stream) {
    Mix_FreeMusic(stream->music);
}

signed char FSOUND_Init(int mixrate,
                        int maxsoftwarechannels,
                        unsigned int flags) {
    int f = MIX_INIT_FLAC | MIX_INIT_MOD | MIX_INIT_MP3 | MIX_INIT_OGG;
    int initted = Mix_Init(f);
    if (initted & flags != flags) {
        printf("Mix_Init: Failed to init required ogg and mod support!\n");
        printf("Mix_Init: %s\n", Mix_GetError());
        return 0;
    }

    if (Mix_OpenAudio(mixrate, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
        printf("Mix_OpenAudio: %s\n", Mix_GetError());
        return 0;
    }
    return 1;
}
void FSOUND_Close() {
    Mix_CloseAudio();
    while (Mix_Init(0)) Mix_Quit();
}
int FSOUND_GetError() {}
signed char FMUSIC_PlaySong(FMUSIC_MODULE* mod) {}
FMUSIC_MODULE* FMUSIC_LoadSong(const char* name) {}
signed char FMUSIC_SetMasterVolume(FMUSIC_MODULE* mod, int volume) {}
signed char FMUSIC_StopSong(FMUSIC_MODULE* mod) {}
signed char FMUSIC_FreeSong(FMUSIC_MODULE* mod) {}
signed char FSOUND_SetPriority(int channel, int priority) {}
}
