#include <stdio.h>
#include "trie.h"


int main(int argc, char** argv)
{
	trie *r = create_trie_node();
	FILE *fp = NULL;
	char *path;
	char line[1024];
	int n = 0;
	int count = 0;
	int max = 0;
	char max_words[1024];

	if(argc == 2)
		path = argv[1];
	else
	{
		fflush(stdin);
		puts("input a file path:");
		gets(path);
	}

	if(!(fp = fopen(path, "r")))
	{
		puts("can\'t open file!");
		return 1;
	}

	puts("begin!");

	while(fgets(line, 1024, fp))
	// while(gets(line))
	{
		line[strlen(line) - 1] = '\0';
		n = trie_add_record(r, line, 1);
		if(n == 1)
			count++;
		if(n > max)
		{
			max = n;
			strcpy(max_words, line);
		}
		if(strcmp(line, "q") == 0)
			break;
	}

	puts("complete!");
	printf("max_words: %s - %d times\n", max_words, max);
	printf("total words: %d\n", count);

	while(1)
	{
		fflush(stdin);
		gets(line);
		n = is_trie_member(r, line);
		if(n == NOT_EXIST)
			printf("\t%s - %s\n", line, "NULL");
		else
			printf("\t%s - %d\n", line, n);
		if(strcmp("q", line) == 0)
			break;
	}

	return 0;


	// trie_add_record(r, "helloworld", 1);
	// if(NOT_EXIST == is_trie_member(r, "what"))
	// 	puts("FALSE");
	// else
	// 	puts("TRUE");
	// remove_trie_member(r, "helloworld");
	// if(NOT_EXIST == is_trie_member(r, "helloworld"))
	// 	puts("FALSE");
	// else
	// 	puts("TRUE");

	// destroy_trie(r);

	// return 0;
}