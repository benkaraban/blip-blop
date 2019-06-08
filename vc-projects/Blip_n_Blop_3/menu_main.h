#pragma once

#include <string>
#include <vector>

#include "graphics.h"
#include "menus/main_menu.h"
#include "menus/options_menu.h"
#include "menus/start_menu.h"

#define RET_CONTINUE 0
#define RET_START_GAME1 1
#define RET_HISCORES 2
#define RET_EXIT 3
#define RET_CREDITS 4
#define RET_START_GAME2 5

class TitleScreen {
    MainMenu first_menu_;
    StartMenu start_menu_;
    OptionsMenu options_menu_;
    AbstractMenu* active_menu_;

   public:
    bool start_sound_on;  // Ces deux booléens permettent de savoir si on a
                          // changé
    bool start_music_on;  // l'état de sound_on/music_on pour recharger le
                          // tout à la fin du menu

    TitleScreen() : active_menu_(&first_menu_) {}
    void start();
    int update();  // Retour 0=toujours menu  1=retour jeu  2=quitter
    void stop();
    void draw(SDL::Surface* surf);
};
