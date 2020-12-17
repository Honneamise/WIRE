
#include "../shodan.h"

/**********/
SFont* FontInit(char* file)
{
	SFont* font = Calloc(1, sizeof(SFont));

	SDL_Surface* s = SDL_LoadBMP(file);

	if (s == NULL) { Error(__func__, "%s", SDL_GetError()); }

	else
	{
		SDL_Surface* surface = SDL_ConvertSurfaceFormat(s, _IMAGE_FORMAT, 0); 

		font->texture = SDL_CreateTextureFromSurface(Shodan->renderer, surface);

		SDL_SetTextureBlendMode(font->texture, SDL_BLENDMODE_BLEND);

		font->tile_w = (int)(surface->w / _ASCII_CHARSET_SIZE);
		font->tile_h = surface->h;

		font->tiles = Calloc(_ASCII_CHARSET_SIZE, sizeof(SDL_Rect*));

		for (int k = 0; k < _ASCII_CHARSET_SIZE; k++)
		{
			font->tiles[k] = Calloc(1, sizeof(SDL_Rect));

			font->tiles[k]->x = font->tile_w * k;
			font->tiles[k]->y = 0;
			font->tiles[k]->w = font->tile_w;
			font->tiles[k]->h = font->tile_h;
		};

		SDL_FreeSurface(surface);
		SDL_FreeSurface(s);
	}

	return font;
}

/**********/
void FontClose(SFont** font)
{
	SDL_DestroyTexture((*font)->texture);

	for (int i = 0; i < _ASCII_CHARSET_SIZE; i++)
	{
		Free((*font)->tiles[i]);
	};

	Free((*font)->tiles);

	Free(*font);

	*font = NULL;
}
