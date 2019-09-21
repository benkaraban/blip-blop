/******************************************************************
*
*
*		----------------
*		  Picture.cpp
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



//-----------------------------------------------------------------------------
//		Headers
//-----------------------------------------------------------------------------

#include "graphics.h"
#include "picture.h"
#include "dd_gfx.h"
#include "ben_debug.h"


//-----------------------------------------------------------------------------
// Nom: Picture::Picture() - CONSTRUCTEUR -
// Desc: Initialise tout à 0
//-----------------------------------------------------------------------------

Picture::Picture() : surf(NULL), xspot(0), yspot(0), xsize(0), ysize(0)
{
}

//-----------------------------------------------------------------------------
// Nom: Picture::FindSize() - METHODE PRIVEE -
// Desc: Recherche la largeur et la hauteur de l'image et assigne
//		 ces deux valeurs à 'xsize' et 'ysize'
//-----------------------------------------------------------------------------

void Picture::FindSize()
{
	/*DDSURFACEDESC2	ddsd;

	ddsd.dwSize = sizeof(ddsd);
	ddsd.dwFlags = DDSD_HEIGHT | DDSD_WIDTH;

	if (surf->GetSurfaceDesc(&ddsd) != DD_OK) {
		debug << "Ne peut pas obtenir la DESC d'une surface! (Picture::FindSize)\n";
		return;
	}*/

	xsize = surf->Get()->w;
	ysize = surf->Get()->h;
}

//-----------------------------------------------------------------------------
// Nom: Picture::SetColorKey()
// Desc: Règle la couleur transparente de l'image
//-----------------------------------------------------------------------------

void Picture::SetColorKey(Pixel rgb)
{
	if (surf == NULL) {
		debug << "Picture::SetColorKey() - surface à NULL\n";
		return;
	}

	DDSetColorKey(surf, rgb);
}


//-----------------------------------------------------------------------------
// Nom: Picture::SetSpot()
// Desc: Règle les coordonnée du point chaud
//-----------------------------------------------------------------------------

void Picture::SetSpot(int x, int y)
{
	xspot = x;
	yspot = y;
}


//-----------------------------------------------------------------------------
// Nom: Picture::SetSurface()
// Desc: Assigne une surface et change les attributs de taille en conséquence
//-----------------------------------------------------------------------------

void Picture::SetSurface(SDL::Surface * s)
{
	surf = s;
	FindSize();
}

//-----------------------------------------------------------------------------
// Nom: Picture::LoadBMP()
// Desc: Charge une image BMP
//-----------------------------------------------------------------------------

void Picture::LoadBMP(char * file)
{
	surf = DDLoadBMP(file);
	FindSize();
	xspot = 0;
	yspot = 0;
}


//-----------------------------------------------------------------------------
// Nom: Picture::LoadBMP()
// Desc: Charge une image BMP. Les flags permettent de mettre l'image
//		 en mémoire VIDEO / SYSTEM / BEST
//-----------------------------------------------------------------------------

void Picture::LoadBMP(char * file, int flags)
{
	surf = DDLoadBMP(file, flags);
	FindSize();
	xspot = 0;
	yspot = 0;
}


//-----------------------------------------------------------------------------
// Nom: Picture::LoadBMP()
// Desc: Charge une image BMP et règle le point chaud
//-----------------------------------------------------------------------------

void Picture::LoadBMP(char * file, int xs, int ys)
{
	surf = DDLoadBMP(file);
	FindSize();
	xspot = xs;
	yspot = ys;
}


//-----------------------------------------------------------------------------
// Nom: Picture::LoadBMP()
// Desc: Charge une image BMP et règle le point chaud. Cette méthode
//		 utilise les mêmes flags que la mèthode surdéfinie ci-dessus
//-----------------------------------------------------------------------------

void Picture::LoadBMP(char * file, int xs, int ys, int flags)
{
	surf = DDLoadBMP(file, flags);
	FindSize();
	xspot = xs;
	yspot = ys;
}


//-----------------------------------------------------------------------------
// Nom: Picture::BlitTo()
// Desc: Effectue un blit pour afficher l'image sur la surface donnée.
//		 L'interêt de cette mèthode par rapport à un Blt simple est qu'elle
//		 utilise le point chaud et qu'elle permet d'afficher des images
//		 partielles lorsqu'une image est affichée trop prêt d'un bord
//		 de l'écran (Blt n'affiche rien dans ce cas).
//-----------------------------------------------------------------------------

void Picture::BlitTo(SDL::Surface * s, int x, int y) const
{
	x -= xspot;
	y -= yspot;

	int x2 = x + xsize;
	int y2 = y + ysize;


	// S'il n'y a rien à afficher, on se casse tout de suite!
	if (x > XPIC_MAX || x2 < 0 || y > YPIC_MAX || y2 < 0)
		return;

	Rect	r;

	r.left	= (x < 0) ? -x : 0;
	r.top	= (y < 0) ? -y : 0;
	r.right	= (x2 > XPIC_MAX) ? XPIC_MAX - x : xsize;
	r.bottom = (y2 > YPIC_MAX) ? YPIC_MAX - y : ysize;

	if (x < 0) x = 0;
	if (y < 0) y = 0;

	s->BltFast(x, y, surf, &r, DDBLTFAST_SRCCOLORKEY
	           | DDBLTFAST_WAIT);

	/*static int test_i = 1;
	char buf[128];
	sprintf(buf, "test/%d.bmp", test_i);
	SDL_SaveBMP(surf->Get(), buf);
	test_i++;*/

}

//-----------------------------------------------------------------------------
// Nom: Picture::PasteTo()
// Desc: Effectue un blit pour afficher l'image sur la surface donnée.
//		 L'interêt de cette mèthode par rapport à un Blt simple est qu'elle
//		 utilise le point chaud et qu'elle permet d'afficher des images
//		 partielles lorsqu'une image est affichée trop prêt d'un bord
//		 de l'écran (Blt n'affiche rien dans ce cas).
//-----------------------------------------------------------------------------

void Picture::PasteTo(SDL::Surface * s, int x, int y) const
{
	x -= xspot;
	y -= yspot;

	int x2 = x + xsize;
	int y2 = y + ysize;


	// S'il n'y a rien à afficher, on se casse tout de suite!
	if (x > XPIC_MAX || x2 < 0 || y > YPIC_MAX || y2 < 0)
		return;

	Rect	r;

	r.left	= (x < 0) ? -x : 0;
	r.top	= (y < 0) ? -y : 0;
	r.right	= (x2 > XPIC_MAX) ? XPIC_MAX - x : xsize;
	r.bottom = (y2 > YPIC_MAX) ? YPIC_MAX - y : ysize;

	if (x < 0) x = 0;
	if (y < 0) y = 0;

	s->BltFast(x, y, surf, &r, DDBLTFAST_NOCOLORKEY
	           | DDBLTFAST_WAIT);
}


//-----------------------------------------------------------------------------
// Nom: Picture::Close()
// Desc: Ferme le tout (en particulier la surface)
//-----------------------------------------------------------------------------

void Picture::Close()
{
	if (surf != NULL)
		surf->Release();
	surf = NULL;
}

//-----------------------------------------------------------------------------
// Nom: Picture::~Picture() - DESTRUCTEUR -
// Desc: Appelle Close()
//-----------------------------------------------------------------------------

Picture::~Picture()
{
	Close();
}

//-----------------------------------------------------------------------------
// Nom: loadPBK
// Desc: Charge le fichier PBK 'fic', remplit le tableau 'p' avec la
//		 couleur 'rgb', et renvoit la taille de la PBK
//-----------------------------------------------------------------------------

int loadPBK(char * fic, Picture * & p, int rgb)
{
    std::ifstream f;
	int			nbpic;

	if (p != NULL) {
		debug << "loadPBK/Picture.cpp->" << fic << ":tableau déjà initialisé\n";
		return 0;
	}

	f.open(fic);

	if (f.is_open() == 0) {
		debug << "LoadPBK/Picture.cpp->Ne peut pas ouvrir " << fic << "\n";
		return 0;
	}

	f >> nbpic;

	if (nbpic < 1) {
		debug << "LoadPBK(Picture.cpp)->Fichier " << fic << " corrompu!\n";
		nbpic = 0;
		return 0;
	}

	p = new Picture[nbpic];

	char	txt[256];
	int		x;
	int		y;
	int		n;

	for (int i = 0; i < nbpic; i++) {
		f >> n;
		f >> txt;
		f >> x;
		f >> y;

		p[n].LoadBMP(txt, x, y);
		p[n].SetColorKey(rgb);
	}

	f.close();

	return nbpic;
}

//-----------------------------------------------------------------------------
// Nom: closePBK
// Desc: Ferme une PBK (il faut préciser la taille)
//-----------------------------------------------------------------------------

void closePBK(Picture * & p, int t)
{
	if (p != NULL) {
		for (int i = 0; i < t; i++)
			p[i].Close();
		delete [] p;
	}
}
