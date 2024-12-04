#include "../jacolib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to count occurrences of a number in an array
int count_occurrences(int* array, int size, int number)
{
    int count = 0;
    for (int i = 0; i < size; i++) 
    {
        if (array[i] == number) 
        {
            count++;
        }
    }
    return count;
}

// Comparator function for qsort
int compare_int(const void* a, const void* b)
{
    return (*(int*)a - *(int*)b);
}

int main()
{
    const char* filename = "input.txt";

    char* content = ReadFile(filename);
    int line_count = 0;
    char** lines = SplitLines(content, &line_count);

    // Allocate arrays to store left and right column values
    int* left_column = (int*)malloc(sizeof(int) * line_count);
    int* right_column = (int*)malloc(sizeof(int) * line_count);

    // Parse the file lines into left and right column arrays
    for (int i = 0; i < line_count; i++) 
    {
        sscanf(lines[i], "%d %d", &left_column[i], &right_column[i]);
        free(lines[i]); // Free each line after parsing
    }

    free(lines);
    free(content);

    // Calculate the similarity score
    int similarity_score = 0;
    for (int i = 0; i < line_count; i++) 
    {
        int count = count_occurrences(right_column, line_count, left_column[i]);
        similarity_score += left_column[i] * count;
    }

    // Print the similarity score
    printf("Similarity score: %d\n", similarity_score);

    // Free allocated memory
    free(left_column);
    free(right_column);

    return 0;
}
