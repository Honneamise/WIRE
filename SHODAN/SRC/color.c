
#include "../shodan.h"

/*********/
SColor* ColorInit(Uint8 r, Uint8 g, Uint8 b)
{
	SColor* color = Calloc(1, sizeof(SColor));

	color->r = r;
	color->g = g;
	color->b = b;
	color->a = SDL_ALPHA_OPAQUE;

	return color;
}

/*********/
void ColorClose(SColor** color)
{
	Free(*color);

	*color = NULL;
}

/*********/
Uint8 ColorGetAlpha(SColor* color)
{
	return color->a;
}

/*********/
void ColorSetAlpha(SColor* color, Uint8 alpha)
{
	color->a = alpha;
}

