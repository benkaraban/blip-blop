/******************************************************************
*
*
*		----------------
*		   Game.h
*		----------------
*
*		Classe Game
*
*		La classe représentant une partie
*
*
*		Prosper / LOADED -   V 0.2
*
*
*
******************************************************************/

#ifndef _Game_
#define _Game_

//-----------------------------------------------------------------------------
//		Headers
//-----------------------------------------------------------------------------

#include "graphics.h"
#include "dd_gfx.h"
#include "picture.h"
#include "rpg_player.h"
#include "blip.h"
#include "chrono.h"
#include "moving_average.h"

#include "meteo_neige.h"
#include "meteo_pluie.h"

#define	NB_GOUTTES	500
#define NB_FLOCONS	500

#define MAX_PART	50

#define PART_CINE		0
#define PART_LEVEL		1
#define PART_BRIEFING	2

#define LVL_BONUS		0
#define LVL_FIRST		1
#define LVL_INTER		2
#define LVL_LAST		3
#define LVL_COMPLETE	4
#define LVL_END			5



//-----------------------------------------------------------------------------
//		Définition de la classe Game
//-----------------------------------------------------------------------------

class Game
{
protected:
        MovingAverage<int> frame_spare_time_;
	PictureBank	pbk_briefing;
	bool	briefing;

	int		nb_part;
	char	fic_names[MAX_PART][200];
	int		type_part[MAX_PART];
	int		type_lvl[MAX_PART];


	bool	joueurs_morts;	// Explicite, isn't it ?
	bool	niveau_fini;	// Yeah!
	bool	niveau_bonus;
	bool	skipped;		// Jeu skippe
	bool	last_perfect1;
	bool	last_perfect2;

	int		dtime;
        Chrono time_; // Pour le mode auto
	int		nframe;			// Pour la synchronisation
	int		etape_timer;

	int		vic_x;			// Pour obtenir la victoire il faut avoir :
	int		vic_flag1;		// offset >= vic_x
	int		vic_val1;		// ET game_flag[vic_flag1] == vic_val1
	int		vic_flag2;		// ET game_flag[vic_flag2] == vic_val2
	int		vic_val2;

	int		wait_for_victory;	// Pour que la partie ne s'achève pas immédiatement
	int		wait_for_death;
	int		wait_cheat;

	int		xstart1;		// Coordonnées de départ des joueurs
	int		ystart1;
	int		xstart2;
	int		ystart2;

	Couille *	player1;
	Couille *	player2;

	RPGPlayer	rpg;

	bool	must_stop_go;
	int		teta_go;
	int		last_x_go;
	bool	fleche_go;
	int		x_fleche_go;
	int		nb_rebonds_go;
	int		delai_go;
	int		etape_fleche_go;
	int		ss_etape_fleche_go;

	bool	show_fps;
	bool	show_lists;

	int		phi_deform;

	MeteoNeige	neige[NB_FLOCONS];
	int			next_flocon;

	MeteoPluie	pluie[NB_GOUTTES];
	int			next_goutte;

public:
	// Constructeur -> met tout à NULL
	//
	Game();


	// Destructeur -> on est pas des Brujahs...
	//
	~Game();


	// jouePartie -> Faites chier la vache!
	//
	void jouePartie(int nbj, int idj);


	// joueNiveau -> Balance les PEs! Retourne VRAI si les joueurs
	// passent le niveau avec succès
	//
	bool joueNiveau(const char * nom_niveau, int type);


	// chargeNiveau -> Charge le niveau (appelé par joueNiveau)
	//
	bool chargeNiveau(const char * nom_niveau);


	// releaseNiveau -> Permet de désallouer le schnuff
	//
	void releaseNiveau();


	// updateAll -> fait tout avancer
	//
	void updateAll();


	// drawAll -> affiche tout
	//
	void drawAll(bool flip = true);

	// gameLoop -> let's burn!
	//
	void gameLoop();

	void releasePartie();

	bool chargePartie();
	bool loadList(const char * fic);

	void creeBulle(Sprite * s);

	int selectPlayer();

        template <class T>
        void UpdateCollection(const T& xs);
	void updateFlecheGo();
	void updateMeteo();
	void updateEvents();
	void updateDeformation();
	void updateBulles();
	void updateTremblements();

	void updateLock();
	void updateHoldFire();
	void updateTeteTurc();
	void updateRPG();
	void updateFlags();
	void updateVictoryAndDefeat();
	void updateMenu();
	void updateCheat();
	void manageCollisions();

        template <class T>
        void RemoveDestroyed(T& xs);

        template <class T>
        void DrawCollection(const T& xs);
	void drawTremblements();
	void drawFlecheGo();
	void drawHUB();
	void drawHUBpv(int x, int y, int pv);
	void drawTimer();

	void drawDebugInfos();

	void drawDeformation();

	void cleanLists();
	void showPE(bool bonus, bool fuckOff = false);
	void drawLoading();
	void getHiscore();
	void getName(Joueur * joueur, int i);
	void showGameOver();
	void showHighScores();

	void showBriefing(char * fn);

	void showCredits(bool theEnd = false);
	void showMainScreen();

	void go();
};


#endif
