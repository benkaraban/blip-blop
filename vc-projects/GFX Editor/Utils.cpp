#include "StdAfx.h"

#include "Utils.h"

bool dirExists(const std::string& dirName_in)
{
	DWORD ftyp = GetFileAttributesA(dirName_in.c_str());
	if (ftyp == INVALID_FILE_ATTRIBUTES)
		return false;  //something is wrong with your path!

	if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
		return true;   // this is a directory!

	return false;    // this is not a directory!
}

size_t ppm_save(ppm_image *img, FILE *outfile) {
	size_t n = 0;
	n += fprintf(outfile, "P6\n%d %d\n%d\n",
		img->width, img->height, 0xFF);
	n += fwrite(img->data, 1, img->width * img->height * 3, outfile);
	return n;
}

unsigned char* convertLGX0ToRGB(unsigned char* bytes, int size)
{
	int newsize = size*1.5;
	unsigned char* ret = new unsigned char[newsize];
	unsigned char *dest = ret;

	unsigned char *pt = bytes;

	/*
	rval = ((pixval & 0xFF) * LGX_RMAX_0)/0xFF;
	gval = (((pixval>>8) & 0xFF) * LGX_GMAX_0)/0xFF;
	bval = (((pixval>>16) & 0xFF) * LGX_BMAX_0)/0xFF;


	taille++;		// 1 mot inscrit


	*((unsigned short*)ptrd) = unsigned short((rval<<LGX_RDECAL_0) | (gval<<LGX_GDECAL_0) | (bval<<LGX_BDECAL_0));
	ptrd += 2;
	*/
	for (int i = 0; i < size; i += 2)
	{
		unsigned short val = *(unsigned short *)pt;

		unsigned char r = ((float)((val >> LGX_RDECAL_0)&LGX_RMAX_0)) / LGX_RMAX_0 * 255.0;
		unsigned char g = ((float)((val >> LGX_GDECAL_0)&LGX_GMAX_0)) / LGX_GMAX_0 * 255.0;
		unsigned char b = ((float)((val >> LGX_BDECAL_0)&LGX_BMAX_0)) / LGX_BMAX_0 * 255.0;

		dest[0] = r;
		dest[1] = g;
		dest[2] = b;

		pt += 2;
		dest += 3;
	}
	return ret;
}

unsigned char* convertLGX1ToRGB(unsigned char* bytes, int size, int w,int h)
{
	int newsize = w*h*3;
	unsigned char* ret = new unsigned char[newsize];
	unsigned char *dest = ret;

	unsigned char *pt = bytes;

	/*
	rval = ((pixval & 0xFF) * LGX_RMAX_0)/0xFF;
	gval = (((pixval>>8) & 0xFF) * LGX_GMAX_0)/0xFF;
	bval = (((pixval>>16) & 0xFF) * LGX_BMAX_0)/0xFF;


	taille++;		// 1 mot inscrit


	*((unsigned short*)ptrd) = unsigned short((rval<<LGX_RDECAL_0) | (gval<<LGX_GDECAL_0) | (bval<<LGX_BDECAL_0));
	ptrd += 2;
	*/
	while (pt<(bytes+size))
	{
		unsigned short val = *(unsigned short *)pt;

		if (val & 0x8000)
		{
			int rep = val & 0x7FFF;
			pt += 2;
			for (int k = 0; k < rep; k++)
			{
				unsigned short val2 = *(unsigned short *)pt;

				unsigned char r = ((float)((val2 >> LGX_RDECAL_1)&LGX_RMAX_1)) / LGX_RMAX_1 * 255.0;
				unsigned char g = ((float)((val2 >> LGX_GDECAL_1)&LGX_GMAX_1)) / LGX_GMAX_1 * 255.0;
				unsigned char b = ((float)((val2 >> LGX_BDECAL_1)&LGX_BMAX_1)) / LGX_BMAX_1 * 255.0;

				dest[0] = r;
				dest[1] = g;
				dest[2] = b;

				dest += 3;
			}
			pt += 2;
		}
		else
		{
			unsigned char r = ((float)((val >> LGX_RDECAL_1)&LGX_RMAX_1)) / LGX_RMAX_1 * 255.0;
			unsigned char g = ((float)((val >> LGX_GDECAL_1)&LGX_GMAX_1)) / LGX_GMAX_1 * 255.0;
			unsigned char b = ((float)((val >> LGX_BDECAL_1)&LGX_BMAX_1)) / LGX_BMAX_1 * 255.0;

			dest[0] = r;
			dest[1] = g;
			dest[2] = b;

			pt += 2;
			dest += 3;
		}
	}
	return ret;
}