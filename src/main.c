#include <stdio.h>
#include "lex.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char** argv) {
    /* create a new .html file with the same name as the .buml one */
    FILE* input_file = argv[1];
    printf("%s\n", argv[1]);
    char* new_file_name; /* to create new HTML file */
    new_file_name = strdup(argv[1]); /* copy the name of the .buml file */
    int len = strlen(new_file_name);
    int i;
    for(i = 1; i < 5; i++)
        new_file_name[len - i] = ' '; /* get rid of the "buml" at the end of the file name */
    len -= (i - 1);
    new_file_name[len] = 'h';
    new_file_name[len + 1] = 't';
    new_file_name[len + 2] = 'm';
    new_file_name[len + 3] = 'l';
    printf("%s\n", new_file_name);

    /* lex and parse the new HTML file and push html code into .html file */
    FILE* html_file = fopen(new_file_name, "+w");
    lex(input_file, html_file);

    free(new_file_name);
}
