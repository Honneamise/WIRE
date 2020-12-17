
#include "../shodan.h"

/**********/
int ShodanFps()
{
	if (Shodan->frames == 0) { return 0; };

	float fps = Shodan->frames / (TimerGet(Shodan->timer) / 1000.0f);

	if (fps > 100000.0f) { return 0; };

	return (int)fps;
}

/**********/
void ShodanPushMouseMotion()
{
	int x = 0;
	int y = 0;

	SDL_Event event;

	SDL_GetMouseState(&x, &y);

	event.type = SDL_MOUSEMOTION;
	event.motion.x = x;
	event.motion.y = y;

	SDL_PushEvent(&event);
}

/**********/
void ShodanInit(int w, int h, bool screen, bool audio)
{
#if defined(_MSC_VER) && defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDOUT);
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
	Log(__func__, "Memory leaks debug enabled");
#endif

	Shodan = Calloc(1, sizeof(SCore));

	Shodan->width = w;
	Shodan->height = h;

	Shodan->event = NONE;
	Shodan->key = NONE;
	Shodan->mousex = 0;
	Shodan->mousey = 0;
	Shodan->button = NONE;

	Shodan->font = NULL;

	Shodan->frames = 0;
	Shodan->timer = TimerInit();

	Shodan->run = false;
	Shodan->change = NULL;
	Shodan->state = NULL;
	Shodan->pool = ArrayInit();

	if (SDL_Init(SDL_INIT_VIDEO) < 0) { Error(__func__, "%s", SDL_GetError()); };

	if (screen)
	{
		Shodan->window = SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_SHOWN);
	}
	else
	{
		Shodan->window = SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_SHOWN);
	}

	if (Shodan->window == NULL) { Error(__func__, "%s", SDL_GetError()); };

	Shodan->renderer = SDL_CreateRenderer(Shodan->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (Shodan->renderer == NULL) { Error(__func__, "%s", SDL_GetError()); };

	if (SDL_RenderSetLogicalSize(Shodan->renderer, w, h) < 0) { Error(__func__, "%s", SDL_GetError()); };

	Shodan->texture = SDL_CreateTexture(Shodan->renderer, _IMAGE_FORMAT, SDL_TEXTUREACCESS_TARGET, w, h);

	if (Shodan->texture == NULL) { Error(__func__, "%s", SDL_GetError()); };

	SDL_SetRenderDrawColor(Shodan->renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

	SDL_SetRenderDrawBlendMode(Shodan->renderer, SDL_BLENDMODE_BLEND);

	ShodanPushMouseMotion();

	srand((unsigned int)time(NULL));

	//audio
	if (audio)
	{
		SDL_InitSubSystem(SDL_INIT_AUDIO);

		Shodan->audio_spec.freq = _AUDIO_FREQ;
		Shodan->audio_spec.format = _AUDIO_FORMAT;
		Shodan->audio_spec.channels = _AUDIO_CHANNELS;
		Shodan->audio_spec.samples = _AUDIO_SAMPLES;

		Shodan->audio_device = SDL_OpenAudioDevice(NULL, 0, &Shodan->audio_spec, NULL, 0);

		if (Shodan->audio_device == 0) { Error(__func__, "%s", SDL_GetError()); }

		SDL_PauseAudioDevice(Shodan->audio_device, 0);
	}
}

/**********/
void ShodanClose()
{
	TimerClose(&Shodan->timer);

	ArrayClose(&Shodan->pool);

	SDL_DestroyTexture(Shodan->texture);

	SDL_DestroyRenderer(Shodan->renderer);

	SDL_DestroyWindow(Shodan->window);

	SDL_CloseAudioDevice(Shodan->audio_device);

	SDL_Quit();

	Free(Shodan);

	Shodan = NULL;

}

/**********/
void ShodanInfo()
{
	Log(__func__, "Shodan version : %s", SHODAN_VERSION);

	Log(__func__, "CPU logical cores : %d", SDL_GetCPUCount());

	Log(__func__, "System RAM : %d", SDL_GetSystemRAM());

	Log(__func__, "Platform : %s", SDL_GetPlatform());

	SDL_RendererInfo info;
	if (SDL_GetRendererInfo(Shodan->renderer, &info) != 0) { Error(__func__, "%s", SDL_GetError()); };

	Log(__func__, "Driver : %s", info.name);

	int disp = SDL_GetWindowDisplayIndex(Shodan->window);

	SDL_DisplayMode mode;

	if (SDL_GetCurrentDisplayMode(disp, &mode) != 0) { Error(__func__, "%s", SDL_GetError()); };

	Log(__func__, "Display : %dx%d %dhz %dbpp", mode.w, mode.h, mode.refresh_rate, SDL_BITSPERPIXEL(mode.format));

	SDL_version compiled;
	SDL_VERSION(&compiled);

	Log(__func__, "SDL compiled : %d.%d.%d", compiled.major, compiled.minor, compiled.patch);

	SDL_version linked;
	SDL_GetVersion(&linked);

	Log(__func__, "SDL linked : %d.%d.%d", linked.major, linked.minor, linked.patch);

}

/**********/
void ShodanSleep(int delay)
{
	SDL_Delay(delay);
	Shodan->frames = 0;
	TimerStart(Shodan->timer);
}

/**********/
void ShodanBeginDraw()
{
	Shodan->frames++;

	SDL_SetRenderTarget(Shodan->renderer, Shodan->texture);
}

/**********/
void ShodanEndDraw()
{
	SDL_SetRenderTarget(Shodan->renderer, NULL);

	SDL_RenderCopy(Shodan->renderer, Shodan->texture, NULL, NULL);

	SDL_RenderPresent(Shodan->renderer);
}

/**********/
void ShodanClear(SColor* color)
{
	SDL_SetRenderDrawColor(Shodan->renderer, color->r, color->g, color->b, color->a);

	SDL_RenderClear(Shodan->renderer);
}

/**********/
void ShodanSetColor(SColor* color)
{
	SDL_SetRenderDrawColor(Shodan->renderer, color->r, color->g, color->b, color->a);
}

/**********/
void ShodanLine(int srcx, int srcy, int dstx, int dsty)
{
	SDL_RenderDrawLine(Shodan->renderer, srcx, srcy, dstx, dsty);
}

/**********/
void ShodanRect(int x, int y, int w, int h)
{
	SDL_Rect rect = { x, y, w, h };

	SDL_RenderDrawRect(Shodan->renderer, &rect);
}

/**********/
void ShodanRectArea(int x, int y, int w, int h)
{
	SDL_Rect rect = { x, y, w, h };

	SDL_RenderFillRect(Shodan->renderer, &rect);
}

/**********/
/* adapted from : https://gist.github.com/Gumichan01/332c26f6197a432db91cc4327fcabb1c */
void ShodanCircle(int x, int y, int radius)
{
	int offsetx, offsety, d;

	offsetx = 0;
	offsety = radius;
	d = radius - 1;

	while (offsety >= offsetx)
	{
		SDL_RenderDrawPoint(Shodan->renderer, x + offsetx, y + offsety);
		SDL_RenderDrawPoint(Shodan->renderer, x + offsety, y + offsetx);
		SDL_RenderDrawPoint(Shodan->renderer, x - offsetx, y + offsety);
		SDL_RenderDrawPoint(Shodan->renderer, x - offsety, y + offsetx);
		SDL_RenderDrawPoint(Shodan->renderer, x + offsetx, y - offsety);
		SDL_RenderDrawPoint(Shodan->renderer, x + offsety, y - offsetx);
		SDL_RenderDrawPoint(Shodan->renderer, x - offsetx, y - offsety);
		SDL_RenderDrawPoint(Shodan->renderer, x - offsety, y - offsetx);

		if (d >= 2 * offsetx)
		{
			d -= 2 * offsetx + 1;
			offsetx += 1;
		}
		else if (d < 2 * (radius - offsety))
		{
			d += 2 * offsety - 1;
			offsety -= 1;
		}
		else
		{
			d += 2 * (offsety - offsetx - 1);
			offsety -= 1;
			offsetx += 1;
		}
	}

}

/**********/
/* adapted from : https://gist.github.com/Gumichan01/332c26f6197a432db91cc4327fcabb1c */
void ShodanCircleArea(int x, int y, int radius)
{
	int offsetx, offsety, d = 0;

	offsetx = 0;
	offsety = radius;
	d = radius - 1;

	while (offsety >= offsetx)
	{
		SDL_RenderDrawLine(Shodan->renderer, x - offsety, y + offsetx, x + offsety, y + offsetx);
		SDL_RenderDrawLine(Shodan->renderer, x - offsetx, y + offsety, x + offsetx, y + offsety);
		SDL_RenderDrawLine(Shodan->renderer, x - offsetx, y - offsety, x + offsetx, y - offsety);
		SDL_RenderDrawLine(Shodan->renderer, x - offsety, y - offsetx, x + offsety, y - offsetx);

		if (d >= 2 * offsetx)
		{
			d -= 2 * offsetx + 1;
			offsetx += 1;
		}
		else if (d < 2 * (radius - offsety))
		{
			d += 2 * offsety - 1;
			offsety -= 1;
		}
		else
		{
			d += 2 * (offsety - offsetx - 1);
			offsety -= 1;
			offsetx += 1;
		}
	}
}

/**********/
void ShodanPolygon(SPoly* poly)
{
	if (poly->vertices->size < 3) { return; }

	for (int i = 0; i < poly->vertices->size - 1; i++)
	{
		SVector* src = ArrayGet(poly->vertices, i);
		SVector* dst = ArrayGet(poly->vertices, i + 1);

		SDL_RenderDrawLine(Shodan->renderer, (int)src->x, (int)src->y, (int)dst->x, (int)dst->y);
	}

	SVector* src = ArrayGet(poly->vertices, 0);
	SVector* dst = ArrayGet(poly->vertices, poly->vertices->size - 1);

	SDL_RenderDrawLine(Shodan->renderer, (int)src->x, (int)src->y, (int)dst->x, (int)dst->y);
}

/**********/
/* adapted from : https://alienryderflex.com/polygon_fill/ */
void ShodanPolygonArea(SPoly* poly)
{
	if (poly->vertices->size < 3) { return; };

	int  nodes, pixelY, i, j, swap = 0;
	//int pixelX = 0; //not used if drawing lines

	int* nodeX = Calloc(poly->vertices->size, sizeof(int));//?? nodeX[MAX_POLY_CORNERS],

	SVector** vertices = (SVector**)poly->vertices->items;

	//  Loop through the rows of the image.
	for (pixelY = (int)poly->miny; pixelY < (int)poly->maxy; pixelY++)
	{

		//  Build a list of nodes.
		nodes = 0;

		j = poly->vertices->size - 1;
		for (i = 0; i < poly->vertices->size; i++)
		{
			if ((vertices[i]->y < (float)pixelY && vertices[j]->y >= (float)pixelY) || (vertices[j]->y < (float)pixelY && vertices[i]->y >= (float)pixelY))
			{
				nodeX[nodes++] = (int)(vertices[i]->x + (pixelY - vertices[i]->y) / (vertices[j]->y - vertices[i]->y) * (vertices[j]->x - vertices[i]->x) + 0.5f);
			}

			j = i;
		}

		//  Sort the nodes, via a simple Bubble sort.
		i = 0;
		while (i < nodes - 1)
		{
			if (nodeX[i] > nodeX[i + 1])
			{
				swap = nodeX[i]; nodeX[i] = nodeX[i + 1]; nodeX[i + 1] = swap; if (i) i--;
			}
			else
			{
				i++;
			}
		}

		//  Fill the pixels between node pairs.
		for (i = 0; i < nodes; i += 2)
		{
			if (nodeX[i] >= poly->maxx) break;
			if (nodeX[i + 1] > poly->minx)
			{
				if (nodeX[i] < (int)poly->minx) nodeX[i] = (int)poly->minx;
				if (nodeX[i + 1] > (int)poly->maxx) nodeX[i + 1] = (int)poly->maxx;

				SDL_RenderDrawLine(Shodan->renderer, nodeX[i], pixelY, nodeX[i + 1] - 1, pixelY);
			}
		}
	}

	Free(nodeX);
}


/**********/
void ShodanImage(SImage* img, int x, int y)
{
	SDL_Rect dst = { x, y, img->w,  img->h };

	SDL_RenderCopy(Shodan->renderer, img->texture, NULL, &dst);
}

/**********/
void ShodanImageSized(SImage* img, int x, int y, int w, int h)
{
	SDL_Rect dst = { x, y, w,  h };

	SDL_RenderCopy(Shodan->renderer, img->texture, NULL, &dst);
}

/**********/
void ShodanImageRotated(SImage* img, int x, int y, int angle)
{
	SDL_Rect dst = { x, y, img->w,  img->h };

	SDL_RenderCopyEx(Shodan->renderer,
		img->texture,
		NULL,
		&dst,
		-(double)angle,
		NULL,
		SDL_FLIP_NONE);
}

/**********/
void ShodanSetFont(SFont* font)
{
	Shodan->font = font;
}

/**********/
void ShodanText(char* string, int x, int y)
{
	if (Shodan->font == NULL) { Error(__func__, "Font not set"); return; };

	if (string == NULL) { Log(__func__, "Text not set"); return; };

	Uint8 r, g, b = 0;

	SDL_GetRenderDrawColor(Shodan->renderer, &r, &g, &b, NULL);

	SDL_SetTextureColorMod(Shodan->font->texture, r, g, b);

	size_t len = strlen(string);

	int posx = x;
	int posy = y;

	for (size_t i = 0; i < len; i++)
	{

		if (string[i] == _ASCII_NEWLINE)
		{
			posx = x;
			posy += Shodan->font->tile_h;
		}
		else
		{
			int tile_index = string[i] - _ASCII_OFFSET;

			if (tile_index < 0 || tile_index >= _ASCII_CHARSET_SIZE)
			{
				tile_index = _ASCII_UNKNOW - _ASCII_OFFSET;
			}

			SDL_Rect dst = { posx, posy,  Shodan->font->tile_w,  Shodan->font->tile_h };

			SDL_RenderCopy(Shodan->renderer, Shodan->font->texture, Shodan->font->tiles[tile_index], &dst);

			posx += Shodan->font->tile_w;
		}

	};

}

/**********/
int ShodanTextWidth(char* string)
{
	int size = 0;

	int count = 0;

	int len = strlen(string);

	for (int i = 0; i < len; i++)
	{
		count++;

		if (string[i] == _ASCII_NEWLINE) { count = 0; }

		if (count > size) { size = count; };
	};

	return size * Shodan->font->tile_w;
}

/**********/
int ShodanTextHeight(char* string)
{
	int count = 1;

	int len = strlen(string);

	for (int i = 0; i < len; i++)
	{
		if (string[i] == _ASCII_NEWLINE) { count++; };
	};

	return count * Shodan->font->tile_h;
}

/**********/
void ShodanPlay(SSound* sound)
{
	if (Shodan->audio_device == 0) { Log(__func__, "Audio system not initialized"); return; }

	SDL_ClearQueuedAudio(Shodan->audio_device);

	int res = SDL_QueueAudio(Shodan->audio_device, sound->buf, sound->len);

	if (res != 0) { Error(__func__, "%s", SDL_GetError()); }
}

/**********/
bool ShodanEvents()
{
	SDL_Event event;

	if (SDL_PollEvent(&event))
	{

		switch (event.type)
		{
		case SDL_QUIT:
			Shodan->event = QUIT;
			return true;

		case SDL_KEYDOWN:
			Shodan->event = KEYPRESS;
			Shodan->key = event.key.keysym.sym;
			return true;

		case SDL_KEYUP:
			Shodan->event = KEYRELEASE;
			Shodan->key = event.key.keysym.sym;
			return true;

		case SDL_MOUSEMOTION:
			Shodan->event = MOUSEMOVE;
			Shodan->mousex = event.motion.x;
			Shodan->mousey = event.motion.y;
			return true;

		case SDL_MOUSEBUTTONDOWN:
			Shodan->event = MOUSEPRESS;
			Shodan->mousex = event.button.x;
			Shodan->mousey = event.button.y;
			Shodan->button = event.button.button;
			return true;
		
		case SDL_MOUSEBUTTONUP:
			Shodan->event = MOUSERELEASE;
			Shodan->mousex = event.button.x;
			Shodan->mousey = event.button.y;
			Shodan->button = event.button.button;
			return true;

		case SDL_MOUSEWHEEL:
			Shodan->event = MOUSEWHEEL;
			Shodan->wheel = (event.wheel.y < 0) ? W_DOWN : W_UP;
			return true;

		// fix this !!!
		case SDL_WINDOWEVENT:
		{
			if (event.window.event == SDL_WINDOWEVENT_EXPOSED)
			{
				Shodan->frames = 0;
				TimerStart(Shodan->timer);
			}
		}
		break;

		default: Shodan->event=NONE; break;

		}

	}

	Shodan->event = NONE;

	return false;
}

/**********/
void ShodanWaitKeyboard()
{
	bool wait = true;

	while (wait)
	{
		while (ShodanEvents())
		{
			if (EVENT == QUIT) { wait = false; };//exit anyway

			if (EVENT == KEYPRESS) { wait = false; };
		}

		SDL_Delay(10);
	}

	Shodan->frames = 0;
	TimerStart(Shodan->timer);
}

/**********/
void ShodanStart(char* name)
{
	ShodanSetState(name);

	ShodanPushMouseMotion();

	Shodan->run = true;

	while (Shodan->run == true)
	{
		if (Shodan->change != NULL)
		{
			Shodan->state = Shodan->change;
			Shodan->change = NULL;
			while (ShodanEvents()) {};
			ShodanPushMouseMotion();
		}

		if (Shodan->state->input != NULL) { Shodan->state->input(); };

		if (Shodan->state->update != NULL) { Shodan->state->update(); };

		ShodanBeginDraw();
		if (Shodan->state->draw != NULL) { Shodan->state->draw(); };
		ShodanEndDraw();
	}
}

/**********/
void ShodanStop()
{
	Shodan->run = false;
}

/**********/
void ShodanAddState(SState* state)
{
	for (int i = 0; i < Shodan->pool->size; i++)
	{
		SState* s = (SState*)ArrayGet(Shodan->pool, i);

		if (strcmp(s->name, state->name) == 0)
		{
			Log(__func__, "State \"%s\" already added", s->name);

			return;
		}
	}

	ArrayAdd(Shodan->pool, state);
}

/**********/
void ShodanSetState(char* name)
{
	for (int i = 0; i < Shodan->pool->size; i++)
	{
		SState* s = (SState*)ArrayGet(Shodan->pool, i);

		if (strcmp(s->name, name) == 0)
		{
			Shodan->change = s;

			return;
		}
	}

	Log(__func__, "State \"%s\" not found", name);
}

