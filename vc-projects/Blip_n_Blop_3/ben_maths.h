/******************************************************************
 *
 *
 *               ----------------
 *                  BenMaths.h
 *               ----------------
 *
 *
 *               Precomputed cos, sin and sqrt functions for integral values.
 *               Original comment claims that it brings 2000% to 2500% speedup.
 *               #TODO: HOW TRUE IS THAT IN 2019?
 *
 *               Prosper / LOADED -   V 0.1
 *
 *
 *
 ******************************************************************/

#pragma once

#ifndef M_PI
#define M_PI 3.141592654
#endif

// Angles must be in positive degrees. Computes scale * cos(angle)
int cosi(int scale, int angle);
int sini(int scale, int angle);
int sqrti(int x);
