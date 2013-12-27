
#ifndef _MusicBank_
#define _MusicBank_

#define	CHANNEL_NUMBER	32

#include "fmod.h"

class MusicBank {
protected:
	int	*		type;

//	FSOUND_SAMPLE **	mp3;
	FSOUND_STREAM **	mp3;

	FMUSIC_MODULE **	mod;
	void **				mp3Data;

	bool *		playing;
	int *		channel;

	int			nb_musiques;

public:

	MusicBank();
	~MusicBank();

	void setVol(int v);
	bool open(const char * file, bool loop = true);
	void close();
	void play(int n);
	void stop(int n);
	void stop(); // Stoppe TOUTES les musiques
};

#endif