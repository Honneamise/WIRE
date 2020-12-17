#ifndef TIMER_H
#define TIMER_H

//timer
typedef struct STimer
{
	Uint32 start_ticks;
	Uint32 pause_ticks;
	bool paused;
	bool started;

} STimer;

/**********/
STimer* TimerInit();

void TimerClose(STimer** timer);

void TimerStart(STimer* timer);

void TimerStop(STimer* timer);

void TimerPause(STimer* timer);

void TimerUnpause(STimer* timer);

Uint32 TimerGet(STimer* timer);

#endif