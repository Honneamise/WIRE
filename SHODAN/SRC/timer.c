
#include "../shodan.h"

/**********/
STimer* TimerInit()
{
	STimer* timer = Calloc(1, sizeof(STimer));

	timer->start_ticks = 0;
	timer->pause_ticks = 0;
	timer->started = false;
	timer->paused = false;

	return timer;
}

/**********/
void TimerClose(STimer** timer)
{
	Free(*timer);

	*timer = NULL;
}

/**********/
void TimerStart(STimer* timer)
{
	timer->started = true;
	timer->paused = false;
	timer->start_ticks = SDL_GetTicks();
	timer->pause_ticks = 0;
}

/**********/
void TimerStop(STimer* timer)
{
	timer->started = false;
	timer->paused = false;
	timer->start_ticks = 0;
	timer->pause_ticks = 0;
}

/**********/
void TimerPause(STimer* timer)
{
	if (timer->started && !timer->paused)
	{
		timer->paused = true;
		timer->pause_ticks = SDL_GetTicks() - timer->start_ticks;
		timer->start_ticks = 0;
	}
}

/**********/
void TimerUnpause(STimer* timer)
{
	if (timer->started && timer->paused)
	{
		timer->paused = false;
		timer->start_ticks = SDL_GetTicks() - timer->pause_ticks;
		timer->pause_ticks = 0;
	}
}

/**********/
Uint32 TimerGet(STimer* timer)
{
	Uint32 time = 0;

	if (timer->started)
	{
		if (timer->paused)
		{
			time = timer->pause_ticks;
		}
		else
		{
			time = SDL_GetTicks() - timer->start_ticks;
		}
	}

	return time;
}

