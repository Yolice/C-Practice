#include<stdio.h>
#include<stdlib.h>
#include<time.h>

const int INF = -999999;
struct List* head = NULL;

struct List
{
	int value;
	struct List* next;
	struct List* prev;
	struct List* up_level;
	struct List* down_level;
};

struct List* Insert_Operation(struct List* head, int value)  //插入排序,保证链表是有序的
{
	struct List* new_node = (struct List*)malloc(sizeof(struct List));
	new_node->value = value;
	new_node->next = NULL;
	new_node->prev = NULL;
	new_node->up_level = NULL;
	new_node->down_level = NULL;

	//在跳跃表中只有两种case，因为表头一定是负无穷，所以只有插入到末尾或者在中间插入
	while (head->next && value > head->value)
	{
		head = head->next;
	}
	if (head->next == NULL) 
	{
		if (value > head->value)  //case 1：后插入
		{
			head->next = new_node;
			new_node->prev = head;
		}
		else if (value < head->value) //case 2.1: 中间插入,head选到最后一个元素
		{
			struct List* prev = head->prev;
			new_node->next = head;
			head->prev = new_node;
			new_node->prev = prev;
			prev->next = new_node;
		}
	}
	else if (head->next) //case 2.2 ：中间插入,head并不是最后一个元素
	{
		struct List* prev = head->prev;
		new_node->next = head;
		head->prev = new_node;
		new_node->prev = prev;
		prev->next = new_node;
	}
	else
	{
		printf("error!!!!!");  //不应该出现的case
		exit(1);
	}
	return new_node;
}

void Traversal(struct List* head)
{
	while (head)
	{
		if (head->value == INF)
		{
			printf("-INF ");
		}
		else
		{
			printf("%d ", head->value);
		}
		head = head->next;
	}
	printf("\n");
}

struct List* Search(struct List* head,int value)
{
	while (head)
	{
		if (value == head->value)
		{
			return head;
		}
		else
		{
			head = head->next;
		}
	}
	return NULL;
}

void Delete_Operation(struct List* head,int value)
{
	struct List* delete_node = Search(head,value);
	if (delete_node) 
	{
		if (delete_node->next) //case 1:删除的是中间元素
		{
			struct List* prev = delete_node->prev;
			prev->next = delete_node->next;
			delete_node->next->prev = prev;
		}
		else  // case 2:删除是末尾元素
		{
			delete_node->prev->next = NULL;
		}
		//printf("delete successful!\n");
	}
	else
	{
		//printf("delete false no such as value!\n");
	}
}

void Delete(struct List* head, int value)
{
	Delete_Operation(head, value);
	while (head->up_level)
	{
		Delete_Operation(head->up_level, value);
		head = head->up_level;
	}
}

int random_generator()
{
	int res = rand() % 2;
	return res;
}

void Insert(struct List* head, int value)
{
	struct List* origin_layer_node=Insert_Operation(head, value);
	int up_flag = random_generator();
	while (up_flag)
	{
		if (head->up_level)
		{
			struct List* higher_layer_node=Insert_Operation(head->up_level,value);
			origin_layer_node->up_level = higher_layer_node;
			higher_layer_node->down_level = origin_layer_node;
			head = head->up_level;
		}
		else
		{
			struct List* up_level_head = (struct List*)malloc(sizeof(struct List));
			head->up_level = up_level_head;
			up_level_head->value = INF;
			up_level_head->next = NULL;
			up_level_head->up_level = NULL;
			up_level_head->down_level = head;
			struct List* higher_layer_node=Insert_Operation(up_level_head, value);
			origin_layer_node->up_level = higher_layer_node;
			higher_layer_node->down_level = origin_layer_node;
			head = up_level_head;
		}
		up_flag = random_generator();
	}
}

void Find_node(struct List* head,int value)
{
	if (head == NULL)
	{
		printf("node doesn't exist!\n");
		return;
	}
	while (head->next && head->value != value && head->next->value <= value)
	{
		head = head->next;
	}
	if (head->value == value)
	{
		printf("node exist!\n");
		return;
	}
	else
	{
		head = head->down_level;
		Find_node(head, value);
	}
}

void Find(struct List* head, int value)
{
	while (head->up_level)
	{
		head = head->up_level;
	}
	Find_node(head,value);
}

int main()
{
	head = (struct List*)malloc(sizeof(struct List));
	head->value = INF;
	head->next = NULL;
	head->prev = NULL;
	head->up_level = NULL;
	head->down_level = NULL;

	srand((unsigned)time(NULL));//srand()就是给rand()提供种子seed 
	Insert(head, 1);
	Insert(head, 2);
	Insert(head, 3);
	Insert(head, 6);
	Insert(head, 5);
	Insert(head, 4);
	Insert(head, 7);
	Insert(head, 0);
	Insert(head, 9);
	Insert(head, 8);
	Insert(head, 10);
	Insert(head, 11);
	Insert(head, 12);
	Insert(head, 14);
	Insert(head, 13);
	Insert(head, -1);
	Find(head, 1);


	Delete(head, 1);
	Find(head, 1);

	return 0;
}
