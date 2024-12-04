#include "../jacolib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Comparator function for qsort
int compare_int(const void* a, const void* b)
{
    return (*(int*)a - *(int*)b);
}

int main()
{
    const char* filename = "input.txt"; // The input

    char* content = ReadFile(filename);
    int line_count = 0;
    char** lines = SplitLines(content, &line_count);

    // Allocate arrays to store left and right column values
    int* left_column = (int*)malloc(sizeof(int) * line_count);
    int* right_column = (int*)malloc(sizeof(int) * line_count);
    if (!left_column || !right_column) 
    {
        perror("Memory allocation error");
        exit(1);
    }

    // Parse the file lines into left and right column arrays
    for (int i = 0; i < line_count; i++) 
    {
        sscanf(lines[i], "%d %d", &left_column[i], &right_column[i]);
        free(lines[i]); // Free each line after parsing
    }
    

    // Sort both columns
    qsort(left_column, line_count, sizeof(int), compare_int);
    qsort(right_column, line_count, sizeof(int), compare_int);

    // Calculate the total distance
    int total_distance = 0;
    for (int i = 0; i < line_count; i++) 
    {
        total_distance += abs(left_column[i] - right_column[i]);
    }

    // Print the total distance
    printf("Total distance: %d\n", total_distance);

    // Free the allocated memory
    free(left_column);
    free(right_column);
    free(lines);
    free(content);

    return 0;
}
