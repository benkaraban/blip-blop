#include <cstring>

#include "globals.h"
#include "config.h"
#include "scroll.h"
#include "ben_debug.h"

bool RestoreAll()
{
	if (primSurface->Restore() != DD_OK) {
		debug << "Cannot restore primary surface.\n";
		return false;
	}

	fnt_menu.restoreAll();

	// Affiche un "LOADING..."
	//
	fnt_menu.printC(backSurface, 320, 210, "PLEASE WAIT");
	//primSurface->Flip(NULL, DDFLIP_WAIT);
	graphicInstance->Flip();

	graphicInstance->RestoreAllSurfaces();

	n_img = 0;
	xTex = 0;
	n_cache = 0;
	next_x = 0;

	pbk_decor.restoreAll();
	pbk_blip.restoreAll();
	pbk_blop.restoreAll();
	pbk_bb.restoreAll();
	pbk_misc.restoreAll();
	pbk_ennemis.restoreAll();
	pbk_niveau.restoreAll();
	pbk_rpg.restoreAll();
	pbk_rpg_bb.restoreAll();

	pbk_inter.restoreAll();

	fnt_score_blip.restoreAll();
	fnt_score_blop.restoreAll();
	fnt_ammo.restoreAll();
	fnt_ammo_used.restoreAll();
	fnt_cool.restoreAll();
	fnt_rpg.restoreAll();
	fnt_menus.restoreAll();

	in.reAcquire();

	return true;
}
