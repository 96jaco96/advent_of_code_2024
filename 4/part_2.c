#include "../jacolib.h"
#include <stdio.h>
#include <string.h>

#define WORD "MAS"
#define WORD_LEN 3

// Define the diagonal directions as (dx, dy) pairs
int directions[4][2] = 
{
    {1, 1},   // Diagonal down-right
    {-1, -1}, // Diagonal up-left
    {1, -1},  // Diagonal down-left
    {-1, 1}   // Diagonal up-right
};

// Check if the word exists starting from x, y in the given direction
int find_word(char** grid, int rows, int cols, int x, int y, int dx, int dy) 
{
    for (int i = 0; i < WORD_LEN; i++) 
    {
        int nx = x + i * dx;
        int ny = y + i * dy;
        // Check bounds and character match
        if (nx < 0 || ny < 0 || nx >= rows || ny >= cols || grid[nx][ny] != WORD[i]) 
        {
            return 0;
        }
    }
    return 1; // Word found in this direction
}

// Find all diagonal MAS occurrences and count valid X intersections
int count_x_mas(char** grid, int rows, int cols) 
{
    int total_count = 0;

    // Iterate over every cell in the grid
    for (int x = 0; x < rows; x++) 
    {
        for (int y = 0; y < cols; y++) 
        {
            // Only proceed if the current cell contains 'A' (potential center)
            if (grid[x][y] == 'A') 
            {
                // Check all diagonal directions for intersecting "MAS"
                int intersect_count = 0;

                for (int d = 0; d < 4; d++) 
                {
                    int dx = directions[d][0];
                    int dy = directions[d][1];

                    // Check if a MAS exists in this diagonal direction
                    if (find_word(grid, rows, cols, x - dx, y - dy, dx, dy)) 
                    {
                        intersect_count++;
                    }
                }

                // If and ONLY if there are exactly 2 diagonal "MAS" intersecting at 'A', it's a valid X-MAS
                if (intersect_count == 2) 
                {
                    total_count++;
                }
            }
        }
    }

    return total_count;
}

int main() 
{
    const char* filename = "input.txt";
    int line_count = 0;

    // File reading boilerplate
    char* content = ReadLines(filename);
    char** grid = SplitLines(content, &line_count);

    // Count the total number of the X MAS intersections
    int total_count = count_x_mas(grid, line_count, strlen(grid[0]));

    printf("Total occurrences of X MAS: %d\n", total_count);

    for (int i = 0; i < line_count; i++) 
    {
        free(grid[i]);
    }
    free(grid);
    free(content);

    return 0;
}
