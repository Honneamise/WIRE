#ifndef SOUND_H
#define SOUND_H

#define _AUDIO_FREQ 44100
#define _AUDIO_FORMAT AUDIO_S16LSB
#define _AUDIO_CHANNELS 2
#define _AUDIO_SAMPLES 4096

//sound
typedef struct SSound
{
	Uint32 len;
	Uint8* buf;

} SSound;

/**********/
SSound* SoundInit(char* file);

void SoundClose(SSound** sound);

#endif