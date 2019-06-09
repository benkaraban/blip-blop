
#include <fstream>
#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include <stdlib.h>
#include "music_bank.h"
#include "fmod__errors.h"
#include "ben_debug.h"
#include "config.h"

#define TYPE_MOD	0
#define TYPE_MP3	1

#define MAX_ZIK		10

MusicBank::MusicBank() : nb_musiques(0)
{
}

MusicBank::~MusicBank()
{
	if (nb_musiques > 0) {
		debug << "MusicBank non desallouée\n";
		close();
	}
}

bool MusicBank::open(const char * file, bool loop)
{
	if (!music_on)
		return true;

	char		buffer[200];
	ifstream	f;

	f.open(file, ios::in);

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

	type_.resize(nb_musiques);
	playing_.resize(nb_musiques);
//	mp3 = new FSOUND_SAMPLE * [nb_musiques];
	mp3_.resize(nb_musiques);
	mod_.resize(nb_musiques);
	channel_.resize(nb_musiques);
	mp3Data_.resize(nb_musiques);


	for (int i = 0; i < nb_musiques; i++) {
		f >> type_[i];
		f >> buffer;

		if (type_[i] == TYPE_MOD) {
			if ((mod_[i] = FMUSIC_LoadSong(buffer)) == 0) {
				f.close();
				debug << "MusicBank::load() -> Ne peut pas charger le MOD " << buffer << "\n";
				nb_musiques = i;
				close();
				return false;
			}
		} else { // TYPE_MP3
			mp3Data_[i] = NULL;

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

			mp3Data_[i] = malloc(size);

			fread(mp3Data_[i], size, 1, f2);

			fflush(f2);
			fclose(f2);

			if (loop) {
				//mp3[i] = FSOUND_Sample_Load( FSOUND_FREE, (char*)mp3Data[i], FSOUND_LOADMEMORY | FSOUND_LOOP_NORMAL, size);
#ifdef _WIN32
				mp3_[i] = FSOUND_Stream_OpenFile((char*)mp3Data_[i], FSOUND_LOADMEMORY | FSOUND_LOOP_NORMAL, size);
#else
				mp3_[i] = FSOUND_Stream_OpenFile(buffer, FSOUND_LOADMEMORY | FSOUND_LOOP_NORMAL, size);
#endif
			} else {
				//mp3[i] = FSOUND_Sample_Load( FSOUND_FREE, (char*)mp3Data[i], FSOUND_LOADMEMORY | FSOUND_LOOP_OFF, size);
#ifdef _WIN32
				mp3_[i] = FSOUND_Stream_OpenFile((char*)mp3Data_[i], FSOUND_LOADMEMORY | FSOUND_LOOP_OFF, size);
#else
				mp3_[i] = FSOUND_Stream_OpenFile(buffer, FSOUND_LOADMEMORY | FSOUND_LOOP_OFF, size);
#endif
			}

			if (mp3_[i] == NULL) {
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

		playing_[i] = false;
	}

	f.close();
	return true;
}

void MusicBank::close()
{
	for (int i = 0; i < nb_musiques; i++) {
		if (type_[i] == TYPE_MOD) {
			FMUSIC_FreeSong(mod_[i]);
		} else {
			//FSOUND_Sample_Free(mp3[i]);
			FSOUND_Stream_Close(mp3_[i]);
			if (mp3Data_[i] != NULL)
				free(mp3Data_[i]);
		}
	}

	nb_musiques = 0;
        type_.clear();
        mp3_.clear();
        mod_.clear();
        mp3Data_.clear();
        playing_.clear();
        channel_.clear();
}

void MusicBank::play(int n)
{
	if (!music_on)
		return;

	if (n < 0 || n >= nb_musiques) {
		debug << "MusicBank::play() -> Tentative de jouer une musique non chargée : " << n << "\n";
		return;
	}

	if (type_[n] == TYPE_MOD)
		FMUSIC_PlaySong(mod_[n]);
	else {
//		channel_[n] = FSOUND_PlaySound( 0, mp3[n]);
		channel_[n] = FSOUND_Stream_Play(0, mp3_[n]);
	}

	playing_[n] = true;
}


void MusicBank::stop(int n)
{
	if (!music_on)
		return;

	if (n < 0 || n >= nb_musiques) {
		debug << "MusicBank::stop() -> Tentative de stoper une musique non chargée : " << n << "\n";
		return;
	}

	if (!playing_[n])
		return;

	if (type_[n] == TYPE_MOD)
		FMUSIC_StopSong(mod_[n]);
	else
//		FSOUND_StopSound( channel_[n]);
		FSOUND_Stream_Stop(mp3_[n]);

	playing_[n] = false;
}

void MusicBank::stop()
{
	for (int i = 0; i < nb_musiques; i++) {
		if (playing_[i])
			stop(i);
	}
}

void MusicBank::setVol(int v)
{
	if (!music_on)
		return;

	for (int i = 0; i < nb_musiques; i++) {
		if (type_[i] == TYPE_MOD)
			FMUSIC_SetMasterVolume(mod_[i], v);
	}
}
