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


RPGPlayer::RPGPlayer() : focus(0), key_released(false), skiped(false)
{
	pic_tab[0] = NULL;
	pic_tab[1] = NULL;

	nimage[0] = 0;
	nimage[1] = 0;

	ntxt[0] = 0;
	ntxt[1] = 0;
}


void RPGPlayer::attachFile(const char * f)
{
    fic_name_ = f;
}


bool RPGPlayer::startPlay(int n)
{
	fic_.open(fic_name_.c_str());

	if (fic_.is_open() == 0) {
		debug << "RPGPlayer::startPlay() -> Cannot open " << fic_name_ << "\n";
		return false;
	}

        buffer1_ = "rpg=" + std::to_string(n);
        std::getline(fic_, buffer2_);

	while (!fic_.eof() && buffer1_ != buffer2_)
		std::getline(fic_, buffer2_);

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

	while (!ready_to_draw && read() && buffer1_ != "stop") {

		// D'abord, on analyse les cas ou on n'a pas besoin de couper
		//
		if (buffer1_ == "endif") {
//			debug<<"endif\n";
		} else if (buffer1_ == "bbswap") {
			cur_joueur += 1;
			cur_joueur %= nbjoueurs;
		} else {
			// Coupe le schnuff en 2 buffer1:txt1 et buffer2:txt2
			// tel que dans le fichier il y a "txt1=txt2"
			//
			int pos = buffer1_.find('=');
			buffer2_ = buffer1_.substr(pos + 1);
                        buffer1_ = buffer1_.substr(0, pos);

			if (buffer1_ == "ifnbj") {
				if (nbjoueurs != std::stoi(buffer2_)) {
					// Si la condition est fausse on skipe le tout
					while (read() && buffer1_ != "endif");
				}
			} else if (buffer1_ == "focus") {
				// Gère le focus

				if (buffer2_ == "haut")
					focus = 0;
				else if (buffer2_ == "bas")
					focus = 1;
				else
					error(buffer2_);
			} else if (buffer1_ == "id") {
				// Gère l'identité de la PBK de la case

				if (buffer2_ == "joueur") {
					pic_tab[focus] = &pbk_rpg_bb;
					id[focus] = ID_JOUEUR;
				} else if (buffer2_ == "ennemi") {
					pic_tab[focus] = &pbk_rpg;
					id[focus] = ID_ENNEMI;
				} else
					error(buffer2_);
			} else if (buffer1_ == "img") {
				// Change l'image

				if (id[focus] == ID_JOUEUR)
					nimage[focus] = std::stoi(buffer2_) + base_joueur[cur_joueur];
				else
					nimage[focus] = std::stoi(buffer2_);
			} else if (buffer1_ == "txt") {
				// Change le texte

				ntxt[focus] = std::stoi(buffer2_);
			} else if (buffer1_ == "affiche") {
				// Près pour l'affichage

				time_.Reset();
				wait_.Reset(std::stoi(buffer2_));
				ready_to_draw = true;
			} else if (buffer1_ == "flag") {
				// Flag

				int pos = buffer2_.find('.');
				int val = std::stoi(buffer2_.substr(pos + 1));
                                buffer2_ = buffer2_.substr(0, pos);

				game_flag[std::stoi(buffer2_)] = val;
//				debug<<"Flag "<<atoi(buffer2)<<"="<<val<<"\n";
			} else {
				error(buffer1_);
			}
		}
	}

	return ready_to_draw;
}


bool RPGPlayer::read()
{
        std::getline(fic_, buffer1_);

	// Skip les commentaires
	//
	while (!fic_.eof() && buffer1_[0] == ';')
		std::getline(fic_, buffer1_);

        return !fic_.eof();
}



void RPGPlayer::error(const std::string& err_msg)
{
	debug << "RPGPlayer::updateScene() -> Erreur de syntaxe :'" << err_msg << "'\n";
}









