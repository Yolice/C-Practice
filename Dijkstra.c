#include<stdio.h>
#include<stdlib.h>

#define VERTEXS_NUM 6
#define F 999

struct Queue* front;
struct Queue* rear;

int Adjaecent_Array[VERTEXS_NUM][VERTEXS_NUM] =
{
	{0,1,12,F,F,F},
	{F,0,9,3,F,F},
	{F,F,0,F,5,F},
	{F,F,4,0,13,15},
	{F,F,F,F,0,4},
	{F,F,F,F,F,0}
};


struct Queue
{
	int value;
	int weight;
	struct Queue* prev;
	struct Queue* next;
};

void Enqueue(int value)
{
	struct Queue* new_node = (struct Queue*)malloc(sizeof(struct Queue));
	new_node->value = value;
	new_node->weight = F;
	new_node->next = NULL;
	new_node->prev = NULL;
	if (front == NULL && rear == NULL)
	{
		front = new_node;
		rear = new_node;
	}
	else
	{
		rear->next = new_node;
		new_node->prev = rear;
		rear = new_node;
	}
}

int Dequeu()   //优先队列方式出列，出最小权重的顶点
{
	if (rear == front)
	{
		rear = NULL;
		front = NULL;
	}
	else
	{
		int weight = F;
		int min_weight_vertex = -1;
		struct Queue* start = front;
		struct Queue* record = front;
		while (start)
		{
			if (start->weight < weight)
			{
				min_weight_vertex = start->value;
				weight = start->weight;
				record = start;
			}
			start = start->next;
		}

		if (record->prev == NULL)
		{
			front = front->next;
			front->prev = NULL;
		}
		else if (record->next == NULL)
		{
			rear = rear->prev;
			rear->next = NULL;
		}
		else
		{
			record->prev->next = record->next;
			record->next->prev = record->prev;
		}

		return min_weight_vertex;
	}
}

void Traversal(Queue* head)
{
	if (!head)
	{
		printf("Queue is empty!");
		return;
	}
	while (head)
	{
		printf("%d ", head->value);
		head = head->next;
	}
}

void Update_queue(struct Queue* node, int value,int weight)
{
	while (node)
	{
		if (node->value == value)
		{
			node->weight = weight;
			break;
		}
		node = node->next;
	}
}


void Dijkstra_shortest_path()
{
	int distance[VERTEXS_NUM] = { 0,F,F,F,F,F }; //计算1到2-6点的最短距离
	int vertex = Dequeu();
	while (front)
	{
		for (int i = 0; i < VERTEXS_NUM; i++)
		{
			if (Adjaecent_Array[vertex - 1][i] != 0 && Adjaecent_Array[vertex - 1][i] != F)
			{
				if (distance[vertex - 1] + Adjaecent_Array[vertex - 1][i] < distance[i])
				{
					distance[i] = distance[vertex - 1] + Adjaecent_Array[vertex - 1][i];
					Update_queue(front, i + 1, distance[i]);
				}
			}
		}
		for (int i = 0; i < VERTEXS_NUM; i++)
		{
			if (distance[i] == F)
			{
				printf("F ");
			}
			else
			{
				printf("%d ", distance[i]);
			}
		}
		printf("\n");
		vertex = Dequeu();
	}
}


int main()
{
	front = NULL;
	rear = NULL;

	Enqueue(1);
	Enqueue(2);
	Enqueue(3);
	Enqueue(4);
	Enqueue(5);
	Enqueue(6);
	front->weight = 0; //算顶点1到其他所有顶点最短距离

	Dijkstra_shortest_path();

	return 0;
}
