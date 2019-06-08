#include "menu_main.h"
#include <cstdio>
#include <cstring>
#include "config.h"
#include "control_alias.h"
#include "globals.h"
#include "input.h"
#include "key_translator.h"
#include "lgx_packer.h"
#include "txt_data.h"

#define TXT_RESUME 800
#define TXT_VIDEO 801
#define TXT_SOUND 802
#define TXT_CTRL 803
#define TXT_MISC 804
#define TXT_EXIT_GAME 805
#define TXT_ON 809
#define TXT_OFF 810
#define TXT_VSYNC 806
#define TXT_FULLSCREEN 835

#define TXT_SYNCHRO 806
#define TXT_DETAIL 807
#define TXT_RETURN 808
#define TXT_DHIGH 809
#define TXT_DMED 810
#define TXT_DLOW 811

#define TXT_MUSICVOL 812
#define TXT_SOUNDVOL 813
#define TXT_MUSICON 814
#define TXT_SOUNDON 815

#define TXT_LANGUAGE 816
#define TXT_RESET 829

#define TXT_P1CTRL 817
#define TXT_P2CTRL 818
#define TXT_P1KEYS 819
#define TXT_P2KEYS 820

#define TXT_UP 821
#define TXT_DOWN 822
#define TXT_LEFT 823
#define TXT_RIGHT 824
#define TXT_FIRE 825
#define TXT_JUMP 826
#define TXT_SPECIAL 827

#define TXT_START_GAME 830
#define TXT_EXIT 833

#define TXT_START_GAME1 831
#define TXT_START_GAME2 832

#define TXT_CANCEL 834

#define MENU_MAIN 0

#define MENU_KEY1 5
#define MENU_KEY2 6
#define MENU_OPTS 7
#define MENU_EXIT 8
#define MENU_START 9

#define NB_TXT 10

int MenuList::ComputeWidth() const {
    int width = 0;

    for (const std::string& s : items_) {
        int tmp = fnt_menu.width(s.c_str());

        if (tmp > width) {
            width = tmp;
        }
    }

    width += 60;
    width /= 2;

    if (width < 200)
        width = 200;
    else if (width > 320)
        width = 320;
    return width;
}

void MenuList::ShadeTextBox(SDL::Surface* surf) const {
    int ys = items_.size() * 15;
    // Compute the size of the "schnuff" (= thing) to darken
    //
    int width = ComputeWidth();

    RECT rec;
    rec.top = 220 - ys;
    rec.left = 320 - width;
    rec.bottom = 260 + ys;
    rec.right = 320 + width;

    LGXpaker.halfTone(surf, &rec);
}

void MenuList::Draw(SDL::Surface* surf) const {
    ShadeTextBox(surf);

    int y = 240 - items_.size() * 15;
    for (int i = 0; i < items_.size(); ++i) {
        if (focused_ == i)
            fnt_menus.printC(surf, 320, y, items_[i].c_str());
        else
            fnt_menu.printC(surf, 320, y, items_[i].c_str());

        y += 30;
    }
}

MainMenu2::MainMenu2() {
    items_.AddEntry(txt_data[TXT_START_GAME]);
    items_.AddEntry("OPTIONS");
    items_.AddEntry(txt_data[TXT_EXIT]);
}

MainMenuType MainMenu2::ProcessEvent() {
    if (in.scanKey(DIK_UP) || in.scanAlias(ALIAS_P1_UP)) {
        items_.MoveUp();
    } else if (in.scanKey(DIK_DOWN) || in.scanAlias(ALIAS_P1_DOWN)) {
        items_.MoveDown();
    }
    if (in.scanKey(DIK_RETURN) || in.scanAlias(ALIAS_P1_FIRE)) {
        switch (items_.focused()) {
            case 0:
                return MainMenuType::Start;
            case 1:
                return MainMenuType::Options;
            case 2:
                return MainMenuType::Exit;
        }
    }
    return MainMenuType::Main;
}

StartMenu::StartMenu() {
    items_.AddEntry(txt_data[TXT_START_GAME1]);
    items_.AddEntry(txt_data[TXT_START_GAME2]);
    items_.AddEntry(txt_data[TXT_RETURN]);
}

MainMenuType StartMenu::ProcessEvent() {
    if (in.scanKey(DIK_UP) || in.scanAlias(ALIAS_P1_UP)) {
        items_.MoveUp();
    } else if (in.scanKey(DIK_DOWN) || in.scanAlias(ALIAS_P1_DOWN)) {
        items_.MoveDown();
    }
    if (in.scanKey(DIK_RETURN) || in.scanAlias(ALIAS_P1_FIRE)) {
        switch (items_.focused()) {
            case 0:
                return MainMenuType::Game_1;
            case 1:
                return MainMenuType::Game_2;
            case 2:
                return MainMenuType::Main;
        }
    }
    return MainMenuType::Start;
}

MenuMain::MenuMain() {
    active_menu_ = &first_menu_;

    redefine = -1;
}

void MenuMain::start() {
    current_menu = MENU_MAIN;
    nb_focus = 3;
    focus = 0;
    updateName();

    start_music_on = music_on;
    start_sound_on = sound_on;
}

int MenuMain::update() {
    in.update();

    updateRedefine();
    updateName();

    MainMenuType next = active_menu_->ProcessEvent();
    switch (next) {
        case MainMenuType::Main:
            active_menu_ = &first_menu_;
            break;
        case MainMenuType::Start:
            active_menu_ = &start_menu_;
            break;
        case MainMenuType::Game_1:
            return RET_START_GAME1;
        case MainMenuType::Game_2:
            return RET_START_GAME2;
        case MainMenuType::Exit:
            return RET_EXIT;
    }

    //////////////////////////////////////////////////
    //	Touche haut
    //////////////////////////////////////////////////

    if (in.scanKey(DIK_UP) || in.scanAlias(ALIAS_P1_UP)) {
        focus -= 1;

        if (focus < 0) focus = nb_focus - 1;

        in.waitClean();
    }
    //////////////////////////////////////////////////
    //	Touche bas
    //////////////////////////////////////////////////
    else if (in.scanKey(DIK_DOWN) || in.scanAlias(ALIAS_P1_DOWN)) {
        focus += 1;
        focus %= nb_focus;
        in.waitClean();
    }

    //////////////////////////////////////////////////
    //	Touche entrée
    //////////////////////////////////////////////////

    if (in.scanKey(DIK_RETURN) || in.scanAlias(ALIAS_P1_FIRE)) {
        in.waitClean();

        switch (current_menu) {
            case MENU_OPTS:
                switch (focus) {
                    case 0:
                        vSyncOn = !vSyncOn;
                        updateName();
                        return RET_CONTINUE;
                        break;

                    case 1:
                        current_menu = MENU_KEY1;
                        nb_focus = 8;
                        focus = 7;
                        updateName();
                        return RET_CONTINUE;
                        break;

                    case 2:
                        current_menu = MENU_KEY2;
                        nb_focus = 8;
                        focus = 7;
                        updateName();
                        return RET_CONTINUE;
                        break;

                    case 3:  // Return
                        current_menu = MENU_MAIN;
                        nb_focus = 3;
                        focus = 1;
                        updateName();
                        return RET_CONTINUE;
                        break;
                }
                break;

            case MENU_KEY1:  // Redefinition
                switch (focus) {
                    case 7:
                        current_menu = MENU_OPTS;
                        nb_focus = 4;
                        focus = 1;
                        updateName();
                        return 0;
                        break;

                    default:
                        redefine = focus;
                        updateName();
                        return 0;
                        break;
                }
                break;

            case MENU_KEY2:  // Redefinition 2
                switch (focus) {
                    case 7:
                        current_menu = MENU_OPTS;
                        nb_focus = 4;
                        focus = 2;
                        updateName();
                        return 0;
                        break;

                    default:
                        redefine = focus;
                        updateName();
                        return 0;
                        break;
                }
                break;
        }
    }

    //////////////////////////////////////////////////
    //	Touche droite
    //////////////////////////////////////////////////

    if (in.scanKey(DIK_RIGHT) || in.scanAlias(ALIAS_P1_RIGHT)) {
        in.waitClean();

        switch (current_menu) {
            case MENU_OPTS:
                switch (focus) {
                    case 0:
                        vSyncOn = !vSyncOn;
                        updateName();
                        return RET_CONTINUE;
                        break;
                }
                break;
        }
    }
    //////////////////////////////////////////////////
    //	Touche gauche
    //////////////////////////////////////////////////
    else if (in.scanKey(DIK_LEFT) || in.scanAlias(ALIAS_P1_LEFT)) {
        in.waitClean();

        switch (current_menu) {
            case MENU_OPTS:
                switch (focus) {
                    case 0:
                        vSyncOn = !vSyncOn;
                        updateName();
                        return RET_CONTINUE;
                        break;
                }
                break;
        }
    }

    return RET_CONTINUE;
}

void MenuMain::stop() {
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

    old_menu = -1;
}

void MenuMain::draw(SDL::Surface* surf) { active_menu_->Draw(surf); }

void MenuMain::updateRedefine() {
    if (redefine == -1) return;

    int n = in.waitKey();

    if (current_menu == MENU_KEY1) {
        switch (redefine) {
            case 0:
                in.setAlias(ALIAS_P1_UP, n);
                break;
            case 1:
                in.setAlias(ALIAS_P1_DOWN, n);
                break;
            case 2:
                in.setAlias(ALIAS_P1_LEFT, n);
                break;
            case 3:
                in.setAlias(ALIAS_P1_RIGHT, n);
                break;
            case 4:
                in.setAlias(ALIAS_P1_FIRE, n);
                break;
            case 5:
                in.setAlias(ALIAS_P1_JUMP, n);
                break;
            case 6:
                in.setAlias(ALIAS_P1_SUPER, n);
                break;
        }
    } else {
        switch (redefine) {
            case 0:
                in.setAlias(ALIAS_P2_UP, n);
                break;
            case 1:
                in.setAlias(ALIAS_P2_DOWN, n);
                break;
            case 2:
                in.setAlias(ALIAS_P2_LEFT, n);
                break;
            case 3:
                in.setAlias(ALIAS_P2_RIGHT, n);
                break;
            case 4:
                in.setAlias(ALIAS_P2_FIRE, n);
                break;
            case 5:
                in.setAlias(ALIAS_P2_JUMP, n);
                break;
            case 6:
                in.setAlias(ALIAS_P2_SUPER, n);
                break;
        }
    }

    in.waitClean();
    redefine = -1;
}

void MenuMain::updateName() {
    menu_txt_.clear();

    switch (current_menu) {
        case MENU_OPTS:

            if (vSyncOn)
                menu_txt_.push_back(txt_data[TXT_VSYNC] + " " +
                                    txt_data[TXT_ON]);
            else
                menu_txt_.push_back(txt_data[TXT_VSYNC] + " " +
                                    txt_data[TXT_OFF]);

            menu_txt_.push_back(txt_data[TXT_P1KEYS]);
            menu_txt_.push_back(txt_data[TXT_P2KEYS]);
            menu_txt_.push_back(txt_data[TXT_RETURN]);
            break;

        case MENU_KEY1: {
            auto keys = {std::make_tuple(0, TXT_UP, ALIAS_P1_UP),
                         std::make_tuple(1, TXT_DOWN, ALIAS_P1_DOWN),
                         std::make_tuple(2, TXT_LEFT, ALIAS_P1_LEFT),
                         std::make_tuple(3, TXT_RIGHT, ALIAS_P1_RIGHT),
                         std::make_tuple(4, TXT_FIRE, ALIAS_P1_FIRE),
                         std::make_tuple(5, TXT_JUMP, ALIAS_P1_JUMP),
                         std::make_tuple(6, TXT_SPECIAL, ALIAS_P1_SUPER)};
            for (auto& k : keys) {
                if (redefine == std::get<0>(k)) {
                    menu_txt_.push_back(txt_data[std::get<1>(k)] + " = ...");
                } else {
                    menu_txt_.push_back(
                        txt_data[std::get<1>(k)] + " = " +
                        DIK_to_string(in.getAlias(std::get<2>(k))));
                }
            }

            menu_txt_.push_back(txt_data[TXT_RETURN]);
            break;
        }

        case MENU_KEY2: {
            auto keys = {std::make_tuple(0, TXT_UP, ALIAS_P2_UP),
                         std::make_tuple(1, TXT_DOWN, ALIAS_P2_DOWN),
                         std::make_tuple(2, TXT_LEFT, ALIAS_P2_LEFT),
                         std::make_tuple(3, TXT_RIGHT, ALIAS_P2_RIGHT),
                         std::make_tuple(4, TXT_FIRE, ALIAS_P2_FIRE),
                         std::make_tuple(5, TXT_JUMP, ALIAS_P2_JUMP),
                         std::make_tuple(6, TXT_SPECIAL, ALIAS_P2_SUPER)};
            for (auto& k : keys) {
                if (redefine == std::get<0>(k)) {
                    menu_txt_.push_back(txt_data[std::get<1>(k)] + " = ...");
                } else {
                    menu_txt_.push_back(
                        txt_data[std::get<1>(k)] + " = " +
                        DIK_to_string(in.getAlias(std::get<2>(k))));
                }
            }

            menu_txt_.push_back(txt_data[TXT_RETURN]);
            break;
        }
    }
}
