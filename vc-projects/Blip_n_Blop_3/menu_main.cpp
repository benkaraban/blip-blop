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

OptionsMenu::OptionsMenu() {
    vsync_on_txt_ = txt_data[TXT_VSYNC] + " " + txt_data[TXT_ON];
    vsync_off_txt_ = txt_data[TXT_VSYNC] + " " + txt_data[TXT_OFF];

    items_.AddEntry("VSYNC");
    items_.AddEntry(txt_data[TXT_P1KEYS]);
    items_.AddEntry(txt_data[TXT_P2KEYS]);
    items_.AddEntry(txt_data[TXT_RETURN]);
    RefreshVsync();
}

void OptionsMenu::RefreshVsync() {
    items_.ChangeEntry(0, vSyncOn ? vsync_on_txt_ : vsync_off_txt_);
}

MainMenuType OptionsMenu::ProcessEvent() {
    if (in.scanKey(DIK_UP) || in.scanAlias(ALIAS_P1_UP)) {
        items_.MoveUp();
    } else if (in.scanKey(DIK_DOWN) || in.scanAlias(ALIAS_P1_DOWN)) {
        items_.MoveDown();
    }
    if (in.scanKey(DIK_RIGHT) || in.scanAlias(ALIAS_P1_RIGHT) ||
        in.scanKey(DIK_LEFT) || in.scanAlias(ALIAS_P1_LEFT)) {
        vSyncOn = !vSyncOn;
        RefreshVsync();
    }
    if (in.scanKey(DIK_RETURN) || in.scanAlias(ALIAS_P1_FIRE)) {
        switch (items_.focused()) {
            case 0:
                vSyncOn = !vSyncOn;
                RefreshVsync();
                break;
            case 1:
                return MainMenuType::Keys_1;
            case 2:
                return MainMenuType::Keys_2;
            case 3:
                return MainMenuType::Main;
        }
    }
    return MainMenuType::Options;
}

KeysMenu::KeysMenu(int nb_player) {
    player_ = nb_player;
    if (nb_player == 1) {
        dat_ = {std::make_tuple(0, TXT_UP, ALIAS_P1_UP),
                std::make_tuple(1, TXT_DOWN, ALIAS_P1_DOWN),
                std::make_tuple(2, TXT_LEFT, ALIAS_P1_LEFT),
                std::make_tuple(3, TXT_RIGHT, ALIAS_P1_RIGHT),
                std::make_tuple(4, TXT_FIRE, ALIAS_P1_FIRE),
                std::make_tuple(5, TXT_JUMP, ALIAS_P1_JUMP),
                std::make_tuple(6, TXT_SPECIAL, ALIAS_P1_SUPER)};
    } else if (nb_player == 2) {
        dat_ = {std::make_tuple(0, TXT_UP, ALIAS_P2_UP),
                std::make_tuple(1, TXT_DOWN, ALIAS_P2_DOWN),
                std::make_tuple(2, TXT_LEFT, ALIAS_P2_LEFT),
                std::make_tuple(3, TXT_RIGHT, ALIAS_P2_RIGHT),
                std::make_tuple(4, TXT_FIRE, ALIAS_P2_FIRE),
                std::make_tuple(5, TXT_JUMP, ALIAS_P2_JUMP),
                std::make_tuple(6, TXT_SPECIAL, ALIAS_P2_SUPER)};
    } else {
        throw std::invalid_argument("nb_player can be only 1 or 2");
    }

    for (auto& k : dat_) {
        items_.AddEntry(KeyText(std::get<0>(k)));
    }

    items_.AddEntry(txt_data[TXT_RETURN]);
}

std::string KeysMenu::WaitText(int n) const {
    return txt_data[std::get<1>(dat_[n])] + " = ...";
}
std::string KeysMenu::KeyText(int n) const {
    auto& k = dat_[n];
    return txt_data[std::get<1>(k)] + " = " +
           DIK_to_string(in.getAlias(std::get<2>(k)));
}

void KeysMenu::EditKey() {
    state_ = State::WaitingKey;
    items_.ChangeEntry(items_.focused(), WaitText(items_.focused()));
}

void KeysMenu::SetKey(int key) {
    state_ = State::Browsing;
    in.setAlias(std::get<2>(dat_[items_.focused()]), key);
    items_.ChangeEntry(items_.focused(), KeyText(items_.focused()));
}

MainMenuType KeysMenu::ProcessEvent() {
    if (state_ == State::WaitingKey) {
        int key = in.waitKey();
        SetKey(key);
    } else {
        if (in.scanKey(DIK_UP) || in.scanAlias(ALIAS_P1_UP)) {
            items_.MoveUp();
        } else if (in.scanKey(DIK_DOWN) || in.scanAlias(ALIAS_P1_DOWN)) {
            items_.MoveDown();
        }
        if (in.scanKey(DIK_RETURN) || in.scanAlias(ALIAS_P1_FIRE)) {
            if (items_.focused() == items_.size() - 1) {
                return MainMenuType::Main;
            }
            EditKey();
        }
    }
    return player_ == 1 ? MainMenuType::Keys_1 : MainMenuType::Keys_2;
}

void MenuMain::start() {
    start_music_on = music_on;
    start_sound_on = sound_on;
}

int MenuMain::update() {
    in.update();

    MainMenuType next = active_menu_->ProcessEvent();
    in.waitClean();

    switch (next) {
        case MainMenuType::Main:
            active_menu_ = &first_menu_;
            break;
        case MainMenuType::Start:
            active_menu_ = &start_menu_;
            break;
        case MainMenuType::Options:
            active_menu_ = &options_menu_;
            break;
        case MainMenuType::Keys_1:
            active_menu_ = &p1_menu_;
            break;
        case MainMenuType::Keys_2:
            active_menu_ = &p2_menu_;
            break;
        case MainMenuType::Game_1:
            return RET_START_GAME1;
        case MainMenuType::Game_2:
            return RET_START_GAME2;
        case MainMenuType::Exit:
            return RET_EXIT;
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
}

void MenuMain::draw(SDL::Surface* surf) { active_menu_->Draw(surf); }
