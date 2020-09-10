#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//记录一段文本的单词出现频率
#define true 1
#define false 0



struct Node
{
	char* record_word; //动态申请数组大小
	int frequency;
	struct Node* next;
};

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

int Search_Same_name(struct Node* head, char* compare_name)
{
	head = head->next;
	while (head)
	{
		if (!(strcmp(head->record_word, compare_name)))  //如果等于
		{
			return true;
		}
		head = head->next;
	}
	return false;
}

void CreateNode_with_name(char* name_points, struct Node* head)
{
	struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
	new_node->record_word = (char*)malloc(sizeof(char) * 100);
	new_node->frequency = 1;
	new_node->next = NULL;
	int Flag = Search_Same_name(head, name_points);
	if (Flag)
	{
		while (head->next)
		{
			if (!(strcmp(head->record_word, name_points)))
			{
				head->frequency++;
				return;
			}
			head = head->next;
		}
	}
	while (head->next)
	{
		head = head->next;
	}
	strcpy(new_node->record_word, name_points);
	head->next = new_node;
}


void TraversalList(struct Node* head)
{
	head = head->next;
	while (head)
	{
		printf("%s:%d\n", head->record_word, head->frequency);
		head = head->next;
	}
}

void Counter_any_words_frequency(char* buffer_points, struct Node* head)
{
	const char delimiter[20] = " .,:;?!()\n";
	char* token = strtok(buffer_points, delimiter);
	while (token)
	{
		CreateNode_with_name(token, head);
		token = strtok(NULL, delimiter);
	}
}


int main(int argc, char* argv[])
{
	struct Node* head = (struct Node*)malloc(sizeof(struct Node));
	head->record_word = (char*)malloc(sizeof(char) * 100);
	strcpy(head->record_word, "");
	head->frequency = 0;
	head->next = NULL;
	FILE* fp = fopen(argv[1], "r");
	char buffer_temp[100] = { "" };
	char* buffer_temp_point = buffer_temp;
	char buffer[10000] = { "" };
	char* buffer_point = buffer;
	//char buffer[10000] = {"A WALNUT \n As soft as silk, as white as milk, \n As bitter as gall, a strong wall,\n And a green coat covers me all." };
	//char buffer[10000] = { "THE CAT AND THE FIDDLE \n Hey, diddle, diddle! \n The cat and the fiddle, \nThe cow jumped over the moon; \n The little dog laughed \nTo see such sport, \n And the dish ran away with the spoon. " };
	while (fgets(buffer_temp, 100, fp) != NULL)
	{
		strcat(buffer, buffer_temp);
	}
	char* upper_point = buffer;
	Upper_any_words(buffer);
	Counter_any_words_frequency(buffer, head);
	TraversalList(head);
	fclose(fp);
	return 0;
}


