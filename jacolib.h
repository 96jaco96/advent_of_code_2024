#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~ Files manipulation ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// Read the file in a raw way char by char 
char* ReadFile(const char* filename)
{
    FILE* f = fopen(filename, "rb");
    if (f == NULL){
        exit(1);
    }
    fseek(f, 0L, SEEK_END);
    long size = ftell(f)+1;
    fclose(f);
    f = fopen(filename, "r");
    void* content = memset(malloc(size), '\0', size);
    fread(content, 1, size-1, f);
    fclose(f);
    return (char*) content;
}

// Read the file in a raw way line by line
char* ReadLines(const char* filename)
{
    FILE* f = fopen(filename, "rb");
    if (f == NULL) {
        perror("Error opening file");
        exit(1);
    }
    
    fseek(f, 0L, SEEK_END);
    long size = ftell(f) + 1; // Add 1 for the null terminator
    fclose(f);
    
    f = fopen(filename, "r");
    if (f == NULL) {
        perror("Error opening file");
        exit(1);
    }

    char* content = (char*)calloc(size, sizeof(char));
    if (content == NULL) {
        perror("Memory allocation error");
        exit(1);
    }

    fread(content, 1, size - 1, f); // Read all but the null terminator
    fclose(f);

    return content;
}

// Used to split the lines read by ReadLines using something like:

// char* content = ReadLines(filename);
// int line_count = 0;
// char** lines = SplitLines(content, &line_count);
// char** SplitLines(char* content, int* line_count);
// printf("%s\n", lines[0]);

char** SplitLines(char* content, int* line_count)
{
    char** lines = NULL;
    int count = 0;

    // Tokenize the content by newline
    char* line = strtok(content, "\n");
    while (line != NULL) {
        lines = (char**)realloc(lines, sizeof(char*) * (count + 1));
        if (lines == NULL) {
            perror("Memory allocation error");
            exit(1);
        }

        lines[count] = strdup(line); // Duplicate the line
        if (lines[count] == NULL) {
            perror("Memory allocation error");
            exit(1);
        }

        count++;
        line = strtok(NULL, "\n");
    }

    *line_count = count;
    return lines;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~ Arrays manipulation ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int SumArray(int* array, int size)
{
    int sum = 0;
    for (int i = 0; i < size; i++)
    {
        sum += array[i];
    }
    return sum;
}

int AverageArray(int* array, int size)
{
    return SumArray(array, size) / size;
}

void QuickSort(int *array, int left, int right)
{
    int i = left, j = right;
    int tmp;
    int pivot = array[(left + right) / 2];

    /* partition */
    while (i <= j)
    {
        while (array[i] < pivot)
            i++;
        while (array[j] > pivot)
            j--;
        if (i <= j)
        {
            tmp = array[i];
            array[i] = array[j];
            array[j] = tmp;
            i++;
            j--;
        }
    };

    /* recursion */
    if (left < j)
        QuickSort(array, left, j);
    if (i < right)
        QuickSort(array, i, right);
}

int IntArrayToSingleInt(int* array, int size)
{
    int i, k = 0;
    for (i = 0; i < size; i++)
        k = 10 * k + array[i];
    return k;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~ Strings manipulation ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int CharToInt(char c)
{
    return c - '0';
}

char IntToChar(int i)
{
    return i + '0';
}

void ToUpperCase(char* str)
{
    for (int i = 0; i < strlen(str); i++)
    {
        str[i] = toupper(str[i]);
    }
}

void ToLowerCase(char* str)
{
    for (int i = 0; i < strlen(str); i++)
    {
        str[i] = tolower(str[i]);
    }
}

void RemoveAlpha(char* str)
{
    for (int i = 0; i < strlen(str); i++)
    {
        if (isalpha(str[i]))
        {
            str[i] = ' ';
        }
    }
}

void StripSpaces(char* str)
{
    for (int i = 0; i < strlen(str); i++)
    {
        if (str[i] == ' ')
        {
            for (int j = i; j < strlen(str); j++)
            {
                str[j] = str[j+1];
            }
            i--;
        }
    }
}

void RemoveNumbers(char* str)
{
    for (int i = 0; i < strlen(str); i++)
    {
        if (isdigit(str[i]))
        {
            str[i] = ' ';
        }
    }
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~ General functions ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int RandomNumberBetween(int min, int max)
{
    srand(time(0));
    return (min + rand() % (max - min + 1));
}

void WaitSeconds(double seconds)
{
    clock_t start = clock();
    while (clock() < start + seconds * CLOCKS_PER_SEC);
}


