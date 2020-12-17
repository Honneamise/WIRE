
#include "../shodan.h"

/**********/
SSound* SoundInit(char* file)
{
	SSound* sound = Calloc(1, sizeof(SSound));

	SDL_AudioSpec spec = { 0 };

	void* res = SDL_LoadWAV(file, &spec, &sound->buf, &sound->len);

	if (res == NULL) { Error(__func__, "%s", SDL_GetError()); }

	return sound;
}

/**********/
void SoundClose(SSound** sound)
{
	SDL_FreeWAV((*sound)->buf);

	Free(*sound);

	*sound = NULL;
}

