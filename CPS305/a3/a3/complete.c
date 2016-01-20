#include <stdio.h>
#include <stdlib.h>
#include "trie.h"

/*
* PURPOSE : print all autocomplete options for some text
*
* INPUTS :
*            trie *t:        pointer to trie with dictionary loaded
*            char* text:        the text to autocomplete
*            int length:        length of the text
*
*/
void autocomplete(trie* t, char* text, int length) {
    trie* x = trie_find(t, text, length);
    if (x == t) {
        printf("No solutions found.\n");
    }
    else {
        trie_print(x, text, length);
    }
}

/*
* PURPOSE : count chars in word (will stop at new line and null char)
*
* INPUTS :
*            char *text:        Text to count
*
*/
int count(char* text) {
    int i = 0;
    for (i = 0; text[i] != '\n' && text[i] != '\0'; i++);
    return i;
}

/*
* PURPOSE : main method will perform the following:
*            1. Load dictionary into a tree
*            2. Read user input from stdin
*            3. Print autocomplete results for user input
*            4. Exit on blank line and free memory
*
* INPUTS :
*            char *text:        Text to count
*
*/
int main() {
    trie* t = (trie*)malloc(sizeof(trie));
    trie_init(t);
    trie_addfile(t, "american-english-no-accents");

    char* text = malloc(32 * sizeof(char));

    do {
        printf("Enter String: ");
        fgets(text, 32, stdin);
        autocomplete(t, text, count(text));
    } while (text[0] != '\n');

    trie_free(t);
    free(text);
    return 0;
}