
#ifndef _WIN_LGX_
#define _WIN_LGX_

#define LGX_RMAX_0	31
#define	LGX_GMAX_0	63
#define	LGX_BMAX_0	31

#define	LGX_RDECAL_0	11
#define	LGX_GDECAL_0	5
#define	LGX_BDECAL_0	0

#define LGX_RMAX_1	31
#define	LGX_GMAX_1	31
#define	LGX_BMAX_1	31

#define	LGX_RDECAL_1	10
#define	LGX_GDECAL_1	5
#define	LGX_BDECAL_1	0

struct LGX_HEADER
{
	char			id[3];
	char			version;
	unsigned short	xsize;
	unsigned short	ysize;
	unsigned short	depth;
};


bool createLGX_0( HDC hdc, const char * fic, int xs, int ys);
bool createLGX_1( HDC hdc, const char * fic, int xs, int ys);

int createLGX_0( HDC hdc, int xs, int ys, void * & ptr);
int createLGX_1( HDC hdc, int xs, int ys, void * & ptr);


#endif