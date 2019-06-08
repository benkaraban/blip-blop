#include "dd_gfx.h"
#include <stdio.h>
#include "ben_debug.h"
#include "config.h"
#include "globals.h"
#include "l_timer.h"
#include "lgx_packer.h"

//-----------------------------------------------------------------------------
//              Objet 'ddraw' global REEL
//-----------------------------------------------------------------------------

Graphics* graphicInstance = NULL;

static int oldRefreshRate = -1;

//-----------------------------------------------------------------------------
// Nom: DDInitDirectDraw
// Desc: Ouvre DirectDraw
//-----------------------------------------------------------------------------

void DDInitDirectDraw() {
    if (graphicInstance != NULL) {
        debug << "Graphic engine already initialized!\n";
    }
    graphicInstance = new Graphics();
    graphicInstance->Init();
}

//-----------------------------------------------------------------------------
// Nom: DDCloseDirectDraw()
// Desc: Ferme Direct Draw
//-----------------------------------------------------------------------------

void DDCloseDirectDraw() { graphicInstance->~Graphics(); }

//-----------------------------------------------------------------------------
// Nom: DDSetGfxMode
// Desc: Règle la résolution graphique X Y NbBits/Pixel
//-----------------------------------------------------------------------------

void DDSetGfxMode(int x, int y, int d, bool fullscreen) {
    debug << "DDSetGfxMode (" << x << "," << y << ")"
          << "\n";
    graphicInstance->SetGfxMode(x, y, d, fullscreen);
}

//-----------------------------------------------------------------------------
// Nom: DDCreateSurface
// Desc: Crée une Surface de taille X*Y
//-----------------------------------------------------------------------------

SDL::Surface* DDCreateSurface(int x, int y) {
    debug << "DDCreateSurface (" << x << "," << y << ")"
          << "\n";
    return graphicInstance->CreateSurface(x, y, DDSURF_BEST);
}

//-----------------------------------------------------------------------------
// Nom: DDCreateSurface
// Desc: Crée une Surface de taille X*Y en mém VIDEO / SYSTEM (cf DDOpenBMP)
//-----------------------------------------------------------------------------

SDL::Surface* DDCreateSurface(int x, int y, int flags) {
    return graphicInstance->CreateSurface(x, y, flags);
}

//-----------------------------------------------------------------------------
// Nom: DDCreatePrimary
// Desc: Crée une Primary Surface sans double buffer
//-----------------------------------------------------------------------------

SDL::Surface* DDCreatePrimary() {
    debug << "DDCreatePrimary ()"
          << "\n";
    return graphicInstance->CreatePrimary();
}

//-----------------------------------------------------------------------------
// Nom: DDCreatePrimary
// Desc: Crée une Primary Surface avec double buffer (le paramètre)
//-----------------------------------------------------------------------------

SDL::Surface* DDCreatePrimary(SDL::Surface*& back) {
    debug << "DDCreatePrimary (back)"
          << "\n";
    return graphicInstance->CreatePrimary(back);
}

//-----------------------------------------------------------------------------
// Nom: DDLoadBMP
// Desc: Crée une surface ayant pour contenu une image (BMP)
//-----------------------------------------------------------------------------

SDL::Surface* DDLoadBMP(char* file) {
    debug << "DDLoadBMP (" << file << ")"
          << "\n";
    return graphicInstance->LoadBMP(file, DDSURF_BEST);
}

//-----------------------------------------------------------------------------
// Nom: DDLoadBMP
// Desc: Crée une surface ayant pour contenu l'image
//-----------------------------------------------------------------------------

SDL::Surface* DDLoadBMP(char* file, int flags) {
    debug << "DDLoadBMP (" << file << ")"
          << "\n";
    return graphicInstance->LoadBMP(file, flags);
}

//-----------------------------------------------------------------------------
// Nom: DDSetColorKey
// Desc: Règle la couleur transparente d'une surface
//-----------------------------------------------------------------------------

HRESULT DDSetColorKey(SDL::Surface* surf, COLORREF rgb) {
    // debug << "DDSetColorKey ()" << "\n";
    return graphicInstance->SetColorKey(surf, rgb);
}

void DDFlip() {
    // debug << "DDFlip ()" << "\n";
    graphicInstance->Flip();
}

void DDFlipV() {
    // debug << "DDFlipV ()" << "\n";
    graphicInstance->FlipV();
}

void DDToggleFullscreen() { graphicInstance->ToggleFullscreen(); }
