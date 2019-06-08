#pragma once

#include "abstract_menu.h"

#include "keys_menu.h"
#include "options_panel.h"

class OptionsMenu : public AbstractMenu {
   public:
    OptionsMenu() : p1_menu_(1), p2_menu_(2), active_menu_(&options_menu_) {}
    void Draw(SDL::Surface* surf) const override { active_menu_->Draw(surf); }
    int ProcessEvent() override;

   private:
    OptionsPanel options_menu_;
    KeysMenu p1_menu_;
    KeysMenu p2_menu_;
    AbstractMenu* active_menu_;
};
