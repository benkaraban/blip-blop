#include "menu_list.h"

#include "../globals.h"
#include "../lgx_packer.h"

int MenuList::ComputeWidth() const {
    int width = 0;

    for (const std::string& s : items_) {
        int tmp = fnt_menu.width(s.c_str());

        if (tmp > width) {
            width = tmp;
        }
    }

    width += 60;
    width /= 2;

    if (width < 200)
        width = 200;
    else if (width > 320)
        width = 320;
    return width;
}

void MenuList::ShadeTextBox(SDL::Surface* surf) const {
    int ys = items_.size() * 15;
    // Compute the size of the "schnuff" (= thing) to darken
    //
    int width = ComputeWidth();

    Rect rec;
    rec.top = 220 - ys;
    rec.left = 320 - width;
    rec.bottom = 260 + ys;
    rec.right = 320 + width;

    LGXpaker.halfTone(surf, &rec);
}

void MenuList::Draw(SDL::Surface* surf) const {
    ShadeTextBox(surf);

    int y = 240 - items_.size() * 15;
    for (int i = 0; i < items_.size(); ++i) {
        if (focused_ == i)
            fnt_menus.printC(surf, 320, y, items_[i].c_str());
        else
            fnt_menu.printC(surf, 320, y, items_[i].c_str());

        y += 30;
    }
}
