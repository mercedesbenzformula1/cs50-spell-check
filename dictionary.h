// Declares a dictionary's functionality

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdbool.h>

#include "node.h"

// Maximum length for a word
// (e.g., pneumonoultramicroscopicsilicovolcanoconiosis)
#define LENGTH 45

// Prototypes
bool check(char *word, node_t* startnode);
bool load(const char *dictionary, node_t* startnode);
unsigned int size(void);
bool unload(void);
void initnode(node_t* n);
int addword(char* word, node_t* top);

#endif // DICTIONARY_H
