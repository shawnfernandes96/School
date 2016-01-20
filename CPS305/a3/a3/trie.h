#include <stdio.h>

typedef struct trie {
    struct trie* children;
    int count;
    char letter;
    char leaf;
} trie;

/*
* PURPOSE : Intialise a trie
*
* INPUTS :
*            trie *t:        pointer to trie being initialised
*
*/
void trie_init(trie* t);

/*
* PURPOSE : Free all memory used by trie
*
* INPUTS :
*            trie *t:        pointer to trie being freed
*
*/
void trie_free(trie* t);

/*
* PURPOSE : Add a word to a trie
*
* INPUTS :
*            trie *t:        pointer to trie
*            char *text:        string being added
*            int length:        length of string being added
*
*/
void trie_add(trie* t, char* text, int length);

/*
* PURPOSE : Add a child trie to a trie
*
* INPUTS :
*            trie *t:        trie being added to
*            char l:            letter to be placed in added trie
*            char leaf:        boolean that is true when this node is the end of a word
*                            (and may have other words in children, for example the
*                             'g' in "dog" can lead to "dogs")
*
* RETURNS : A pointer to the added child
*
*/
trie* trie_addchild(trie* t, char l, char leaf);

/*
* PURPOSE : Find a word in a trie
*
* INPUTS :
*            trie *t:        pointer to trie being searched
*            char* text:        the text to search for
*            int length:        length of the text to search for
*
* RETURNS : A pointer to the found subtrie (or the original if not found)
*
*/
trie* trie_find(trie* t, char* text, int length);

/*
* PURPOSE : Add a list of words to a trie from a file
*
* INPUTS :
*            trie *t:            pointer to trie being added to
*            char *filename:        file name
*
*
*/
void trie_addfile(trie* t, char* filename);

/*
* PURPOSE : Find subtrie that matches text and prints all children of that subtrie
*
* INPUTS :
*            trie *t:        pointer to trie being searched and printed
*            char *text:        text to search for
*            int length:        length of text to search for
*
*/
void trie_print(trie* t, char* text, int length);