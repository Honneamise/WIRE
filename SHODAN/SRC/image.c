
#include "../shodan.h"

/**********/
SImage* ImageInit(char* file)
{
	SImage* img = Calloc(1, sizeof(SImage));

	SDL_Surface* s = SDL_LoadBMP(file);

	if (s == NULL) { Error(__func__, "%s", SDL_GetError()); }

	else
	{
		SDL_Surface* surface = SDL_ConvertSurfaceFormat(s, _IMAGE_FORMAT, 0);

		img->texture = SDL_CreateTextureFromSurface(Shodan->renderer, surface);

		SDL_SetTextureBlendMode(img->texture, SDL_BLENDMODE_BLEND);

		img->w = surface->w;
		img->h = surface->h;

		SDL_FreeSurface(surface);
		SDL_FreeSurface(s);

	}

	return img;
}

/**********/
/* adapeted from : https://gigi.nullneuron.net/gigilabs/converting-an-image-to-grayscale-using-sdl2/ */
SImage* ImageInitBW(char* file)
{
	SImage* img = Calloc(1, sizeof(SImage));

	SDL_Surface* s = SDL_LoadBMP(file);

	if (s == NULL) { Error(__func__, "%s", SDL_GetError()); }

	else
	{
		SDL_Surface* surface = SDL_ConvertSurfaceFormat(s, _IMAGE_FORMAT, 0);

		img->texture = SDL_CreateTexture(Shodan->renderer, _IMAGE_FORMAT, SDL_TEXTUREACCESS_STATIC, surface->w, surface->h);

		Uint32* pixels = (Uint32*)surface->pixels;

		for (int counter = 0; counter < surface->h * surface->w; counter++)
		{
			Uint32 pixel = pixels[counter];

			Uint8 r = (Uint8)(pixel >> 24) & 0xFF;
			Uint8 g = (Uint8)(pixel >> 16) & 0xFF;
			Uint8 b = (Uint8)(pixel >> 8) & 0xFF;
			Uint8 a = (Uint8)(pixel >> 0) & 0xFF;

			Uint8 v = (Uint8)(r * _IMAGE_R_FILTER + g * _IMAGE_G_FILTER + b * _IMAGE_B_FILTER);

			pixel = (v << 24) | (v << 16) | (v << 8) | a;

			pixels[counter] = pixel;
		}

		SDL_UpdateTexture(img->texture, NULL, surface->pixels, surface->w * _IMAGE_BYTES_PER_PIXEL);

		SDL_SetTextureBlendMode(img->texture, SDL_BLENDMODE_BLEND);

		img->w = surface->w;
		img->h = surface->h;

		SDL_FreeSurface(surface);
		SDL_FreeSurface(s);

	}

	return img;
}

/**********/
SImage* ImageInitAlpha(char* file, SColor* color)
{
	SImage* img = Calloc(1, sizeof(SImage));

	SDL_Surface* s = SDL_LoadBMP(file);

	if (s == NULL) { Error(__func__, "%s", SDL_GetError()); }

	else
	{
		SDL_Surface* surface = SDL_ConvertSurfaceFormat(s, _IMAGE_FORMAT, 0);

		SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, color->r, color->g, color->b));

		img->texture = SDL_CreateTextureFromSurface(Shodan->renderer, surface);

		SDL_SetTextureBlendMode(img->texture, SDL_BLENDMODE_BLEND);

		img->w = surface->w;
		img->h = surface->h;

		SDL_FreeSurface(surface);
		SDL_FreeSurface(s);
	}

	return img;
}

/**********/
void ImageClose(SImage** img)
{
	SDL_DestroyTexture((*img)->texture);

	Free(*img);

	*img = NULL;
}

/**********/
void ImageSetBlend(SImage* img, Uint8 blend)
{
	SDL_SetTextureAlphaMod(img->texture, blend);
}

