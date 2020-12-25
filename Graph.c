#include<stdio.h>
#include<stdlib.h>

const int VERTEXS_NUM = 5;
const int INF = 999;
int weigh_select_queue[100];

int adjacent[VERTEXS_NUM][VERTEXS_NUM] =
{
	{0,4,4,6,6},
	{4,0,2,INF,INF},
	{4,2,0,8,INF},
	{6,INF,8,0,9},
	{6,INF,INF,9,0}
};

int Mst_prim[VERTEXS_NUM][VERTEXS_NUM] =
{
	{0,INF,INF,INF,INF},
	{INF,0,INF,INF,INF},
	{INF,INF,0,INF,INF},
	{INF,INF,INF,0,INF},
	{INF,INF,INF,INF,0},
};

int test[100];
int useable_vertex[VERTEXS_NUM + 1] = { 0,1,2,3,4,-1 };
int visited_vertex[5] = { INF,INF,INF,INF,INF };
struct List_head
{
	int which_vertex;
	struct List* next;
};

struct List
{
	int source_vertex;
	int vertex;
	int weight;
	struct List* prev;
	struct List* next;
};


struct List_head* vertex_0 = (struct List_head*)malloc(sizeof(struct List_head));
struct List_head* vertex_1 = (struct List_head*)malloc(sizeof(struct List_head));
struct List_head* vertex_2 = (struct List_head*)malloc(sizeof(struct List_head));
struct List_head* vertex_3 = (struct List_head*)malloc(sizeof(struct List_head));
struct List_head* vertex_4 = (struct List_head*)malloc(sizeof(struct List_head));
struct List_head* vertex_head[VERTEXS_NUM] = { vertex_0,vertex_1,vertex_2,vertex_3,vertex_4 };


void Init_adjacent_list(struct List_head* vertex_head, int neigbour_vertex, int weight)
{
	struct List* new_node = (struct List*)malloc(sizeof(struct List));
	new_node->vertex = neigbour_vertex;
	new_node->source_vertex = vertex_head->which_vertex;
	new_node->weight = weight;
	new_node->next = NULL;
	new_node->prev = NULL;
	if (vertex_head->next == NULL)
	{
		vertex_head->next = new_node;
	}
	else
	{
		struct List* head = vertex_head->next;
		while (head->next)
		{
			head = head->next;
		}
		head->next = new_node;
		new_node->prev = head;
	}
}

void Traversal(struct List_head* head)
{
	struct List* vertex = head->next;
	while (vertex)
	{
		printf("vertex is %d", vertex->vertex);
		printf(". weight is %d\n", vertex->weight);
		vertex = vertex->next;
	}
}

int Min(int* arrary) //返回相接最小权重的顶点
{
	int weigh = INF;
	int vertex = -1;
	for (int i = 0; i < VERTEXS_NUM; i++)
	{
		if (*arrary != 0 && *arrary < weigh)
		{
			weigh = *arrary;
			vertex = i;
		}
		arrary++;
	}
	return vertex;
}


void Elemet_copy(int* source, int* destine)
{
	int length = 5; //已知source不会超过5个
	while (length)
	{
		*destine = *source;
		source++;
		destine++;
		length--;
	}
}

void Prim() //用领结矩阵来生成树
{
	int* queue = weigh_select_queue;
	int* start = queue;
	int current_vertex = 0;
	int* visited = visited_vertex;
	while (useable_vertex[current_vertex] != -1)
	{
		visited = visited_vertex;
		visited_vertex[current_vertex] = current_vertex;
		weigh_select_queue[100] = NULL;
		while (*visited != INF)
		{
			Elemet_copy(adjacent[useable_vertex[current_vertex]], queue);
			queue = queue + 5;
			visited++;
		}
		int next_vertex = Min(start);
		Mst_prim[current_vertex][next_vertex] = adjacent[current_vertex][next_vertex];
		Mst_prim[next_vertex][current_vertex] = adjacent[current_vertex][next_vertex];
		visited = visited_vertex;
		while (*visited != INF)
		{
			adjacent[current_vertex][*visited] = INF;
			adjacent[*visited][current_vertex] = INF;
			visited++;
		}
		useable_vertex[current_vertex] = -1;
		current_vertex++;
		queue = start;
	}
}

bool If_visited_all(int* visited_array)
{
	int if_visited_all_flag = -1;
	for (int i = 0; i < VERTEXS_NUM; i++)
	{
		if (if_visited_all_flag < *visited_array)
		{
			if_visited_all_flag = *visited_array;
			visited_array++;
		}
	}
	if (if_visited_all_flag == INF)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Kruskal()  //领接表
{
	int visited_vertex[5] = { INF,INF,INF,INF,INF };
	struct List* weigh_ascent_list;
	struct List* record_min_weigh_node = NULL;
	weigh_ascent_list = vertex_0->next;
	struct List* list_start = weigh_ascent_list;
	struct List* list_start_mark = list_start;
	int destine_vertex;
	int source_vertex = 0;
	int min_weigh = INF;
	for (int i = 1; i < VERTEXS_NUM; i++)
	{
		while (weigh_ascent_list->next)
		{
			weigh_ascent_list = weigh_ascent_list->next;
		}
		weigh_ascent_list->next = vertex_head[i]->next;
		vertex_head[i]->next->prev = weigh_ascent_list;
		weigh_ascent_list = weigh_ascent_list->next;
	}

	while (If_visited_all(visited_vertex))
	{
		while (list_start)
		{
			if (list_start->weight < min_weigh)
			{
				destine_vertex = list_start->vertex;
				min_weigh = list_start->weight;
				source_vertex = list_start->source_vertex;
				record_min_weigh_node = list_start;
			}
			list_start = list_start->next;
		}
		if (record_min_weigh_node->prev)
		{
			record_min_weigh_node->prev->next = record_min_weigh_node->next;
			record_min_weigh_node->next->prev = record_min_weigh_node->prev;
		}
		else if(record_min_weigh_node->prev==NULL)
		{
			list_start_mark = list_start_mark->next;
			list_start_mark->prev = NULL;
		}
		else
		{
			record_min_weigh_node->prev->next = NULL;
		}
		if (visited_vertex[source_vertex] == INF || visited_vertex[destine_vertex] == INF)
		{
			Mst_prim[source_vertex][destine_vertex] = min_weigh;
			Mst_prim[destine_vertex][source_vertex] = min_weigh;
			visited_vertex[source_vertex] = source_vertex;
			visited_vertex[destine_vertex] = destine_vertex;
		}
		min_weigh = INF;
		list_start = list_start_mark;
	}
}

void show_mst()
{
	for (int i = 0; i < VERTEXS_NUM; i++)
	{
		for (int j = 0; j < VERTEXS_NUM; j++)
		{
			if (Mst_prim[i][j] == INF)
			{
				printf("INF ");
			}
			else
			{
				printf("%d ", Mst_prim[i][j]);
			}
		}
		printf("\n");
	}
}


int main()
{
	vertex_0->next = NULL;
	vertex_0->which_vertex = 0;
	vertex_1->next = NULL;
	vertex_1->which_vertex = 1;
	vertex_2->next = NULL;
	vertex_2->which_vertex = 2;
	vertex_3->next = NULL;
	vertex_3->which_vertex = 3;
	vertex_4->next = NULL;
	vertex_4->which_vertex = 4;
	Init_adjacent_list(vertex_0, 1, 4);
	Init_adjacent_list(vertex_0, 2, 4);
	Init_adjacent_list(vertex_0, 3, 6);
	Init_adjacent_list(vertex_0, 4, 6);
	Init_adjacent_list(vertex_1, 0, 4);
	Init_adjacent_list(vertex_1, 2, 2);
	Init_adjacent_list(vertex_2, 0, 4);
	Init_adjacent_list(vertex_2, 1, 2);
	Init_adjacent_list(vertex_2, 3, 8);
	Init_adjacent_list(vertex_3, 0, 6);
	Init_adjacent_list(vertex_3, 2, 8);
	Init_adjacent_list(vertex_3, 4, 9);
	Init_adjacent_list(vertex_4, 0, 6);
	Init_adjacent_list(vertex_4, 3, 9);
	//初始化图的储存

	//Prim();
	//Kruskal();
	//show_mst();



	return 0;
}
