#pragma once

#include <string>
#include <vector>

#include "graphics.h"

#define RET_CONTINUE 0
#define RET_START_GAME1 1
#define RET_HISCORES 2
#define RET_EXIT 3
#define RET_CREDITS 4
#define RET_START_GAME2 5

class MenuList {
   public:
    void Draw(SDL::Surface* surf) const;

    void MoveUp() {
        focused_ -= 1;
        if (focused_ < 0) {
            focused_ = items_.size() - 1;
        }
    }

    void MoveDown() {
        focused_ += 1;
        if (focused_ >= items_.size()) {
            focused_ = 0;
        }
    }

    int focused() const { return focused_; }

    void AddEntry(const std::string& entry) { items_.push_back(entry); }
    void ChangeEntry(int idx, const std::string& entry) { items_[idx] = entry; }

    int size() const { return items_.size(); }

   private:
    int ComputeWidth() const;
    void ShadeTextBox(SDL::Surface* surf) const;

    std::vector<std::string> items_;
    int focused_ = 0;
};

enum class MainMenuType {
    Main,
    Start,
    Options,
    Exit,
    Keys_1,
    Keys_2,
    Game_1,
    Game_2
};

class AbstractMenu {
   public:
    virtual void Draw(SDL::Surface* surf) const = 0;
    virtual MainMenuType ProcessEvent() = 0;
};

class MainMenu : public AbstractMenu {
   public:
    MainMenu2();
    void Draw(SDL::Surface* surf) const override { items_.Draw(surf); }
    MainMenuType ProcessEvent();

   private:
    MenuList items_;
};

class StartMenu : public AbstractMenu {
   public:
    StartMenu();
    void Draw(SDL::Surface* surf) const override { items_.Draw(surf); }
    MainMenuType ProcessEvent();

   private:
    MenuList items_;
};

class OptionsMenu : public AbstractMenu {
   public:
    OptionsMenu();
    void Draw(SDL::Surface* surf) const override { items_.Draw(surf); }
    MainMenuType ProcessEvent();

   private:
    void RefreshVsync();

    MenuList items_;
    std::string vsync_on_txt_;
    std::string vsync_off_txt_;
};

class KeysMenu : public AbstractMenu {
   public:
    KeysMenu(int num_player);
    void Draw(SDL::Surface* surf) const override { items_.Draw(surf); }
    MainMenuType ProcessEvent();

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

class TitleScreen {
    MainMenu first_menu_;
    StartMenu start_menu_;
    OptionsMenu options_menu_;
    KeysMenu p1_menu_;
    KeysMenu p2_menu_;
    AbstractMenu* active_menu_;

   public:
    std::vector<std::string> menu_txt_;

    RECT rec;

    bool start_sound_on;  // Ces deux booléens permettent de savoir si on a
                          // changé
    bool start_music_on;  // l'état de sound_on/music_on pour recharger le
                          // tout à la fin du menu

    MenuMain() : p1_menu_(1), p2_menu_(2), active_menu_(&first_menu_) {}
    void start();
    int update();  // Retour 0=toujours menu  1=retour jeu  2=quitter
    void stop();
    void draw(SDL::Surface* surf);
};
