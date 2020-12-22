#include<stdio.h>
#include<stdlib.h>

const int VERTEXS_NUM = 5;
const int INF = 9999999999999999999;

int adjacent[VERTEXS_NUM][VERTEXS_NUM] =
{
	{0,4,4,6,6},
	{4,0,2,INF,INF},
	{4,2,0,8,INF},
	{6,INF,8,0,9},
	{6,INF,INF,9,0}
};

struct List
{
	int vertex;
	int weight;
	struct List* next;
};


struct List* vertex_0;
struct List* vertex_1;
struct List* vertex_2;
struct List* vertex_3;
struct List* vertex_4;

struct List* adjacent_list[VERTEXS_NUM] = { vertex_0,vertex_1,vertex_2,vertex_3,vertex_4, };



void Traversal(struct List* head)
{
	while (head)
	{
		printf("vertex is %d", head->vertex);
		printf(". weight is %d\n", head->weight);
		head = head->next;
	}
}

int main()
{
	vertex_0, vertex_1, vertex_2, vertex_3, vertex_4 = NULL;

	Traversal(vertex_0);
	return 0;
}
