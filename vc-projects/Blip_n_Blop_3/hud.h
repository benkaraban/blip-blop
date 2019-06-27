#pragma once

#include <iomanip>
#include <sstream>

#include "couille.h"
#include "globals.h"

class HUD {
   public:
    enum class Location : int { Left, Right };
    enum class Color { Blue, Orange };

    void Draw(Couille* player,
              Location location,
              Color color,
              bool bonus_stage) {
        DrawHealth(player->pv, location);
        DrawScore(player->getScore(), location, color);
        if (bonus_stage) {
            DrawBonusStage(location);
        } else {
            DrawLives(player->nb_life, location);
        }
        DrawWeapon(player->id_arme, location);

        // FIXME: The drawer clearly should be agnostic of what are the base
        // weapons with unlimited ammo.
        if (player->id_arme == ID_M16) {
            DrawAmmo(-1, false, location);
        } else {
            DrawAmmo(player->ammo, player->tire, location);
        }
        DrawCowBomb(player->nb_cow_bomb, location);
    }

   private:
    void DrawCowBomb(int nb, Location location) {
        if (location == Location::Left) {
            for (int i = 0, dxt = 0; i < nb; i++, dxt += 23)
                pbk_misc[49]->BlitTo(backSurface, 90 + dxt, 65);
        } else {
            for (int i = 0, dxt = 0; i < nb; i++, dxt += 23)
                pbk_misc[49]->BlitTo(backSurface, 520 - dxt, 65);
        }
    }

    void DrawAmmo(int ammo, bool firing, Location location) {
        int x = location == Location::Left ? 135 : 505;
        if (ammo == -1) {
            fnt_ammo.printC(backSurface, x, 43, "*");
            return;
        }

        std::string ammo_str = std::to_string(ammo);
        if (firing) {
            fnt_ammo_used.printC(backSurface, x, 43, ammo_str.c_str());
        } else {
            fnt_ammo.printC(backSurface, x, 43, ammo_str.c_str());
        }
    }

    void DrawWeapon(int weapon, Location location) {
        Picture* pic;

        switch (weapon) {
            case ID_M16:
                pic = pbk_misc[14];
                break;
            case ID_PM:
                pic = pbk_misc[8];
                break;
            case ID_LF:
                pic = pbk_misc[11];
                break;
            case ID_FUSIL:
                pic = pbk_misc[9];
                break;
            case ID_LASER:
                pic = pbk_misc[10];
                break;
        }

        int x = (location == Location::Left) ? 135 : 510;
        pic->BlitTo(backSurface, x, 50);
    }

    void DrawBonusStage(Location location) {
        if (location == Location::Left) {
            fnt_rpg.print(backSurface, 4, 5, "Bonus");
            fnt_rpg.print(backSurface, 4, 20, "Stage");
        } else {
            fnt_rpg.printR(backSurface, 635, 5, "Bonus");
            fnt_rpg.printR(backSurface, 635, 20, "Stage");
        }
    }

    void DrawLives(int lives, Location location) {
        if (location == Location::Left) {
            fnt_cool.print(backSurface, 5, 5, std::to_string(lives).c_str());
        } else {
            fnt_cool.printR(backSurface, 635, 5, std::to_string(lives).c_str());
        }
    }

    void DrawScore(int score, Location location, Color color) {
        std::ostringstream oss;
        oss << std::setw(7) << std::setfill('0') << score;
        std::string s = oss.str();

        int x = (location == Location::Left) ? 100 : 450;
        if (color == Color::Blue) {
            fnt_score_blip.print(backSurface, x, 20, s.c_str());
        } else {
            fnt_score_blop.print(backSurface, x, 20, s.c_str());
        }
    }

    static void DrawHealth(int health, Location location) {
        static const int x_health[] = {3, 0, 13, 44, 31};
        static const int y_health[] = {0, 21, 48, 21, 0};
        static const int pos[2][2] = {{20, 20}, {560, 20}};

        int x = pos[int(location)][0];
        int y = pos[int(location)][1];

        for (int i = 0; i < health; i++) {
            pbk_bb[201 - i]->BlitTo(
                backSurface, x + x_health[i], y + y_health[i]);
        }

        for (int i = health; i < 5; i++) {
            pbk_bb[196 - i]->BlitTo(
                backSurface, x + x_health[i], y + y_health[i]);
        }
    }
};
