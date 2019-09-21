#include "bulle.h"

#include "ben_maths.h"

Bulle::Bulle() : phi(0) {}

void Bulle::update() {
    phi += dphi;
    phi %= 360;

    y += dy;

    x = xbase + cosi(10, phi);

    if (xbase < offset - 10 || y < -10 || mur_opaque(x, y)) a_detruire = true;
}
