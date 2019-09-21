#include <string>

#include <stdio.h>
#include <string.h>
#include "config.h"
#include "input.h"
#include "key_translator.h"

static std::string DIK_to_string_us(int n);
static std::string DIK_to_string_fr(int n);

std::string DIK_to_string(int n) {
    if (lang_type == LANG_FR) {
        return DIK_to_string_fr(n);
    } else {
        return DIK_to_string_us(n);
    }
}

std::string DIK_to_string_us(int n) {
    int j = n >> 10 & 0xFF;

    /*
    Check if is a joystick.
    Normal keys go from 0x0 to 0xFF
    Special keys from 0x40000000 to 0x40000FFF
    Joypad buttons are from 0x0 to 0xFF and joypad number is shifted 10 bytes to
    the left
    */

    if (j == 0) {
        switch (n) {
#define X(_num, _val) \
    case _num:        \
        return _val;
#include "keys_us.xmacro"
#undef X
            default:
                return "UNDEFINED";
        }
    } else {
        int d = n & 0x3FF;

        switch (d) {
            case JOY_UP:
                return std::string("JOY") + std::to_string(j) + " UP";
            case JOY_DOWN:
                return std::string("JOY") + std::to_string(j) + " DOWN";
            case JOY_LEFT:
                return std::string("JOY") + std::to_string(j) + " LEFT";
            case JOY_RIGHT:
                return std::string("JOY") + std::to_string(j) + " RIGHT";
            default:
                return std::string("JOY") + std::to_string(j) + " BUTTON" +
                       std::to_string(d);
        }
    }
}

std::string DIK_to_string_fr(int n) {
    int j = n >> 10;

    if (j == 0) {
        switch (n) {
#define X(_num, _val) \
    case _num:        \
        return _val;
#include "keys_fr.xmacro"
#undef X
            default:
                return "INDEFINIE";
        }
    } else {
        int d = n & 0x3FF;
        switch (d) {
            case JOY_UP:
                return std::string("JOYSTICK") + std::to_string(j) + " HAUT";
            case JOY_DOWN:
                return std::string("JOYSTICK") + std::to_string(j) + " BAS";
            case JOY_LEFT:
                return std::string("JOYSTICK") + std::to_string(j) + " GAUCHE";
            case JOY_RIGHT:
                return std::string("JOYSTICK") + std::to_string(j) + " DROITE";
            default:
                return std::string("JOYSTICK") + std::to_string(j) + " BOUTON" +
                       std::to_string(d + 1);
        }
    }
}
