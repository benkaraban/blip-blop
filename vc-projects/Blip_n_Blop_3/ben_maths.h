/******************************************************************
 *
 *
 *               ----------------
 *                  BenMaths.h
 *               ----------------
 *
 *
 *               Fonctions mathématiques précalculée
 *               Gain approximatif : 2000 à 2500%
 *               #TODO: HOW TRUE IS THAT IN 2019?
 *
 *               Cf. BenMaths.cpp pour plus d'infos
 *
 *               Prosper / LOADED -   V 0.1
 *
 *
 *
 ******************************************************************/

#pragma once

//-----------------------------------------------------------------------------
//              Constantes
//-----------------------------------------------------------------------------

#ifndef PI
#define PI 3.141592654  // C'est PI, utilisé pour la conversion
#endif                  // depgrés<->radians

void preCalcMathsFunctions();

// Angles must be in positive degrees. Computes scale * cos(angle)
int cosi(int scale, int angle);
int sini(int scale, int angle);
int sqrti(int x);
