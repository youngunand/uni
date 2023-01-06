#include <stdio.h>
#include <stdlib.h>

#define START_SYMBOL 'S'
#define END_SYMBOL 'E'
#define PATH_SYMBOL 'O'
#define FREE_SYMBOL ' '
#define ROWS 21
#define COLS 42

typedef struct {
    int x;
    int y;
} point;

void print_grid(char grid[ROWS][COLS])
{
    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS - 1; c++) {
            printf("%c ", grid[r][c]);
        }
        putchar('\n');
    }
}


point find_starting_point(char grid[ROWS][COLS])
{
    for (size_t i = 0; i < ROWS - 1; i++) {
        for (size_t j = 0; j < COLS - 2; j++) {
            // input always has exactely one starting point
            if (grid[i][j] == 'S') {
                point starting_point = { .x = i, .y = j };
                return starting_point;
            }
        }
    }
}

void get_all_neighbors(char grid[ROWS][COLS], char all_neighbors[], point current_point)
{
    if (current_point.x - 1 >= 0) {
        all_neighbors[0] = grid[current_point.x-1][current_point.y]; // NORTH
    }
    if (current_point.x + 1 <= ROWS - 1) {
        all_neighbors[1] = grid[current_point.x+1][current_point.y]; // SOUTH
    }
    if (current_point.y - 1 >= 0) {
        all_neighbors[2] = grid[current_point.x][current_point.y - 1]; // WEST
    }
    if (current_point.y + 1 <= COLS - 2) {
        all_neighbors[3] = grid[current_point.x][current_point.y+1]; // EAST
    }
}

int make_step(char grid[ROWS][COLS], point starting_point, point current_point, int favoured_move, int solution_found)
{
    char all_neighbors[4];
    get_all_neighbors(grid, all_neighbors, current_point);   


    // check for solution
    for (size_t i = 0; i < 4; i++) {
        if (all_neighbors[i] == 'E' || all_neighbors[i] == 'o') { // draw correct path
            solution_found = 1;
            grid[current_point.x][current_point.y] = 'o';
            print_grid(grid);
            //make_step(grid, current_point)
            //for (size_t i = 0; i < 4; i++)
            //{
            //    if(all_neighbors[i] == 'x') {
            //        grid[current_point.x][current_point.y] = 'o';
            //    }
            //    print_grid(grid);
            //}
            
            
            return 1; // break and go outside in recursion
        }
    }
    
    if (all_neighbors[0] == ' ' && favoured_move == 0 ) { // go NORTH
        current_point.x--;
        grid[current_point.x][current_point.y] = 'x';
        print_grid(grid);
        make_step(grid, starting_point, current_point, 0, solution_found); 
        favoured_move = 10; //off-label use of favoured move, so that after recursion no other if is entered (like continue)
    }
    if (all_neighbors[1] == ' '&& favoured_move <= 1) { // go SOUTH
        current_point.x++;
        grid[current_point.x][current_point.y] = 'x';
        print_grid(grid);
        make_step(grid, starting_point, current_point, 1, solution_found);
        favoured_move = 10;
    }
    if (all_neighbors[2] == ' ' && favoured_move <= 2) { // go WEST
        current_point.y--;
        grid[current_point.x][current_point.y] = 'x';
        print_grid(grid);
        make_step(grid, starting_point, current_point, 2, solution_found);
        favoured_move = 10;
    }
    if (all_neighbors[3] == ' ' && favoured_move <= 3) { // go EAST
        current_point.y++;
        grid[current_point.x][current_point.y] = 'x';
        print_grid(grid);
        make_step(grid, starting_point, current_point, 3, solution_found);
        favoured_move = 10;
    } 
    if(favoured_move == 0) {
        if(grid[current_point.x][current_point.y] == 'x') {
            grid[current_point.x][current_point.y] = 'i';
        }
       return 0;
    } else {
           make_step(grid, starting_point, current_point, 0, solution_found);
    }}

int find_path(char grid[ROWS][COLS])
{
    //char solution_grid[ROWS][COLS] = grid;
    point starting_point = find_starting_point(grid);

    point current_point = starting_point;

    int solution = make_step(grid, starting_point, current_point, 0, 0);

    char all_neighbors[4];
    get_all_neighbors(grid, all_neighbors, current_point);

    //if solution was not found go back to starting point
    if(!solution) {
        for (size_t i = 0; i < 4; i++)
        {
            if(all_neighbors[i] == ' ') {
                make_step(grid, starting_point, current_point, 0,0);
            }
        }
        
    }

    //if(grid[starting_point.x][starting_point.y] == 'o') {
    //    return 1;
    //}
    return solution;
}

int main(void)
{
    char grid[ROWS][COLS] = {
        "+-------------+-+---+-------------+-----+",
        "|             | |S  |             |     |",
        "| +-----+---+ | + + | +-----+ +-+ +-+ +-+",
        "|       |   | |   | | |     | | |   |   |",
        "| +---+ | + | | +-+ + + +---+ | +-+ +-+ |",
        "| |   | | | | |   |     |     |   |     |",
        "+-+ + | | | | +---+-----+ +---+-+ +-+-+ |",
        "|   | | | | |     |       |       | |   |",
        "| +-+ + | | +---+ + +-----+-+ +-+ + | +-+",
        "|   |   | | |   |   |         | |   |   |",
        "+-+ +---+ +-+ + +-+-+ + +-+---+ +-+ +-+ |",
        "| | | |       |   |   |   |         |   |",
        "| + | | +-----+ + | +-+-+ | +---+---+ +-+",
        "|   | | |     | | | |     |     |   |   |",
        "+-+-+ | +---+ | | +-+ +---+---+ | + +-+ |",
        "| |   |       | |     |         | |   | |",
        "| + + +-----+ | | +---+-------+-+ | + | |",
        "|   |       | | | |           |   | | | |",
        "| +-+ +-----+ | +-+ +-------+ + +-+ +-+ |",
        "|   |         |     E       |     |     |",
        "+---+---------+-------------+-----+-----+",
    };

    char grid1[ROWS][COLS] = {
        "+++++++++++++++++++++++++++++++++++++++++",
        "+++++++++++++++++++++++++++++++++++++++++",
        "+++++++++++++++++++++++++++++++++++++++++",
        "+++++++++++++++++++++++++++++++++++++++++",
        "+++++++++++++++++++++++++++++++++++++++++",
        "+++++++++++++++++++++++++++++++++++++++++",
        "+++++++++++++++++++++++++++++++++++++++++",
        "|                                       |",
        "|                +-----+                |",
        "++++++++++++++   |    S|   ++++++++++++++",
        "++++++++++++++   |     |   ++++++++++++++",
        "++++++++++++++   |E    |   ++++++++++++++",
        "++++++++++++++   +-----+   ++++++++++++++",
        "++++++++++++++             ++++++++++++++",
        "+++++++++++++++++++++++++++++++++++++++++",
        "+++++++++++++++++++++++++++++++++++++++++",
        "+++++++++++++++++++++++++++++++++++++++++",
        "+++++++++++++++++++++++++++++++++++++++++",
        "+++++++++++++++++++++++++++++++++++++++++",
        "+++++++++++++++++++++++++++++++++++++++++",
        "+++++++++++++++++++++++++++++++++++++++++"
    };
    print_grid(grid);
    printf("\nsolution found: %s\n", find_path(grid) ? "yes" : "no");
    print_grid(grid);
    return EXIT_SUCCESS;
}
