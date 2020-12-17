#include "headers.h"

int main(int argc, char** argv)
{
	ShodanInit(WINDOW_W, WINDOW_H, false, false);

	g_font = FontInit(FONT_FILE);
	ShodanSetFont(g_font);

	g_grid = GridInit(30,40,20);

	SState *editor = StateInit(EDITOR, EditorInit, EditorInput, EditorUpdate, EditorDraw, EditorClose);

	ShodanAddState(editor);

	ShodanStart(EDITOR);

	StateClose(&editor);

	GridClose(&g_grid);

	FontClose(&g_font);

	ShodanClose();

	return 0;
}