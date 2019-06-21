/******************************************************************
 *
 *
 *              ------------------
 *                PictureBank.h
 *              ------------------
 *
 *              Classe PictureBank
 *
 *              Représente un tableau/une banque d'images.
 *
 *
 *              Prosper / LOADED -   V 0.2 - 13 Juillet 2000
 *
 *
 *
 ******************************************************************/

#pragma once

#include <memory>
#include <string>
#include <vector>

#include "picture.h"

class PictureBank {
   private:
    std::vector<std::unique_ptr<Picture>> tab_;
    std::string filename_;
    int flag_fic;
    bool trans_fic;

   public:
    inline Picture* operator[](int n) const { return tab_[n].get(); };
    inline int getSize() const { return tab_.size(); };

    PictureBank();
    bool loadGFX(const char* file, int flag = DDSURF_BEST, bool trans = true);
    bool restoreAll();
};
