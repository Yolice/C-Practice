#include <stdio.h>
#include <stdlib.h>

/*malloc没有检测指针是否是NULL*/


typedef struct node {
	int data;
	struct node* next;
}Node;


typedef struct List {
	struct node* head=NULL;
	void InitialList(int first, int last); //value表示默认会构造一个[first-value]的顺序链表,并且返回一个头指针 
	void InsertList(int index, int value); //index是插入的索引值，在index的位置后插入新的值 。插入分为head后第一个，中间，以及最后一个插入三种情况。
	int DeleteList(int value);//删除索引值为index的结点
	int FindNode(int value);//找到值为value的结点，并返回他的索引值
	int TraversalList();//从头结点开始遍历整个链表 ,返回整个链表元素个数 
}List;

typedef struct stack {
	struct node* top;

}Stack;

void  List::InitialList(int first, int last)
{

	struct node* prev = NULL;
	struct node* current = NULL;
	for (int i = first; i <= last; i++)
	{
		if (head == NULL)
		{
			current = (struct node*)malloc(sizeof(struct node));
			current->data = i;
			head = current;
			prev = current;
			current->next = NULL;
			continue;
		}
		current = (struct node*)malloc(sizeof(struct node*));
		current->data = i;  //初始化申请的结点 
		current->next = NULL;  //这一步是必要的 
		prev->next = current; //交换current和prev，需要prev来指向插入位置的前一个位置 
		prev = current; //指向current 
	}
}

void List::InsertList(int index, int value)
{
	struct node* newnode;
	newnode = (struct node*)malloc(sizeof(struct node*));  
	struct node* temp = head;    //head应该始终指向链表头，使用temp来零时操作链表
	newnode->data = value;
	if (index == 0)   //如果在头插入 
	{
		newnode->next = head;
		head = newnode;
		temp = newnode;
	}
	else
	{
		for (int i = 0; i < index; i++)
		{
			temp = temp->next;
		}
		newnode->next = temp->next;
		temp->next = newnode;
	}
}


int List::FindNode(int value)
{
	int index = 0;
	struct node* temp = head;  //head应该始终指向链表头，使用temp来零时操作链表

	while (temp != NULL)
	{
		if (temp->data == value)
		{
			return index;
		}
		else
		{
			index++;
			temp = temp->next;
		}
	}
	return -1;//查找失败 
}


int List::DeleteList(int value)
{
	int result = FindNode(value);
	struct node* temp = head;
	if (result == -1)
	{
		return -1;
	}
	else 
	{
		if (result == 0) //如果删除的第一个结点
		{
			head = head->next;
		}
		else 
		{
			for (int i = 0; i < result - 1; i++)
			{
				temp = temp->next;
			}
			temp->next = temp->next->next;  //停留在要被删除的结点的前一个结点
			return 1;
		}
		
	}
}


int List::TraversalList()
{
	int length = 0;
	struct node* temp = head;
	while (temp != NULL)
	{
		printf("List element is %d\n", temp->data);
		temp= temp->next;
		length++;
	}
	return length;  //返回链表的长度
}



int main()
{
	/*List a;
	a.InitialList(0, 10);
	a.InsertList(0, 100);
	a.DeleteList(8);
	a.DeleteList(100);
	a.TraversalList();*/
	
	return 0;
}
