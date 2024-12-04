#include "../jacolib.h"
#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

int main() 
{
    const char* filename = "input.txt";
    const char* memory = ReadFile(filename);
    int total = 0;

    // Define and compile the regex pattern
    regex_t regex; // Structure to hold compiled regex
    regcomp(&regex, "mul\\(([0-9]+),([0-9]+)\\)", REG_EXTENDED);
    // PRO TIP!!! Regex compilation makes it faster! Without compilation, we would need to reparse the pattern every time.

    regmatch_t matches[3]; // Another handy structure from regex.h my beloved <3
    // matches[0] The full match (for example mul(2,4))
    // matches[1] The first captured group (for example 2)
    // matches[2] The second captured group (for example 4)

    const char* cursor = memory; // Start searching from the beginning of the input

    // This loop searches the input string (cursor) for a match to the compiled regex.
    // It fills the matches array with the start and end offsets of the matched text.
    // Returns 0 if a match is found, or non-zero if more matches exist.
    while (regexec(&regex, cursor, 3, matches, 0) == 0) 
    {
        // Converting the numbers to integers
        int x = atoi(cursor + matches[1].rm_so);
        int y = atoi(cursor + matches[2].rm_so); 
        // NOTE for myself:
        // rm_so is the start offset or the position from the input string where the match starts.
        // rm_eo is instead the position where the match ends.

        total += x * y;

        // Move cursor forward to continue searching after this match by the size of the full match
        cursor += matches[0].rm_eo;
    }

    regfree(&regex);
    printf("Total sum of valid mul instructions: %d\n", total);

    return 0;
}
