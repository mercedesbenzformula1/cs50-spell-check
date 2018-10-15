// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "dictionary.h"


unsigned int wordcount;

// Returns true if word is in dictionary else false
bool check(char* word, node_t* n)
{
    int len = strlen(word);

    for(int i=0; i<len; i++)
    {
    	/* catch if we went down one and it was empty (i.e. word matches all letters but has
    	 * extra crap appended at the end. For instance if we had a word like "testingsth",
    	 * the "testing" part would be good but when we got to the 't' after the 'g', we would
    	 * realize that this word is misspelled
    	 */
    	if(n == NULL)
    	{
    		return false;
    	}

		// make sure character is lower case
		word[i] = tolower(word[i]);

		// keep going to the right until we find something that matches or we reach the end of that level
		while(n->c != word[i] && n->right != NULL)
		{
			n = n->right;
		}

		// we found something that matches, move down to next level
		if(n->c == word[i])
		{
			n = n->down;
		}
		// nothing matches and we reached end of level and nothing matches
		else if(n->right == NULL)
		{
			return false;
		}

   }
   return true;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char* dictionary, node_t* startnode)
{
	FILE* f = fopen(dictionary, "r");
	char* wbuf = calloc(LENGTH+1, sizeof(char)); // word buffer initialized to empty
	//node_t* nodestart = malloc(sizeof(node_t)); // starting point of dictionary
	initnode(startnode);
	wordcount = 0;

	// go through every word in the dictionary
	do
	{
		// grab each word and throw it into buffer.
		fscanf(f, "%s", wbuf);

		// add word to memory structure
		addword(wbuf, startnode);
	} while(!feof(f));

    free(wbuf);
    fclose(f);

	// error checking
	return (wordcount == 0 ? false : true);
}

int addword(char* word, node_t* n)
{
	// just so we don't calculate strlen every time for loop iterates
	int wlen = strlen(word);

	// go through and add every letter in the word
	for(int i=0; i<wlen; i++)
	{
		// go through the list until we find a node with matching letter or we reach end of list on that level
		while(n->c != word[i] && n->right != NULL && n->c != '\0')
		{
			n = n->right;
		}

		// letter matches
		if(n->c == word[i])
		{
			// there is nothing below it yet
			if(n->down == NULL)
			{
				n->down = malloc(sizeof(node_t));
				initnode(n->down);
				n = n->down;
			}
			// there alread are letters below it
			else
			{
				n = n->down;
			}
		}
		// no leter at this level has been set yet
		else if(n->c == '\0')
		{
			n->c = word[i];
			n->down = malloc(sizeof(node_t));
			initnode(n->down);
			n = n->down;
		}
		// it must be end of list, letter doesn't match anywhere so add it to end
		else if(n->right == NULL)
		{
			// create new node on this level and add letter
			n->right = malloc(sizeof(node_t));
			n = n->right;
			n->c = word[i];

			// create a pointer down and move down to next level
			n->down = malloc(sizeof(node_t));
			initnode(n->down);
			n = n->down;
		}
	}

	wordcount++;
	return 0;
}

// just initilize everything in the node to nothing
void initnode(node_t* n)
{
	n->c = '\0';
	n->right = NULL;
	n->down = NULL;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return wordcount;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    return false;
}
