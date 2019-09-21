#include "ben_maths.h"
#include <math.h>
#include <iostream>

static int bCos[360] = {0};
static int bSin[360] = {0};
static char bSqr[0xFFFF] = {0};

class MathsInit {
   public:
    MathsInit() {
        // Précalcul des cosinus
        for (int i = 0; i < 360; i++) {
            bCos[i] = int(1024 * cos(i / (180 / M_PI)));
        }

        // Précalcul des sinus
        for (int i = 0; i < 360; i++) {
            bSin[i] = int(1024 * sin(i / (180 / M_PI)));
        }

        // Précalcul des racines carrées
        for (int i = 0; i < 0xFFFF; i++) {
            bSqr[i] = char(sqrt(i));
        }
    }
};

static MathsInit init_;

int cosi(int scale, int angle) { return (scale * bCos[angle]) >> 10; }
int sini(int scale, int angle) { return (scale * bSin[angle]) >> 10; }
int sqrti(int x) { return bSqr[x]; }
