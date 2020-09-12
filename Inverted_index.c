#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define true 1
#define false 0

struct WORD_WITH_TF
{
	char* file_name;
	int frequency;
	struct WORD_WITH_TF* next;
};

struct WORD
{
	char* word_name;
	struct WORD_WITH_TF* current_word;
	struct WORD* crash_list;
};

char* Direct_Document = "C:\\Users\\yolic\\source\\repos\\Where\\Debug\\corpusWP\\";

struct WORD* Word_hash_array[100000];

void Upper_any_words(char* buffer_points)
{
	while (*buffer_points)
	{
		if ((*buffer_points) >= 'a' && (*buffer_points) <= 'z')
		{
			*buffer_points -= 32;
		}
		buffer_points++;
	}
}


unsigned int APHash(char* str)
{
	unsigned int hash = 0;
	int i;

	for (i = 0; *str; i++)
	{
		if ((i & 1) == 0)
		{
			hash ^= ((hash << 7) ^ (*str++) ^ (hash >> 3));
		}
		else
		{
			hash ^= (~((hash << 11) ^ (*str++) ^ (hash >> 5)));
		}
	}

	return (hash & 0x7FFFFFFF) % 100000;
}

char* Return_all_text(char* file_name)
{
	FILE* fp = fopen(file_name, "r");
	if (!fp)
	{
		printf("open error");
		exit(1);
	}
	char buffer_temp[1000] = { "" };
	char buffer[10000] = { "" };
	while (fgets(buffer_temp, 1000, fp) != NULL)
	{
		strcat(buffer, buffer_temp);
	}
	fclose(fp);
	return buffer;
}


void Build_word_information(char* word, char* file_name)  
{
	int addr_word = APHash(word);
	if (!Word_hash_array[addr_word]) 
	{
		struct WORD* new_word = (struct WORD*)malloc(sizeof(struct WORD));
		new_word->word_name = (char*)malloc(sizeof(char) * 20);
		strcpy(new_word->word_name, word);
		new_word->current_word = (struct WORD_WITH_TF*)malloc(sizeof(struct WORD_WITH_TF));
		new_word->current_word->file_name = (char*)malloc(sizeof(char) * 20);
		strcpy(new_word->current_word->file_name, file_name);
		new_word->current_word->frequency = 1;
		new_word->current_word->next = NULL;
		Word_hash_array[addr_word] = new_word;
	}
	else if (!strcmp(Word_hash_array[addr_word]->word_name, word)) 
	{
		{
			struct WORD* hash_element = Word_hash_array[addr_word];
			struct WORD_WITH_TF* hash_element_current_word = hash_element->current_word;
			while (hash_element_current_word->next) 
			{
				if (!strcmp(hash_element_current_word->file_name, file_name))
				{
					hash_element_current_word->frequency++;
				}
				hash_element_current_word = hash_element_current_word->next;
			}
			if (!strcmp(hash_element_current_word->file_name, file_name))   //最后一个元素
			{
				hash_element_current_word->frequency++;
			}
			else  //如果连最后一个元素都不是的话
			{
				struct WORD_WITH_TF* new_file = (struct WORD_WITH_TF*)malloc(sizeof(struct WORD_WITH_TF));
				new_file->file_name = (char*)malloc(sizeof(char) * 20);
				strcpy(new_file->file_name, file_name);
				new_file->frequency = 1;
				new_file->next = NULL;
				hash_element_current_word->next = new_file;
			}
		}
	}
	else
	{
		//printf("crash");  
	}
}

void Build_inverted_index(char* all_text, char* file_name)
{
	Upper_any_words(all_text);
	const char delimiter[20] = " /-.,:;?!()\n";
	char* token = strtok(all_text, delimiter);
	while (token)
	{
		Build_word_information(token, file_name);
		token = strtok(NULL, delimiter);
	}
}

void Traversal()
{
	int i = 0;
	while (i < 100000)
	{
		if (Word_hash_array[i])
		{
			struct WORD* elem = Word_hash_array[i];
			printf("单词是:%s ", Word_hash_array[i]->word_name);
			while (Word_hash_array[i]->current_word)
			{
				printf(" 所属文件为:%s,", Word_hash_array[i]->current_word->file_name);
				printf("出现频率为%d", Word_hash_array[i]->current_word->frequency);
				Word_hash_array[i]->current_word = Word_hash_array[i]->current_word->next;
			}
			printf("\n");
		}
		i++;
	}
}

void Build_Inverted_index_all_text()
{
	char file_direct[100];
	for (int i = 1; i < 10; i++)
	{
		char file_number[] = "wp00";
		char postfix[] = { ".txt" };
		char file_name[20];
		sprintf(file_name, "%s%d%s", file_number, i, postfix);
		sprintf(file_direct, "%s%s", Direct_Document, file_name);
		char* all_text = Return_all_text(file_direct, file_name);
		Build_inverted_index(all_text, file_name);
	}
	for (int i = 11; i < 99; i++)
	{
		char file_number[] = "wp0";
		char postfix[] = { ".txt" };
		char file_name[20];
		sprintf(file_name, "%s%d%s", file_number, i, postfix);
		sprintf(file_direct, "%s%s", Direct_Document, file_name);
		char* all_text = Return_all_text(file_direct, file_name);
		Build_inverted_index(all_text, file_name);
	}
	for (int i = 100; i < 221; i++)
	{
		char file_number[] = "wp";
		char postfix[] = { ".txt" };
		char file_name[20];
		sprintf(file_name, "%s%d%s", file_number, i, postfix);
		sprintf(file_direct, "%s%s", Direct_Document, file_name);
		char* all_text = Return_all_text(file_direct, file_name);
		Build_inverted_index(all_text, file_name);
	}
}

void Response_system(char* query)
{
	Upper_any_words(query);
	Build_Inverted_index_all_text();
	int addr = APHash(query);
	if (!Word_hash_array[addr])
	{
		printf("There is no any information about this word..\n");
		exit(1);
	}
	struct WORD_WITH_TF* query_word = Word_hash_array[addr]->current_word;
	int most_frequency = 0;
	char text_name[100];
	char output_buffer[500];
	while (query_word->next)
	{
		if (query_word->frequency >= most_frequency)
		{
			strcpy(text_name, query_word->file_name);
			most_frequency = query_word->frequency;
		}
		query_word = query_word->next;
	}
	char response_direct[100] = { "" };
	strcpy(response_direct, Direct_Document);
	strcat(response_direct, text_name);
	
	printf("\n\n");
	printf("%s:", Word_hash_array[addr]->word_name);
	FILE* fp = fopen(response_direct, "r");
	if (fp == NULL)
	{
		printf("open error");
	}
	while (fgets(output_buffer, 500, fp))
	{
		printf("%s ", output_buffer);
	}
	fclose(fp);
}

int main(int argc, char* argv[])
{
	char query_word[20];
	printf("input your query word:");
	scanf("%s", query_word);
	Response_system(query_word);
	return 0;
}


