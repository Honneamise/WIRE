#define BLANK   'b'
#define COPPER  'c'
#define HEAD    'h'
#define TAIL    't'

#define MIN_CELL_SIZE 5

typedef struct Cell
{
    char cur;
    char next;
}
Cell;

/**********/

typedef struct Grid
{
    int pos_x;
    int pos_y;

    int rows;
    int cols;
    int c_size;

    Cell **cells;

    int steps;

}Grid;

/**********/
Grid *GridInit(int rows, int cols, int c_size);

void GridClose(Grid **grid);

void GridDraw(Grid *grid);

Cell *GridOver(Grid *grid, int x, int y);

void GridReset(Grid *grid);

void GridUpdate(Grid *grid);

