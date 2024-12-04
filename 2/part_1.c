#include "../jacolib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Giga function to check if a report is safe
bool is_safe_report(const char* report_line)
{
    // Parse the report line into an array of integers
    int levels[100]; // Levels are stored here, we assume max 100 levels per report: ADJUST AS NEEDED!!!!
    int level_count = 0;
    const char* token = strtok((char*)report_line, " "); // Using space as delimiter
    while (token != NULL) 
    {
        levels[level_count++] = atoi(token); // woosh! you're now an int!
        token = strtok(NULL, " ");
    }

    // Assume that the report is already nice until proven wrong
    bool increasing = true, decreasing = true;

    // For each level
    for (int i = 1; i < level_count; i++) 
    {
        int diff = levels[i] - levels[i - 1];
        
        // Check if adjacent levels differ by 1 to 3
        if (abs(diff) < 1 || abs(diff) > 3)
        {
            return false; 
        }

        // Check for increasing or decreasing
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

int main()
{
    const char* filename = "input.txt";

    // Boilerplate to read the file contents
    char* content = ReadFile(filename);
    int line_count = 0;
    char** lines = SplitLines(content, &line_count);

    // Count the safe reports
    int safe_count = 0;

    for (int i = 0; i < line_count; i++) 
    {
        if (is_safe_report(lines[i])) 
        {
            safe_count++;
        }
        free(lines[i]);
    }

    // look ma! i'm a good boy freeing memory in C!!! :33 <3
    free(lines);
    free(content);

    // Print the total number of safe reports
    printf("Number of safe reports: %d\n", safe_count);

    return 0;
}
