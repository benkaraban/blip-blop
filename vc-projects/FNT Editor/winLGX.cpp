#include "stdafx.h"
#include "winLGX.h"


bool createLGX_0( HDC hdc, const char * fic, int xs, int ys)
{
	void *	ptr;
	FILE *	f;
	int		taille;

	if ((taille=createLGX_0( hdc, xs, ys, ptr)) == 0 || ptr == NULL)
		return false;

	if ((f=fopen( fic, "wb")) == NULL)
	{
		return false;
	}

	fwrite( ptr, 1, taille, f);
	fclose( f);

	free( ptr);

	return true;
}

bool createLGX_1( HDC hdc, const char * fic, int xs, int ys)
{
	void *	ptr;
	FILE *	f;
	int		taille;

	if ((taille=createLGX_1( hdc, xs, ys, ptr)) == 0 || ptr == NULL)
		return false;

	if ((f=fopen( fic, "wb")) == NULL)
	{
		return false;
	}

	fwrite( ptr, 1, taille, f);
	fclose( f);

	free( ptr);

	return true;
}



int createLGX_0( HDC hdc, int xs, int ys, void * & ptr)
{
	unsigned int	pixval;
	int				rval;
	int				gval;
	int				bval;

	unsigned char*	ptrd;	// Pointeur sur les données
	LGX_HEADER *	lh;
	int				taille = xs*ys*2+sizeof(LGX_HEADER);

	ptr = malloc(taille);
	if ( ptr == NULL)
	{
		return 0;
	}

	lh = (LGX_HEADER *) ptr;

	lh->id[0] = 'L';
	lh->id[1] = 'G';
	lh->id[2] = 'X';
	lh->version = 0;
	lh->xsize = xs;
	lh->ysize = ys;
	lh->depth = 16;

	ptrd = (unsigned char*)ptr+sizeof(LGX_HEADER);

	// Remarque : bizarrement, les couleurs sont données dans l'ordre BGR
	// et pas RGB, bien que ce ne soit pas le cas de D3D (???)

	int		x = 0;
	int		y = 0;

	taille = 0; // Now, taille va valoir la taille effective du fichier

	while ( y<ys)
	{
		pixval = GetPixel( hdc, x, y);


		// On convertit la valeur RGB au format LGX
		
		rval = ((pixval & 0xFF) * LGX_RMAX_0)/0xFF;
		gval = (((pixval>>8) & 0xFF) * LGX_GMAX_0)/0xFF;
		bval = (((pixval>>16) & 0xFF) * LGX_BMAX_0)/0xFF;


		taille++;		// 1 mot inscrit


		*((unsigned short*)ptrd) = unsigned short((rval<<LGX_RDECAL_0) | (gval<<LGX_GDECAL_0) | (bval<<LGX_BDECAL_0));
		ptrd += 2;

		x++;

		if ( x == xs)
		{
			x = 0;
			y++;
		}

	}

	return ((taille<<1)+sizeof(LGX_HEADER)); // Il faut * taille par 2 car on a compté les mots
}

int createLGX_1( HDC hdc, int xs, int ys, void * & ptr)
{
	unsigned int	pixval;
	unsigned short	LGXpixval;
	unsigned short	LGXpixval2;
	int				rval;
	int				gval;
	int				bval;

	unsigned char*	ptrd;	// Pointeur sur les données
	LGX_HEADER *	lh;
	int				taille = xs*ys*2+sizeof(LGX_HEADER);

	ptr = malloc(taille);
	if ( ptr == NULL)
	{
		return 0;
	}

	lh = (LGX_HEADER *) ptr;

	lh->id[0] = 'L';
	lh->id[1] = 'G';
	lh->id[2] = 'X';
	lh->version = 1;
	lh->xsize = xs;
	lh->ysize = ys;
	lh->depth = 16;

	ptrd = (unsigned char*)ptr+sizeof(LGX_HEADER);

	// Remarque : bizarrement, les couleurs sont données dans l'ordre BGR
	// et pas RGB, bien que ce ne soit pas le cas de D3D (???)

	int		x = 0;
	int		y = 0;
	unsigned short		cpt;

	taille = 0; // Now, taille va valoir la taille effective du fichier

	while ( y<ys)
	{
		pixval = GetPixel( hdc, x, y);

		rval = ((pixval & 0xFF) * LGX_RMAX_1)/0xFF;
		gval = (((pixval>>8) & 0xFF) * LGX_GMAX_1)/0xFF;
		bval = (((pixval>>16) & 0xFF) * LGX_BMAX_1)/0xFF;

		LGXpixval = unsigned short((rval<<LGX_RDECAL_1) | (gval<<LGX_GDECAL_1) | (bval<<LGX_BDECAL_1));

		cpt = 0;
		
		do{

			x++;

			if ( x == xs)
			{
				x = 0;
				y++;
			}

			cpt++;

			pixval = GetPixel( hdc, x, y);

			rval = ((pixval & 0xFF) * LGX_RMAX_1)/0xFF;
			gval = (((pixval>>8) & 0xFF) * LGX_GMAX_1)/0xFF;
			bval = (((pixval>>16) & 0xFF) * LGX_BMAX_1)/0xFF;

			LGXpixval2 = unsigned short((rval<<LGX_RDECAL_1) | (gval<<LGX_GDECAL_1) | (bval<<LGX_BDECAL_1));


		}while ( y < ys && LGXpixval == LGXpixval2 && cpt < 0x7FFF);




		if ( cpt >= 2)
		{
			*((unsigned short*)ptrd) = unsigned short(unsigned short(0x8000) | cpt);
			ptrd += 2;
			taille += 2;	// 2 mots inscrits
		}
		else
		{
			taille++;		// 1 mot inscrit
		}


		// Dans tous les cas on fait ça...
		*((unsigned short*)ptrd) = LGXpixval;
		ptrd += 2;

	
	}

	return ((taille<<1)+sizeof(LGX_HEADER)); // Il faut * taille par 2 car on a compté les mots
}
