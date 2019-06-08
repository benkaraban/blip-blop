#include "menu_game.h"
#include <cstdio>
#include <cstring>
#include "config.h"
#include "control_alias.h"
#include "globals.h"
#include "input.h"
#include "key_translator.h"
#include "lgx_packer.h"
#include "menus/txt_defines.h"
#include "txt_data.h"

int MenuGame::Update() {
    in.update();
    MenuType next = MenuType(active_->ProcessEvent());
    in.waitClean();

    switch (next) {
        case MenuType::Game_1:
            return 1;
        case MenuType::Exit:
            return 2;
        case MenuType::Main:
            active_ = &pause_menu_;
            break;
        case MenuType::Options:
            active_ = &options_menu_;
    }
    return 0;
}
