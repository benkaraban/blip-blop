
#ifndef _MenuGame_
#define _MenuGame_

#include "graphics.h"
#include "menus/options_menu.h"
#include "menus/pause_menu.h"

class MenuGame {
    PauseMenu pause_menu_;
    OptionsMenu options_menu_;
    AbstractMenu* active_;

   public:
    MenuGame() : active_(&pause_menu_) {}
    int Update();  // Retour 0=toujours menu  1=retour jeu  2=quitter
    void Draw(SDL::Surface* surf) { active_->Draw(surf); }
};

#endif
