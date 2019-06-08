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
    void ChangeEntry(int idx, std::string& entry) { items_[idx] = entry; }

   private:
    int ComputeWidth() const;
    void ShadeTextBox(SDL::Surface* surf) const;

    std::vector<std::string> items_;
    int focused_ = 0;
};

enum class MainMenuType { Main, Start, Options, Exit, Game_1, Game_2 };

class AbstractMenu {
   public:
    virtual void Draw(SDL::Surface* surf) const = 0;
    virtual MainMenuType ProcessEvent() = 0;
};

class MainMenu2 : public AbstractMenu {
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

class MenuMain {
    MainMenu2 first_menu_;
    StartMenu start_menu_;
    AbstractMenu* active_menu_;

   public:
    int current_menu;  // Numéro du menu courant
    int focus;         // Numéro du menu EN ROUGE
    int nb_focus;      // Nombre de choix du menu actuel
    std::vector<std::string> menu_txt_;
    int redefine;  // Numéro du schnuff à redéfinir
    int old_menu;
    bool up;

    RECT rec;

    bool start_sound_on;  // Ces deux booléens permettent de savoir si on a
                          // changé
    bool start_music_on;  // l'état de sound_on/music_on pour recharger le
                          // tout à la fin du menu

    MenuMain();
    void start();
    int update();  // Retour 0=toujours menu  1=retour jeu  2=quitter
    void stop();
    void updateName();
    void updateRedefine();
    void draw(SDL::Surface* surf);
};
