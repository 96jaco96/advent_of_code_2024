#include "../jacolib.h"
#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

int main() 
{
    const char* filename = "input.txt";
    const char* memory = ReadFile(filename);
    int total = 0;
    int enabled = 1; // assume mult is by default true

    // Compiling our regex patterns
    regex_t mul_regex, do_regex, dont_regex;
    regcomp(&mul_regex, "mul\\(([0-9]+),([0-9]+)\\)", REG_EXTENDED);
    // Anchor these to the start of the string
    regcomp(&do_regex, "^do\\(\\)", REG_EXTENDED); 
    regcomp(&dont_regex, "^don't\\(\\)", REG_EXTENDED);

    regmatch_t matches[3];
    const char* cursor = memory;


    while (*cursor != '\0') 
    {
         // Check for do()
        if (regexec(&do_regex, cursor, 1, matches, 0) == 0 && matches[0].rm_so == 0) 
        {
            enabled = 1;
            cursor += 4; // Move cursor past do() (length is 4)
            continue;
        }

         // Check for don't()
        if (regexec(&dont_regex, cursor, 1, matches, 0) == 0 && matches[0].rm_so == 0) 
        {
            enabled = 0;
            cursor += 7; // Move cursor past don't() (length is 7)
            continue;
        }

        // Check for the pattern mul(X,Y)
        if (regexec(&mul_regex, cursor, 3, matches, 0) == 0 && matches[0].rm_so == 0) 
        {
            if (enabled)  // ONLY process the mul IF enabled
            {
                // Convert to int and add to the total
                int x = atoi(cursor + matches[1].rm_so);
                int y = atoi(cursor + matches[2].rm_so);
                total += x * y;
            }

            cursor += matches[0].rm_eo; // Move cursor past the entire match
            continue;
        }

        // If no matches, just move the cursor forward
        cursor++;
    }

    regfree(&mul_regex);
    regfree(&do_regex);
    regfree(&dont_regex);
    free((void*)memory);

    printf("Total sum of valid enabled mul instructions: %d\n", total);

    return 0;
}
