#pragma once

#include "abstract_menu.h"
#include "menu_list.h"

class StartMenu : public AbstractMenu {
   public:
    StartMenu();
    void Draw(SDL::Surface* surf) const override { items_.Draw(surf); }
    int ProcessEvent();

   private:
    MenuList items_;
};
