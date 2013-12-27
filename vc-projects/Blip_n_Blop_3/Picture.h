/******************************************************************
*
*
*		----------------
*		  Picture.h
*		----------------
*
*		Classe Picture
*
*		La classe Picture représente les images
*		utilisées par les sprites. Elles possèdent
*		un point chaud pour permettre de mieux les
*		gérer et permettent d'afficher des surfaces
*		en bordure d'écran.
*
*
*		Prosper / LOADED -   V 0.2
*
*
*
******************************************************************/

#ifndef _Picture_
#define _Picture_

//-----------------------------------------------------------------------------
//		Headers
//-----------------------------------------------------------------------------

// #include <ddraw.h>
#include "DD_gfx.h"

//-----------------------------------------------------------------------------
//		Constantes pour la gestion de l'affichage
//-----------------------------------------------------------------------------

#define	XPIC_MAX	640		// Représente la largeur de la Primary Surface
#define YPIC_MAX	480		// Représente la hauteur de la Primary Surface

//-----------------------------------------------------------------------------
//		Définition de la classe Picture
//-----------------------------------------------------------------------------

class Picture
{
private:
	IDirectDrawSurface7 *	surf;	// Surface contenant l'image
	int			xsize;				// Largeur de l'image
	int			ysize;				// Hauteur de l'image
	int			xspot;				// X du point chaud
	int			yspot;				// Y du point chaud

	void FindSize();

public:
	Picture();

	inline int xSize() const { return xsize;};
	inline int ySize() const { return ysize;};
	inline int xSpot() const { return xspot;};
	inline int ySpot() const { return yspot;};
	inline IDirectDrawSurface7 * Surf() const { return surf;};

	void SetSpot( int x, int y);
	void SetColorKey( COLORREF rgb);
	void SetSurface( IDirectDrawSurface7 * s);

	void LoadBMP( char * file);
	void LoadBMP( char * file, int flags);
	void LoadBMP( char * file, int xs, int ys);
	void LoadBMP( char * file, int xs, int ys, int flags);
	void LoadLGX( char * file, int xs = 0, int ys = 0, int flags = 0);
	void PasteTo( IDirectDrawSurface7 *s, int x, int y) const;
	void BlitTo( IDirectDrawSurface7 *s, int x, int y) const;
	void Close();

	~Picture();

};


//-----------------------------------------------------------------------------
//		Fonctions permettant de bien gérer les PBK
//-----------------------------------------------------------------------------

int loadPBK(char * fic, Picture * & p, int rgb);
void closePBK(Picture * & p, int t);



#endif
