
#include <fstream.h>
#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include <stdlib.h>
#include "musicbank.h"
#include "fmod_errors.h"
#include "bendebug.h"
#include "config.h"

#define TYPE_MOD	0
#define TYPE_MP3	1

#define MAX_ZIK		10

MusicBank::MusicBank() : nb_musiques(0), type(NULL), playing(NULL),
	mp3(NULL), mod(NULL), channel(NULL) {
}

MusicBank::~MusicBank() {
	if (nb_musiques > 0) {
		debug << "MusicBank non desallouée\n";
		close();
	}
}

bool MusicBank::open(const char * file, bool loop) {
	if (!music_on)
		return true;

	char		buffer[200];
	ifstream	f;

	f.open(file, ios::in | ios::nocreate);

	if (f.is_open() == 0) {
		debug << "MusicBank::load() -> Impossible d'ouvrir le fichier " << file << "\n";
		return false;
	}

	f >> nb_musiques;

	if (nb_musiques < 1) {
		f.close();
		debug << "MusicBank::load() -> Fichier " << file << " corrompu (" << nb_musiques << ")\n";
		return false;
	}

	type = new int[nb_musiques];
	playing = new bool [nb_musiques];
//	mp3 = new FSOUND_SAMPLE * [nb_musiques];
	mp3 = new FSOUND_STREAM * [nb_musiques];
	mod = new FMUSIC_MODULE * [nb_musiques];
	channel = new int [nb_musiques];
	mp3Data = new void * [nb_musiques];


	for (int i = 0; i < nb_musiques; i++) {
		f >> type[i];
		f >> buffer;

		if (type[i] == TYPE_MOD) {
			if ((mod[i] = FMUSIC_LoadSong(buffer)) == 0) {
				f.close();
				debug << "MusicBank::load() -> Ne peut pas charger le MOD " << buffer << "\n";
				nb_musiques = i;
				close();
				return false;
			}
		} else { // TYPE_MP3
			mp3Data[i] = NULL;

			FILE * f2 = fopen(buffer, "rb");

			if (f2 == NULL) {
				f.close();
				debug << "MusicBank::load() -> Ne peut pas charger le MP3 " << buffer << "\n";
				nb_musiques = i;
				close();
				return false;
			}

			fseek(f2, 0, SEEK_END);
			int size = ftell(f2);
			fseek(f2, 0, SEEK_SET);

			mp3Data[i] = malloc(size);

			fread(mp3Data[i], size, 1, f2);

			fflush(f2);
			fclose(f2);

			if (loop) {
//				mp3[i] = FSOUND_Sample_Load( FSOUND_FREE, (char*)mp3Data[i], FSOUND_LOADMEMORY | FSOUND_LOOP_NORMAL, size);
				mp3[i] = FSOUND_Stream_OpenFile((char*)mp3Data[i], FSOUND_LOADMEMORY | FSOUND_LOOP_NORMAL, size);
			} else {
//				mp3[i] = FSOUND_Sample_Load( FSOUND_FREE, (char*)mp3Data[i], FSOUND_LOADMEMORY | FSOUND_LOOP_OFF, size);
				mp3[i] = FSOUND_Stream_OpenFile((char*)mp3Data[i], FSOUND_LOADMEMORY | FSOUND_LOOP_OFF, size);
			}

			if (mp3[i] == NULL) {
				debug << "Cannot stream " << buffer << " FMOD Error :" << FMOD_ErrorString(FSOUND_GetError()) << "\n";
			}

			/*
			if ( loop)
			{
				if ((mp3[i] = FSOUND_Sample_LoadMpeg( FSOUND_FREE, buffer, FSOUND_LOOP_NORMAL)) == 0)
				{
					f.close();
					debug<<"MusicBank::load() -> Ne peut pas charger le MP3 "<<buffer<<"\n";
					nb_musiques = i;
					close();
					return false;
				}
			}
			else
			{
				if ((mp3[i] = FSOUND_Sample_LoadMpeg( FSOUND_FREE, buffer, FSOUND_LOOP_OFF)) == 0)
				{
					f.close();
					debug<<"MusicBank::load() -> Ne peut pas charger le MP3 "<<buffer<<"\n";
					nb_musiques = i;
					close();
					return false;
				}
			}
			*/
		}

		playing[i] = false;
	}

	f.close();
	return true;
}

void MusicBank::close() {
	for (int i = 0; i < nb_musiques; i++) {
		if (type[i] == TYPE_MOD) {
			FMUSIC_FreeSong(mod[i]);
		} else {
//			FSOUND_Sample_Free( mp3[i]);
			FSOUND_Stream_Close(mp3[i]);
			if (mp3Data[i] != NULL)
				free(mp3Data[i]);
		}
	}

	nb_musiques = 0;

	if (type != NULL) {
		delete [] type;
		type = NULL;
	}

	if (mod != NULL) {
		delete [] mod;
		mod = NULL;
	}

	if (mp3 != NULL) {
		delete [] mp3;
		mp3 = NULL;
	}

	if (mp3Data != NULL) {
		delete [] mp3Data;
		mp3Data = NULL;
	}

	if (playing != NULL) {
		delete [] playing;
		playing = NULL;
	}

	if (channel != NULL) {
		delete [] channel;
		channel = NULL;
	}
}

void MusicBank::play(int n) {
	if (!music_on)
		return;

	if (n < 0 || n >= nb_musiques) {
		debug << "MusicBank::play() -> Tentative de jouer une musique non chargée : " << n << "\n";
		return;
	}

	if (type[n] == TYPE_MOD)
		FMUSIC_PlaySong(mod[n]);
	else {
//		channel[n] = FSOUND_PlaySound( 0, mp3[n]);
		channel[n] = FSOUND_Stream_Play(0, mp3[n]);
	}

	playing[n] = true;
}


void MusicBank::stop(int n) {
	if (!music_on)
		return;

	if (n < 0 || n >= nb_musiques) {
		debug << "MusicBank::stop() -> Tentative de stoper une musique non chargée : " << n << "\n";
		return;
	}

	if (!playing[n])
		return;

	if (type[n] == TYPE_MOD)
		FMUSIC_StopSong(mod[n]);
	else
//		FSOUND_StopSound( channel[n]);
		FSOUND_Stream_Stop(mp3[n]);

	playing[n] = false;
}

void MusicBank::stop() {
	for (int i = 0; i < nb_musiques; i++) {
		if (playing[i])
			stop(i);
	}
}

void MusicBank::setVol(int v) {
	if (!music_on)
		return;

	for (int i = 0; i < nb_musiques; i++) {
		if (type[i] == TYPE_MOD)
			FMUSIC_SetMasterVolume(mod[i], v);
	}
}