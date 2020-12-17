#ifndef MACROS_H
#define MACROS_H

//version
#define SHODAN_VERSION "OTTOBRE 2020"

//core
#define WIDTH	Shodan->width
#define HEIGHT	Shodan->height
#define EVENT	Shodan->event
#define KEY		Shodan->key
#define MOUSEX	Shodan->mousex
#define MOUSEY	Shodan->mousey
#define BUTTON	Shodan->button
#define WHEEL	Shodan->wheel
#define FPS		ShodanFps()

//event types
#define NONE		   -1 
#define QUIT		    0
#define KEYPRESS	    1
#define KEYRELEASE	    2
#define MOUSEMOVE	    3
#define MOUSEPRESS	    4
#define MOUSERELEASE	5
#define MOUSEWHEEL	    6

//button
#define B_LEFT	SDL_BUTTON_LEFT
#define B_MID	SDL_BUTTON_MIDDLE
#define B_RIGHT SDL_BUTTON_RIGHT

//wheel
#define W_UP    0
#define W_DOWN  1

//common keys
#define ESC			SDLK_ESCAPE
#define ENTER		SDLK_RETURN
#define CANCEL		SDLK_DELETE
#define BACKSPACE	SDLK_BACKSPACE
#define SPACE		SDLK_SPACE

#define PLUS	SDLK_KP_PLUS
#define MINUS	SDLK_KP_MINUS

#define UP		SDLK_UP
#define DOWN	SDLK_DOWN
#define LEFT	SDLK_LEFT
#define RIGHT	SDLK_RIGHT

#define F1	SDLK_F1
#define F2	SDLK_F2
#define F3	SDLK_F3
#define F4	SDLK_F4
#define F5	SDLK_F5
#define F6	SDLK_F6
#define F7	SDLK_F7
#define F8	SDLK_F8
#define F9	SDLK_F9
#define F10 SDLK_F10
#define F11 SDLK_F11
#define F12 SDLK_F12

//common colors
#define BLACK	(SColor*) &_BLACK
#define WHITE	(SColor*) &_WHITE
#define GREY	(SColor*) &_GREY
#define RED	    (SColor*) &_RED
#define GREEN	(SColor*) &_GREEN
#define BLUE	(SColor*) &_BLUE
#define YELLOW	(SColor*) &_YELLOW
#define ORANGE	(SColor*) &_ORANGE

#endif