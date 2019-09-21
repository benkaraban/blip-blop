#pragma once

#include "abstract_menu.h"

#include <string>

#include "menu_list.h"

class OptionsPanel : public AbstractMenu {
   public:
    OptionsPanel();
    void Draw(SDL::Surface* surf) const override { items_.Draw(surf); }
    int ProcessEvent();

   private:
    void RefreshVsync();

    MenuList items_;
    std::string vsync_on_txt_;
    std::string vsync_off_txt_;
};
