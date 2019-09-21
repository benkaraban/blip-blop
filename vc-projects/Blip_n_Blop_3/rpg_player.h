/******************************************************************
*
*
*		-----------------
*		   RPGPlayer.h
*		-----------------
*
*
*
*		Prosper / LOADED -   V 0.1 - 17 Juillet 2000
*
*
*
******************************************************************/

#pragma once

#include <fstream>
#include <string>

#include "graphics.h"
#include "picture_bank.h"
#include "chrono.h"

#define	ID_JOUEUR	0
#define ID_ENNEMI	1

class RPGPlayer
{
public:
        std::ifstream fic_;
        std::string fic_name_;
        std::string buffer1_;
        std::string buffer2_;

	PictureBank *	pic_tab[2];
	int				nimage[2];
	int				ntxt[2];
	int				id[2];
	int				focus;

        Chrono time_;
        Countdown wait_;
	bool			key_released;
	bool			skiped;

	int				nbjoueurs;
	int				cur_joueur;	// Joueur pris en compte à cet instant (0 ou 1)
	int				base_joueur[2]; // Représente l'image de base du joueur selon qu'il soit Blip ou Blop

	RPGPlayer();

	void attachFile(const char * f);
	bool startPlay(int n);
	bool drawScene(SDL::Surface * surf);
	bool updateScene();
	void stopPlay();
	bool read();
	void error(const std::string& msg);
};
