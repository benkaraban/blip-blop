/******************************************************************
 *
 *
 *		---------------
 *		  SoundBank.h
 *		---------------
 *
 *		Classe SoundBank
 *
 *		Représente un tableau/une banque de sons (Sound).
 *
 *
 *		Prosper / LOADED -   V 0.1 - 16 Juillet 2000
 *
 *
 *
 ******************************************************************/

#pragma once

#include <memory>
#include <string>
#include <vector>

#include "sound.h"

//-----------------------------------------------------------------------------
//		Définition de la classe SoundBank
//-----------------------------------------------------------------------------

class SoundBank {
   protected:
    std::vector<std::unique_ptr<Sound>> tab_;
    std::string filename_;

   public:
    inline Sound* operator[](int n) const { return tab_[n].get(); };
    inline size_t getSize() const { return tab_.size(); };

    virtual bool loadSFX(const char* nom_fic);

    void reload();
    void reinit();
};
