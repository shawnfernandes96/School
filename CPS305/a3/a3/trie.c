#include <stdlib.h>
#include "trie.h"


void trie_init(trie* t) {
    t->count = 0;
    t->children = (trie*)malloc(60 * sizeof(trie));
    t->letter = '\0';
    t->leaf = 0;
}

void trie_free(trie* t) {
    int i = 0;
    for (i = 0; i < t->count; i++) {
        trie* x = &(t->children[i]);
        trie_free(x);
    }
    free(t->children);
}

trie* trie_addchild(trie* t, char l, char leaf) {
    trie* x = &(t->children[t->count]);
    trie_init(x);
    x->letter = l;
    x->leaf = leaf;
    t->count++;
    return x;
}

void trie_add(trie* t, char* text, int length) {
    int i = 0;
    for (i = 0; i < length; i++) {
        int j = 0;
        char found = 0;
        for (j = 0; j < t->count; j++) {
            trie* x = &(t->children[j]);
            if (x->letter == text[i]) {
                t = x;
                found = 1;
                break;
            }
        }
        if (found == 0)
        {
            t = trie_addchild(t, text[i], i == length - 1);
        }
    }
}

trie* trie_find(trie* t, char* text, int length) {
    trie* original = t;
    int i = 0;
    for (i = 0; i < length; i++) {
        int j = 0;
        char found = 0;
        for (j = 0; j < t->count; j++) {
            trie* x = &(t->children[j]);
            if (x->letter == text[i]) {
                t = x;
                found = 1;
                break;
            }

        }
        if (found == 0) {
            return original;
        }
    }
    return t;
}

void trie_addfile(trie* t, char* filename) {
    FILE *f = fopen(filename, "r");
    while (!feof(f)) {
        char* line = (char*)malloc(32 * sizeof(char));
        fgets(line, 32, f);
        int i = 0;
        for (i = 0; line[i] != '\n' && line[i] != '\0'; i++);
        if (i > 0 && i < 32)
            trie_add(t, line, i);
        free(line);
    }
    fclose(f);
}

void trie_print(trie* t, char* text, int length) {
    int i = 0;
    for (i = 0; i < t->count; i++) {
        trie* x = &(t->children[i]);
        text[length++] = x->letter;
        if (x->count < 1) {
            text[length] = '\0';
            printf("%s\n", text);
        }
        else if (x->leaf) {
            text[length] = '\0';
            printf("%s\n", text);
            text[length] = '_';
            trie_print(x, text, length);
        }
        else {
            trie_print(x, text, length);
        }
        length--;
    }
}