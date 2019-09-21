#include "main_menu.h"

#include "../control_alias.h"
#include "../input.h"
#include "../txt_data.h"
#include "txt_defines.h"

MainMenu::MainMenu() {
    items_.AddEntry(txt_data[TXT_START_GAME]);
    items_.AddEntry("OPTIONS");
    items_.AddEntry(txt_data[TXT_EXIT]);
}

int MainMenu::ProcessEvent() {
    if (in.scanKey(DIK_UP) || in.scanAlias(ALIAS_P1_UP)) {
        items_.MoveUp();
    } else if (in.scanKey(DIK_DOWN) || in.scanAlias(ALIAS_P1_DOWN)) {
        items_.MoveDown();
    }
    if (in.scanKey(DIK_RETURN) || in.scanAlias(ALIAS_P1_FIRE)) {
        switch (items_.focused()) {
            case 0:
                return MenuType::Start;
            case 1:
                return MenuType::Options;
            case 2:
                return MenuType::Exit;
        }
    }
    return MenuType::Main;
}
