#pragma once

#include <array>
#include <tuple>

#include "abstract_menu.h"
#include "menu_list.h"

class KeysMenu : public AbstractMenu {
   public:
    KeysMenu(int num_player);
    void Draw(SDL::Surface* surf) const override { items_.Draw(surf); }
    int ProcessEvent();

   private:
    enum class State { WaitingKey, Browsing };
    void EditKey();
    void SetKey(int key);
    std::string WaitText(int n) const;
    std::string KeyText(int n) const;

    std::array<std::tuple<int, int, int>, 7> dat_;
    MenuList items_;
    State state_;
    int player_;
};
