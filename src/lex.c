#include <stdio.h>
#include "lex.h"
#include <stdlib.h>

void lex(FILE* input_file, FILE* target) {
    int found_word = 0;

    /* Copy HTML tags that already exist in the base document */
    while((c = fgetc(input_file)) != EOF) { /* parse through file for HTML and string literals */
        if(isalpha(c) && (state == 0 || state == 1)) /* c is an alphabet, and is thus part of a string literal or markdown-flavored HTML */
            putchar(c); /* put the string back in the file unharmed */
        else if(c == '<') { /* Beginning of tag in markdown */
            state == 1;
            fputs("<", target); /* Start HTML tag */
        }
        else if(c == '>' && state == 2) { /* End of comment in markdown and character is not part of string */
            /* Not very useful, considering there is no way to open a comment. */
            state == 0; /* reset state (no longer in comment) */
            fputs(" -->", target);
        }
        else if(c == '>') { /* End of HTML tag */
            state == 0; /* reset state (no longer in tag) */
            fputs(">", target);
        }
            /* todo: add syntax highlighting, highlighting, strikethough, bold, italics, other stuff */
    }
        
    rewind(input_file); /* re-open input file for parsing */
}
