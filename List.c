#include <stdio.h>
#include <stdlib.h>

typedef struct node{
	int data;
	struct node* next;
}Node;

typedef struct d_node{
	int data;
	struct d_node *prev;
	struct d_node *next;
}; 

typedef struct List{
	struct node *head;
	struct node* InitialList(int first,int last); //value表示默认会构造一个[first-value]的顺序链表,并且返回一个头指针 
	void InsertList(struct node *head,int index,int value); //index是插入的索引值，在index的位置后插入新的值 。插入分为head后第一个，中间，以及最后一个插入三种情况。
	void DeleteList(struct node *head,int value);//删除索引值为index的结点
	int FindNode(struct node *head,int value);//找到值为value的结点，并返回他的索引值
	void TraverlList(struct node *head);//从头结点开始遍历整个链表 ,返回整个链表元素个数 
}List;

struct node* InitialList(int first,int last)
{
	struct node *head=NULL;
	struct node *prev=NULL;
	struct node *current=NULL;
	for (int i=first;i<=last;i++)
	{
		if(head==NULL)
		{
			current=(struct node*)malloc(sizeof(struct node*));
			current->data=i;
			head=current;
			prev=current;
			current->next=NULL;
			continue;
		}
		current=(struct node*)malloc(sizeof(struct node*));
		current->data=i;  //初始化申请的结点 
		current->next=NULL;  //这一步是必要的 
		prev->next=current; //交换current和prev，需要prev来指向插入位置的前一个位置 
		prev=current; //指向current 
	}
	return head; //返回head指向的地址 
}

void InsertList(struct node *head,int index,int value)
{
	struct node* newnode;
	newnode=(struct node*)malloc(sizeof(struct node*));
	newnode->data=value;
	if(index==0)   //如果在头插入 
	{
		newnode->next=head->next;  //注意两条语句的顺序 
		head->next=newnode;
	}
	else
	{
		for(int i=0;i<index;i++)
		{
			head=head->next;
		}
		newnode->next=head->next;
		head->next=newnode;
	}
}


int FindNode(struct node *head,int value)
{
	int index=0;
    while(head!=NULL)
	{
		if(head->data==value)
		{
			return index;
		}
		else
		{
			index++;
			head=head->next;
		}
	}	
	return -1;//查找失败 
}


int DeleteList(struct node *head,int value)
{
	int result=FindNode(head,value);
	if(result==-1)
	{
		return -1;
	}
	for(int i=0;i<result-1;i++)
	{
		head=head->next;
	}
	head->next=head->next->next;
}


int TraversalList(struct node* head)
{
	int length=0;
	while(head!=NULL)
	{
		printf("List element is %d\n",head->data);
		head=head->next;
		length++;
	}
	return length;
}



int main()
{
	struct node *head=InitialList(0,10);
	printf("%d",TraversalList(head)); 
	return 0;
}
 
