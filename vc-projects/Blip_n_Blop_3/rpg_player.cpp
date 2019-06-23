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

#include <fstream>
#include <cstdio>
#include <cstring>
#include "lgx_packer.h"
#include "rpg_player.h"
#include "globals.h"
#include "txt_data.h"
#include "couille.h"
#include "scroll.h"


#define	BUFFER_LENGTH	200

RPGPlayer::RPGPlayer() : fic_name(NULL), focus(0), key_released(false), skiped(false)
{
	pic_tab[0] = NULL;
	pic_tab[1] = NULL;

	nimage[0] = 0;
	nimage[1] = 0;

	ntxt[0] = 0;
	ntxt[1] = 0;

	buffer1 = new char[BUFFER_LENGTH];
	buffer2 = new char[BUFFER_LENGTH];
}


RPGPlayer::~RPGPlayer()
{
	if (buffer1 != NULL)
		delete [] buffer1;

	if (buffer2 != NULL)
		delete [] buffer2;

	if (fic_name != NULL)
		delete [] fic_name;
}


void RPGPlayer::attachFile(const char * f)
{
	if (fic_name != NULL)
		delete [] fic_name;

	fic_name = new char[strlen(f) + 1];

	strcpy(fic_name, f);
}


bool RPGPlayer::startPlay(int n)
{
	fic_.open(fic_name);

	if (fic_.is_open() == 0) {
		debug << "RPGPlayer::startPlay() -> Cannot open " << fic_name << "\n";
		return false;
	}

	sprintf(buffer1, "rpg=%d", n);
	fic_.getline(buffer2, BUFFER_LENGTH);

	while (!fic_.eof() && strcmp(buffer1, buffer2) != 0)
		fic_.getline(buffer2, BUFFER_LENGTH);

	if (fic_.eof()) {
		debug << "RPGPlayer::startPlay() -> Ne trouve pas la scene " << n << "\n";
		return false;
	}

	nimage[0]		= -1;
	nimage[1]		= -1;
	ntxt[0]			= -1;
	ntxt[1]			= -1;

	nbjoueurs		= list_joueurs.size();
	key_released	= false;
	skiped			= false;
	focus			= 0;
	cur_joueur		= 0;
        wait_.Reset(0);

	Couille *	c;
	int			i = 0;

        for (Couille* c : list_joueurs) {
		if (c->id_couille == ID_BLIP)
			base_joueur[i] = 0;
		else
			base_joueur[i] = 6;

		i += 1;
	}

	return true;
}


void RPGPlayer::stopPlay()
{
	fic_.close();
}

bool RPGPlayer::drawScene(SDL::Surface * surf)
{
	bool	not_finished = true;

	in.update();

	if (in.anyKeyPressed()) {
		if (in.scanKey(DIK_ESCAPE)) {
			in.waitClean();

			while (updateScene());

			return false;
		}

		if (key_released && (time_.elapsed() >= 750)) {
			wait_.Reset(0);
			key_released = false;
		}
	} else {
		key_released = true;
	}


	if (wait_.is_zero()) {
		not_finished = updateScene();
        }

	// Assombrissement
	//
	Rect	r;

	if (nimage[0] >= 0) {
		r.left	= 100;
		r.top	= 120;
		r.right = 640;
		r.bottom = 220;

		LGXpaker.halfTone(surf, &r);
	}

	if (nimage[1] >= 0) {
		r.left	= 0;
		r.top	= 300;
		r.right	= 540;
		r.bottom = 400;

		LGXpaker.halfTone(surf, &r);
	}

	// Affiche les têtes de con
	//
	if (pic_tab[0] != NULL &&  nimage[0] >= 0 && nimage[0] < (*pic_tab[0]).getSize())
		(*pic_tab[0])[nimage[0]]->PasteTo(surf, 0, 120);


	if (vbuffer_wide > 640) {
		if (pic_tab[1] != NULL &&  nimage[1] >= 0 && nimage[1] < (*pic_tab[1]).getSize())
			(*pic_tab[1])[nimage[1]]->PasteTo(surf, 540, 300);
	} else {
		if (pic_tab[1] != NULL &&  nimage[1] >= 0 && nimage[1] < (*pic_tab[1]).getSize())
			(*pic_tab[1])[nimage[1]]->PasteTo(surf, 538, 300);
	}

	// Ecrit le texte
	//
	if (ntxt[0] != -1 && txt_data[ntxt[0]].c_str() != NULL)
		fnt_rpg.printMW(surf, 120, 135, txt_data[ntxt[0]].c_str(), 640);

	if (ntxt[1] != -1 && txt_data[ntxt[1]].c_str() != NULL)
		fnt_rpg.printMW(surf, 20, 315, txt_data[ntxt[1]].c_str(), 535);

	return not_finished;
}

bool RPGPlayer::updateScene()
{
	bool	ready_to_draw = false;
	char *	pos;

	while (!ready_to_draw && read() && strcmp(buffer1, "stop") != 0) {

		// D'abord, on analyse les cas ou on n'a pas besoin de couper
		//
		if (strcmp(buffer1, "endif") == 0) {
//			debug<<"endif\n";
		} else if (strcmp(buffer1, "bbswap") == 0) {
			cur_joueur += 1;
			cur_joueur %= nbjoueurs;
		} else {
			// Coupe le schnuff en 2 buffer1:txt1 et buffer2:txt2
			// tel que dans le fichier il y a "txt1=txt2"
			//
			pos = strchr(buffer1, '=');
			strcpy(buffer2, pos + 1);
			pos[0] = '\0';

			if (strcmp(buffer1, "ifnbj") == 0) {
				if (nbjoueurs != atoi(buffer2)) {
					// Si la condition est fausse on skipe le tout
					while (read() && strcmp(buffer1, "endif") != 0);
				}
			} else if (strcmp(buffer1, "focus") == 0) {
				// Gère le focus

				if (strcmp(buffer2, "haut") == 0)
					focus = 0;
				else if (strcmp(buffer2, "bas") == 0)
					focus = 1;
				else
					error(buffer2);
			} else if (strcmp(buffer1, "id") == 0) {
				// Gère l'identité de la PBK de la case

				if (strcmp(buffer2, "joueur") == 0) {
					pic_tab[focus] = &pbk_rpg_bb;
					id[focus] = ID_JOUEUR;
				} else if (strcmp(buffer2, "ennemi") == 0) {
					pic_tab[focus] = &pbk_rpg;
					id[focus] = ID_ENNEMI;
				} else
					error(buffer2);
			} else if (strcmp(buffer1, "img") == 0) {
				// Change l'image

				if (id[focus] == ID_JOUEUR)
					nimage[focus] = atoi(buffer2) + base_joueur[cur_joueur];
				else
					nimage[focus] = atoi(buffer2);
			} else if (strcmp(buffer1, "txt") == 0) {
				// Change le texte

				ntxt[focus] = atoi(buffer2);
			} else if (strcmp(buffer1, "affiche") == 0) {
				// Près pour l'affichage

				time_.Reset();
				wait_.Reset(atoi(buffer2));
				ready_to_draw = true;
			} else if (strcmp(buffer1, "flag") == 0) {
				// Flag

				pos = strchr(buffer2, '.');
				int val = atoi(pos + 1);
				pos[0] = '\0';

				game_flag[atoi(buffer2)] = val;
//				debug<<"Flag "<<atoi(buffer2)<<"="<<val<<"\n";
			} else {
				error(buffer1);
			}
		}
	}

	return ready_to_draw;
}


bool RPGPlayer::read()
{
	fic_.getline(buffer1, BUFFER_LENGTH);

	// Skip les commentaires
	//
	while (!fic_.eof() && buffer1[0] == ';')
		fic_.getline(buffer1, BUFFER_LENGTH);

        return !fic_.eof();
}



void RPGPlayer::error(const char * err_msg)
{
	debug << "RPGPlayer::updateScene() -> Erreur de syntaxe :'" << err_msg << "'\n";
}









