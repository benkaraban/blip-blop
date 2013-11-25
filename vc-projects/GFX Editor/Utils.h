#include <iostream>
#include <string>

#include <Windows.h>

#include "winLGX.h"

using namespace std;

typedef struct {
	int width;
	int height;
	unsigned char *data;
	size_t size;
} ppm_image;

bool dirExists(const std::string& dirName_in);

size_t ppm_save(ppm_image *img, FILE *outfile);

unsigned char* convertLGX0ToRGB(unsigned char* bytes, int size);

unsigned char* convertLGX1ToRGB(unsigned char* bytes, int size, int w, int h);