#pragma once

#include "abstract_menu.h"
#include "menu_list.h"

class MainMenu : public AbstractMenu {
   public:
    MainMenu();
    void Draw(SDL::Surface* surf) const override { items_.Draw(surf); }
    int ProcessEvent();

   private:
    MenuList items_;
};
