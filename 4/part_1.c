#include "../jacolib.h"
#include <stdio.h>
#include <string.h>

// Define the word to search
#define WORD "XMAS"
#define WORD_LEN 4

// Define the eight directions as (dx, dy) pairs
int directions[8][2] = 
{
    {0, 1},   // Right
    {0, -1},  // Left
    {1, 0},   // Down
    {-1, 0},  // Up
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

int main() 
{
    const char* filename = "input.txt";
    int line_count = 0;

    // Read the file and split it into lines
    char* content = ReadLines(filename);
    char** grid = SplitLines(content, &line_count);

    int total_count = 0;

    // Iterate over every cell in the grid
    for (int x = 0; x < line_count; x++) 
    {
        int cols = strlen(grid[x]); // Number of columns in this row
        for (int y = 0; y < cols; y++) 
        {
            // Try all eight directions
            for (int d = 0; d < 8; d++) 
            {
                int dx = directions[d][0];
                int dy = directions[d][1];
                total_count += find_word(grid, line_count, cols, x, y, dx, dy);
            }
        }
    }

    printf("Total occurrences of '%s': %d\n", WORD, total_count);

    // Free the allocated memory
    for (int i = 0; i < line_count; i++) 
    {
        free(grid[i]);
    }
    free(grid);
    free(content);

    return 0;
}
