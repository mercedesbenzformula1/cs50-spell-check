#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"


int main(int argc, const char* argv[])
{
	// boolean to store if we should write to a file or just to stdout
	FILE* out;

	if(argc != 3 && argc != 4)
	{
		printf("Usage: ./speller dictionaryfilepath textfilepath [errorfilepath]\n");
		return 1;
	}
	else if(argc == 4)
	{
		out = fopen(argv[3], "w");
	}

	node_t* startnode = malloc(sizeof(node_t));
	const char* dictpath = argv[1];

	// load dictionary and do error checking
	if(!load(dictpath, startnode))
		return 1;

	FILE* textfile = fopen(argv[2], "r");
	// error checking. Make sure the filepath passed for text file is correct
	if(ferror(textfile))
	{
		return 2;
	}

	// scan through the entire text file
	unsigned int lnum = 1; // starts @ 1 because text editors start with their position stuff at 1, not 0
	unsigned int cnum = 1;
	int wind = 0;
	char word[LENGTH];
	memset(word, '\0', LENGTH);
	while(!feof(textfile))
	{
		char c = fgetc(textfile);

		// update character counter on that line
		cnum++;

		if(!strncmp(word, "grimm11", 7))
		{
			cnum = cnum + 0;
		}

		/* add character to word if doesn't contain special characters
		 * TODO: we need to revise this for events of apostrophes */
		if(isalpha(c))
		{
			word[wind++] = c;//++ increments it after it's executed. saves us from having to make another line of code with "i++;""
		}
		// we've reached the next word. Assumes no words are split between two lines
		//else if(c == ' ' || c == '\n')
		else
		{
			word[wind++] = '\0';

			// run word check
			if(!check(word, startnode))
			{
				if(argc == 4) // we have input of where we want it written
				{
					fprintf(out, "misspelling at %u:%u, \"%s\"\n", lnum, cnum-wind, word);
				}
				else
				{
					printf("misspelling at %u:%u, \"%s\"\n", lnum, cnum-wind, word); //subtracting 1 because we want to minus length
				}
			}

			wind = 0;
		}

		// if we get '\n' it means we reached a new line. Update counters
		if(c == '\n')
		{
			lnum++;
			cnum = 1; // starts at 1 and we've already done a character. Seems counterintuitive
		}
	}
}
