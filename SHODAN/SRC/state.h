#ifndef STATE_H
#define STATE_H

//state
typedef struct SState
{
	char* name;
	void(*init)();
	void(*input)();
	void(*update)();
	void(*draw)();
	void(*close)();

}SState;

/**********/
SState* StateInit(char* name, void(*init)(), void(*input)(), void(*update)(), void(*draw)(), void(*close)());

void StateClose(SState** state);

#endif