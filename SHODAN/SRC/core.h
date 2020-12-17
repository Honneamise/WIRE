#ifndef CORE_H
#define CORE_H

//core, do not expose
typedef struct SCore
{
	int width;
	int height;

	int event;
	int key;
	int mousex;
	int mousey;
	int button;
	int wheel;
	
	SDL_AudioSpec audio_spec;
	SDL_AudioDeviceID audio_device;

	struct SFont* font;

	int frames;
	struct STimer* timer;

	bool run;
	struct SState* change;
	struct SState* state;
	struct SArray* pool;

	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Texture* texture;

}SCore;

/**********/
//utils
int ShodanFps();

void ShodanPushMouseMotion();

//shodan core
void ShodanInit(int w, int h, bool screen, bool audio);

void ShodanClose();

void ShodanInfo();

void ShodanSleep(int delay);

//drawing
void ShodanBeginDraw();

void ShodanEndDraw();

void ShodanClear(SColor* color);

void ShodanSetColor(SColor* color);

void ShodanLine(int srcx, int srcy, int dstx, int dsty);

void ShodanRect(int x, int y, int w, int h);

void ShodanRectArea(int x, int y, int w, int h);

void ShodanCircle(int x, int y, int radius);

void ShodanCircleArea(int x, int y, int radius);

void ShodanPolygon(SPoly* poly);

void ShodanPolygonArea(SPoly* poly);

void ShodanImage(SImage* img, int x, int y);

void ShodanImageSized(SImage* img, int x, int y, int w, int h);

void ShodanImageRotated(SImage* img, int x, int y, int angle);

//text
void ShodanSetFont(SFont* font);

void ShodanText(char* string, int x, int y);

int ShodanTextWidth(char* string);

int ShodanTextHeight(char* string);

//audio
void ShodanPlay(SSound* sound);

//event
bool ShodanEvents();

void ShodanWaitKeyboard();

//state manager
void ShodanStart(char* name);

void ShodanStop();

void ShodanAddState(SState* state);

void ShodanSetState(char* name);

#endif
