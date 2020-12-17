#ifndef COLOR_H
#define COLOR_H

#define _BLACK	(SColor) {0x00,0x00,0x00,SDL_ALPHA_OPAQUE}
#define _WHITE	(SColor) {0xFF,0xFF,0xFF,SDL_ALPHA_OPAQUE}
#define _GREY	(SColor) {0x80,0x80,0x80,SDL_ALPHA_OPAQUE}
#define _RED	(SColor) {0xFF,0x00,0x00,SDL_ALPHA_OPAQUE}
#define _GREEN	(SColor) {0x00,0xFF,0x00,SDL_ALPHA_OPAQUE}
#define _BLUE	(SColor) {0x00,0x00,0xFF,SDL_ALPHA_OPAQUE}
#define _YELLOW	(SColor) {0xFF,0xFF,0x00,SDL_ALPHA_OPAQUE}
#define _ORANGE	(SColor) {0xFF,0x80,0x00,SDL_ALPHA_OPAQUE}

//color
typedef SDL_Color SColor;

/**********/
SColor* ColorInit(Uint8 r, Uint8 g, Uint8 b);

void ColorClose(SColor** color);

Uint8 ColorGetAlpha(SColor* color);

void ColorSetAlpha(SColor* color, Uint8 alpha);

#endif