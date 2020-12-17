#include "headers.h"

bool lmouse = false;
bool rmouse = false;

int mousex = 0;
int mousey = 0;

Grid *selector = NULL;
Cell *sel = NULL;
int sel_i = 0;
int sel_j = 0;

#define SELECTION_STR "Selection:"
#define USAGE_STR "SPACE:step\nCANC:clear\nESC:quit\n\nMOUSE LEFT:fill\nMOUSE RIGHT:move grid\nMOUSE WHEEL:zoom"
#define COMPONENTS_STR "GREY:blank\nORANGE:conductor\nRED:electron head\nBLUE:electron tail"

/**********/
void EditorInit()
{
    selector = GridInit(1,4,20);

    selector->cells[0][0].cur=BLANK;
    selector->cells[0][1].cur=COPPER;
    selector->cells[0][2].cur=HEAD;
    selector->cells[0][3].cur=TAIL;

    selector->pos_x=WIDTH-ShodanTextWidth(COMPONENTS_STR)-g_font->tile_w;
    selector->pos_y=g_font->tile_h*2;

    sel = &selector->cells[0][0];
}
    
/**********/
void EditorInput()
{
    while(ShodanEvents())
    {
        if(EVENT==QUIT){ ShodanStop();}

        if(EVENT==KEYPRESS && KEY==ESC){ ShodanStop(); }

        if(EVENT==KEYPRESS)
        {
            if(KEY==SPACE) { GridUpdate(g_grid); } 
            if(KEY==CANCEL){ GridReset(g_grid); }
        }
        
        if(EVENT==MOUSEPRESS)
        { 
            Cell *c = GridOver(selector, MOUSEX, MOUSEY); 

            if(c!=NULL)
            { 
                sel = c; 
                sel_i = (MOUSEX-selector->pos_x)/selector->c_size;
                sel_j = (MOUSEY-selector->pos_y)/selector->c_size;
                return;
            }

            mousex = MOUSEX;
            mousey = MOUSEY;

            if(lmouse || rmouse){ lmouse=false; rmouse=false; return;}

            if(BUTTON==B_LEFT) 
            {  
                lmouse = true;

                Cell *over = GridOver(g_grid, MOUSEX, MOUSEY); 
                if(over!=NULL) { over->cur=sel->cur;} 
            }

            if(BUTTON==B_RIGHT) 
            { 
                rmouse = true;
            }
        }
        
        if(EVENT==MOUSERELEASE) { lmouse = false; rmouse = false; }

        if(EVENT==MOUSEMOVE)
        {
            Cell *over = GridOver(g_grid, MOUSEX, MOUSEY); 

            if(lmouse && over!=NULL) { over->cur=sel->cur; };

            if(rmouse)
            {
                g_grid->pos_x += MOUSEX - mousex;
                g_grid->pos_y += MOUSEY - mousey;

                mousex = MOUSEX;
                mousey = MOUSEY;
            }      
        }

        if(EVENT==MOUSEWHEEL)
        {
            g_grid->c_size += (WHEEL==W_UP) ? 5 : -5;
            g_grid->c_size = (g_grid->c_size<5) ? 5 : g_grid->c_size;
        }
    }
}

/**********/
void EditorUpdate()
{
    
}
        
/**********/
void EditorDraw()
{
    ShodanClear( &(SColor){0xA0,0xA0,0xA0,0xFF} );

    GridDraw(g_grid);

    GridDraw(selector);

    ShodanSetColor(FONT_COLOR);
    ShodanRect(selector->pos_x+sel_i*selector->c_size+1, 
                selector->pos_y+sel_j*selector->c_size+1, 
                selector->c_size-1, selector->c_size-1);
    

    ShodanSetColor(FONT_COLOR);

    ShodanText(SELECTION_STR, selector->pos_x, selector->pos_y-g_font->tile_h);

    ShodanText(COMPONENTS_STR, WIDTH-ShodanTextWidth(COMPONENTS_STR)-g_font->tile_w, selector->pos_y+selector->c_size+g_font->tile_h);

    ShodanText(USAGE_STR, g_font->tile_w, g_font->tile_h);
}

/**********/
void EditorClose()
{
    GridClose(&selector);
}