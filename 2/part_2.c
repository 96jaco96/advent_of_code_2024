#include "../jacolib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// More compact function to check if a report (given as an array of levels) is safe
// Same logic as part 1 but more compact by moving the parsing and definition of level out of it
bool is_safe_levels(int* levels, int level_count)
{
    bool increasing = true, decreasing = true;

    for (int i = 1; i < level_count; i++) 
    {
        int diff = levels[i] - levels[i - 1];

        // Check if adjacent levels differ by 1 to 3
        if (abs(diff) < 1 || abs(diff) > 3) 
        {
            return false;
        }

        // Check for if they're increasing or decreasing
        if (diff > 0) 
        {
            decreasing = false;
        } 
        else if (diff < 0) 
        {
            increasing = false;
        } 
        else 
        {
            return false; // Levels are neither increasing nor decreasing
        }
    }

    // Ensure levels are either all increasing or all decreasing
    return increasing || decreasing;
}

// Function to check if a report is safe or can be made safe with the Problem Dampener
bool is_safe_with_dampener(const char* report_line)
{
    // Parse the report line into an array of integers
    int levels[100]; // ALWAYS adjust as needed
    int level_count = 0;
    const char* token = strtok((char*)report_line, " ");
    while (token != NULL) 
    {
        levels[level_count++] = atoi(token);
        token = strtok(NULL, " ");
    }

    // Check if the report is already safe
    if (is_safe_levels(levels, level_count)) 
    {
        return true;
    }

    // Try removing each level one at a time
    for (int i = 0; i < level_count; i++) 
    {
        int temp[100]; // Temporary array for testing safety
        int temp_count = 0;

        // Copy all levels except the one at index i
        for (int j = 0; j < level_count; j++) 
        {
            if (j != i) 
            {
                temp[temp_count++] = levels[j];
            }
        }

        // Check if the modified report is safe
        if (is_safe_levels(temp, temp_count)) 
        {
            return true;
        }
    }

    // If no single level removal makes the report safe, it's unsafe
    return false;
}

int main()
{
    const char* filename = "input.txt";

    // Read file content
    char* content = ReadFile(filename);
    int line_count = 0;
    char** lines = SplitLines(content, &line_count);

    // Count the safe reports
    int safe_count = 0;
    for (int i = 0; i < line_count; i++) 
    {
        if (is_safe_with_dampener(lines[i]))
        {
            safe_count++;
        }
        free(lines[i]);
    }

    free(lines);
    free(content);

    printf("Number of safe reports with dampener: %d\n", safe_count);

    return 0;
}
