
#include "../shodan.h"

/**********/
SState* StateInit(char* name, void(*init)(), void(*input)(), void(*update)(), void(*draw)(), void(*close)())
{
	SState* state = Calloc(1, sizeof(SState));

	state->name = name;
	state->init = init;
	state->input = input;
	state->update = update;
	state->draw = draw;
	state->close = close;

	if (state->init != NULL) { state->init(); };

	return state;
}

/**********/
void StateClose(SState** state)
{
	if (state == NULL) { return; };

	if ((*state)->close != NULL) { (*state)->close(); };

	Free(*state);

	*state = NULL;
}

