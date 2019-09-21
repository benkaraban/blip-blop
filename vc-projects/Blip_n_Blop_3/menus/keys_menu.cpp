#include "keys_menu.h"

#include "../config.h"
#include "../control_alias.h"
#include "../input.h"
#include "../key_translator.h"
#include "../txt_data.h"
#include "txt_defines.h"

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

int KeysMenu::ProcessEvent() {
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
                return MenuType::Main;
            }
            EditKey();
        }
    }
    return player_ == 1 ? MenuType::Keys_1 : MenuType::Keys_2;
}
