#ifndef FONT_H
#define FONT_H

#define _ASCII_CHARSET_SIZE 96
#define _ASCII_OFFSET 32
#define _ASCII_NEWLINE 0x0A // '\n'
#define _ASCII_UNKNOW 0x3F // '?'

//font
typedef struct SFont
{
	int tile_w;
	int tile_h;
	SDL_Texture* texture;
	SDL_Rect** tiles;

} SFont;

/**********/
SFont* FontInit(char* file);

void FontClose(SFont** font);

#endif
