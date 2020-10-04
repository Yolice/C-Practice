#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define true 1
#define false 0

const char delimiter[20] = " /-.,:;?!()";

struct List {
	char* word_buffer;
	struct List* next;
};

void reverse_output_word(char* input_word)
{
	char* token = strtok(input_word, delimiter);
	struct List* current = NULL;
	while (token)
	{
		struct List* new_node = (struct List*)malloc(sizeof(struct List));
		new_node->word_buffer = (char*)malloc(sizeof(char) * 20);
		strcpy(new_node->word_buffer,token);
		new_node->next = current;
		current = new_node;
		token = strtok(NULL, delimiter);
	}

	while (current)
	{
		printf("%s ", current->word_buffer);
		current = current->next;
	}
}

int main(int argc, char* argv[])
{
	char query_word[100];
	printf("input your word:");
	gets_s(query_word);
	reverse_output_word(query_word);
	return 0;
}
