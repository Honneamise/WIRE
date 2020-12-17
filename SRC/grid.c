#include "headers.h"

/**********/
Grid *GridInit(int rows, int cols, int c_size)
{
    Grid *grid = Calloc(1, sizeof(Grid));

    grid->rows = rows;
    grid->cols = cols;

    grid->cells = Calloc(rows, sizeof(Cell *));

    for(int i=0;i<rows;i++)
    {
        grid->cells[i] = Calloc(cols, sizeof(Cell));

        for(int j=0;j<cols;j++)
        {
            grid->cells[i][j].cur = BLANK;
        }
    }

    grid->c_size = c_size;

    grid->pos_x = (WIDTH - c_size * cols)/2;
    grid->pos_y = (HEIGHT - c_size * rows)/2;

    return grid;
}


/**********/
void GridClose(Grid **grid)
{
    for(int i=0;i<(*grid)->rows;i++)
    {
        Free((*grid)->cells[i]);
    }

    Free((*grid)->cells);
    
    Free(*grid);
    
    *grid = NULL;
}

/**********/
void GridDraw(Grid *grid)
{
    //bg
    ShodanSetColor(GRID_BG_COLOR);
    ShodanRectArea(grid->pos_x, grid->pos_y, grid->cols*grid->c_size, grid->rows*grid->c_size);

    //cells
    for(int i=0;i<grid->rows;i++)
    {
        for(int j=0;j<grid->cols;j++)
        {
            if(grid->cells[i][j].cur != BLANK)
            {
                int x = grid->pos_x + j*grid->c_size ;
                int y = grid->pos_y + i*grid->c_size ;

                switch(grid->cells[i][j].cur)
                {
                    case COPPER: ShodanSetColor(C_COLOR); break;
                    case HEAD  : ShodanSetColor(H_COLOR); break;
                    case TAIL  : ShodanSetColor(T_COLOR); break;
                    default    : break;
                }
                
                ShodanRectArea(x, y, grid->c_size, grid->c_size);
            }
        }
    }

    //grid
    ShodanSetColor(GRID_COLOR);
    for(int i=0;i<grid->rows+1;i++)
    {
        int y = grid->pos_y + i*grid->c_size;
        ShodanLine(grid->pos_x, y, grid->pos_x + grid->cols*grid->c_size, y);
    }

    for(int i=0;i<grid->cols+1;i++)
    {
        int x = grid->pos_x + i*grid->c_size;
        ShodanLine(x, grid->pos_y, x, grid->pos_y+grid->rows*grid->c_size);
    }
    
}

/**********/
Cell *GridOver(Grid *grid, int x, int y)
{
    if(x<grid->pos_x || x>grid->pos_x+grid->cols*grid->c_size || y<grid->pos_y || y>grid->pos_y+grid->rows*grid->c_size)
    {
        return NULL;
    }

    int i = (y - grid->pos_y)/grid->c_size;

    int j = (x - grid->pos_x)/grid->c_size;

    return &grid->cells[i][j];    
}

/**********/
void GridReset(Grid *grid)
{
    grid->steps = 0;

    for(int i=0;i<grid->rows;i++)
    {
        for(int j=0;j<grid->cols;j++)
        {
            grid->cells[i][j].cur = BLANK;
        }  
    }
}

/**********/
void GridUpdate(Grid *grid)
{
    grid->steps++;

    for(int i=0;i<grid->rows;i++)
    {
        for(int j=0;j<grid->cols;j++)
        {
            if(grid->cells[i][j].cur!=BLANK)
            {
                switch(grid->cells[i][j].cur)
                {
                    case COPPER:
                    {
                        int adj = 0;

                        adj += ((i-1>=0) && (i-1<grid->rows) && (j-1>=0) && (j-1<grid->cols) && (grid->cells[i-1][j-1].cur==HEAD));
                        adj += ((i-1>=0) && (i-1<grid->rows) && (j  >=0) && (j  <grid->cols) && (grid->cells[i-1][j  ].cur==HEAD));
                        adj += ((i-1>=0) && (i-1<grid->rows) && (j+1>=0) && (j+1<grid->cols) && (grid->cells[i-1][j+1].cur==HEAD));
                        adj += ((i  >=0) && (i  <grid->rows) && (j-1>=0) && (j-1<grid->cols) && (grid->cells[i  ][j-1].cur==HEAD));
                        adj += ((i  >=0) && (i  <grid->rows) && (j+1>=0) && (j+1<grid->cols) && (grid->cells[i  ][j+1].cur==HEAD));
                        adj += ((i+1>=0) && (i+1<grid->rows) && (j-1>=0) && (j-1<grid->cols) && (grid->cells[i+1][j-1].cur==HEAD));
                        adj += ((i+1>=0) && (i+1<grid->rows) && (j  >=0) && (j  <grid->cols) && (grid->cells[i+1][j  ].cur==HEAD));
                        adj += ((i+1>=0) && (i+1<grid->rows) && (j+1>=0) && (j+1<grid->cols) && (grid->cells[i+1][j+1].cur==HEAD));

                        if(adj==1 || adj==2){ grid->cells[i][j].next = HEAD; }
                        else{ grid->cells[i][j].next = COPPER; }   
                    }
                    break;

                    case HEAD: grid->cells[i][j].next = TAIL; break;

                    case TAIL: grid->cells[i][j].next = COPPER; break;

                    default: break;
                }
                
            }
        }
    }

    //apply changes
    for(int i=0;i<grid->rows;i++)
    {
        for(int j=0;j<grid->cols;j++)
        {
            if(grid->cells[i][j].cur!=BLANK)
            {
                grid->cells[i][j].cur = grid->cells[i][j].next;
            }
        }
    }
}
