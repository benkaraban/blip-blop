#include "menu_main.h"
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

#define NB_TXT 10

void TitleScreen::start() {
    start_music_on = music_on;
    start_sound_on = sound_on;
}

int TitleScreen::update() {
    in.update();

    MenuType next = MenuType(active_menu_->ProcessEvent());
    in.waitClean();

    switch (next) {
        case MenuType::Main:
            active_menu_ = &first_menu_;
            break;
        case MenuType::Start:
            active_menu_ = &start_menu_;
            break;
        case MenuType::Options:
            active_menu_ = &options_menu_;
            break;
        case MenuType::Game_1:
            return RET_START_GAME1;
        case MenuType::Game_2:
            return RET_START_GAME2;
        case MenuType::Exit:
            return RET_EXIT;
    }

    return RET_CONTINUE;
}

void TitleScreen::stop() {
    if (sound_on != start_sound_on) {
        if (sound_on) {
            sbk_bb.loadSFX("data\\bb.sfx");
        } else {
            sbk_bb.close();
        }
    }

    if (music_on != start_music_on) {
        if (music_on) {
            if (strlen(current_mbk) > 0) {
                if (!mbk_niveau.open(current_mbk))
                    music_on = false;
                else {
                    if (current_zik >= 0) {
                        mbk_niveau.play(current_zik);
                    }
                }
            }
        } else {
            mbk_niveau.stop();
            mbk_niveau.close();
        }
    }
}

void TitleScreen::draw(SDL::Surface* surf) { active_menu_->Draw(surf); }
