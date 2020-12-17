#ifndef IMAGE_H
#define IMAGE_H

#define _IMAGE_FORMAT SDL_PIXELFORMAT_RGBA8888
#define _IMAGE_BYTES_PER_PIXEL 4
#define _IMAGE_R_FILTER 0.212671f
#define _IMAGE_G_FILTER 0.715160f
#define _IMAGE_B_FILTER 0.072169f

//image
typedef struct SImage
{
	int w;
	int h;
	SDL_Texture* texture;

} SImage;

/**********/
SImage* ImageInit(char* file);

SImage* ImageInitBW(char* file);

SImage* ImageInitAlpha(char* file, SColor* color);

void ImageClose(SImage** img);

void ImageSetBlend(SImage* img, Uint8 blend);

#endif