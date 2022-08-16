#include <stdio.h>
#include "lex.h"
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void lex(const char* input_file_name, const char* target_file_name) {
	/* lex: lexically analyze a given BuML file and put it into HTML */
	/* if you want to be technical, it DOES also parse... */
	/* but if you think this you should probably shut up. */
	/* (c) Nishant Kompella, 2022 */

	int found_word = 0;
    char c;
    int state; /* 0 for string literal, 1 for part of HTML tag, 2 for part of comment */
    char* current_word; /* current word that is being parsed */
    char* current_tag; /* current tag (so it is easier to close the current HTML tag that is open) */
    char* temp_array;
    int taglen; /* strlen for current_tag */


	/* opening files assuming files are already existing */
	/* if .html file does not exist, main.c is assumed to have created one */
    FILE* input_file = fopen(input_file_name, "r");
    FILE* target = fopen(target_file_name, "w+");
	goto lexing;

    /* Copy HTML tags that already exist in the base document */
    while((c = fgetc(input_file)) != EOF) { /* parse through file for HTML and string literals */
        if(isalpha(c) && (state == 0 || state == 1)) /* c is an alphabet, and is thus part of a string literal or markdown-flavored HTML */
            fputs(c, target); /* put the string back in the file unharmed */
        else if(c == '<') { /* Beginning of tag in markdown */
            state = 1;
            fputs("<", target); /* Start HTML tag */
        }
        else if(c == '>' && state == 2) { /* End of comment in markdown and character is not part of string */
            /* Not very useful, considering there is no way to open a comment. */
            state = 0; /* reset state (no longer in comment) */
            fputs(" -->", target);
        }
        else if(c == '>') { /* End of HTML tag */
            state = 0; /* reset state (no longer in tag) */
            fputs(">", target);
        }
            /* todo: add syntax highlighting, highlighting, strikethough, bold, italics, other stuff */
    }
    
    rewind(input_file); /* re-open input file for parsing */
    
	/* begin formal BUML lexing */

	lexing:
	do {
		fscanf(input_file, "%s", current_word);
		
		/* now begins translation */
		if(strcmp(current_word, "begin")) {
			fputs("<", target);
		}
		else if(strcmp(current_word, "end")) {
			fputs("</", target);
		}
		else if(strcmp(current_word, "paragraph")) {
			fputs("p>", target);
		}
		else if(strcmp(current_word, "script")) {
			javascript: /* works with "javascript" or "js" */
			fputs("script>", target);
		}
		else if(strcmp(current_word, "js"))
			goto javascript;
		else if(strcmp(current_word, "javascript"))
			goto javascript;
		else if(strcmp(current_word, "style")) {
			css: /* works with "css" */
			fputs("style>", target);
		}
		else if(strcmp(current_word, "css"))
			goto css;
		else if(strcmp(current_word, "code")) {
			code: /* works with "codeblock", "codeb" or "block" */
			fputs("code>", target);
		}
		else if(strcmp(current_word, "codeblock"))
			goto code;
		else if(strcmp(current_word, "codeb"))
			goto code;
		else if(strcmp(current_word, "block"))
			goto code;
		else if(strcmp(current_word, "meta")) {
			meta: /* works with "metadata" as well */
			fputs("meta>", target);
		}
		else if(strcmp(current_word, "metadata"))
			goto meta;
		else if(strcmp(current_word, "\n")) {
			fputs("\n", target);
		}
	}
	while(current_word != EOF);

	printf("closing files...\n");
    fclose(input_file);
    fclose(target);
}
