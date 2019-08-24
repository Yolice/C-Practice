#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*malloc没有检测指针是否是NULL*/

typedef struct sort {
	//int list[10] = { 6,3,1,9,8,2,5,4,7,0 };
	int list[10] = { 1,2,3,4,5,6,7,8,9,10 };
	int length = sizeof(list) / sizeof(int);  //总数据长度除以单个数据长度等于数据个数
	void Bubble_sort(int* list);
	void Quick_sort(int* list);
	bool BinarySearch(int left,int right,int value);
}Sort;

typedef struct hash_table {

}Hash;

typedef struct node {
	int data;
	struct node* next=NULL;
}Node;

typedef struct List {   //在insert和delete等操作时候用temp来代替head移动结点，head还是要指向第一个结点不动
	struct node* head=NULL;
	void InitialList(int first, int last); //初始化head永远指向头，prev指向未插入时的最后一个结点，newnode指向准备插入的新结点 
	void InsertList(int index, int value); //index是插入的索引值，在index的位置后插入新的值 。插入分为head后第一个，中间，以及最后一个插入三种情况。
	int DeleteList(int value);//删除索引值为index的结点
	int FindNode(int value);//找到值为value的结点，并返回他的索引值
	int TraversalList();//从头结点开始遍历整个链表 ,返回整个链表元素个数 
}List;

typedef struct stack { //前插入栈前删出栈
	struct node* top=NULL;   //top=NULL时有空栈,top永远指向栈顶。
	bool is_empty();
	void Push(int value);
	int Pop();
	void Traversal();
}Stack;

typedef struct queue{    //后插入队前删出队
	struct node* front=NULL;
	struct node* rear=NULL;
	bool is_empty();
	void enqueue(int value);
	int dequeue();
	void Traversal();
}Queue;

typedef struct tree_node {
	int data;
	struct tree_node* left = NULL;
	struct tree_node* right = NULL;
	struct tree_node* parent = NULL;

}Tree_node;

typedef struct BinarySearchTree
{
	struct tree_node* root=NULL;   //root是指向树结点的指针
	void InitialBinarySearchTree(struct tree_node* root_node,int value); 
	bool DeleteTreeNode(struct tree_node* root_node,int value);   //删除值为value的结点
	struct tree_node* FindNode(struct tree_node* root_node,int value);
	struct tree_node* FindMinNode(struct tree_node* root_node);     //如果被删除的结点有两个叶子，那么从右子树中跳最小结点来代替被删除的结点
	void PreTraversal(struct tree_node* root_node);
	void MidTraversal(struct tree_node* root_node);
	void RearTraversal(struct tree_node* root_node);
}BST;

typedef struct UnionFind
{
	int pre[10];
	int find(int root);
	void join(int x, int y);
}unionfind;

void sort::Bubble_sort(int *list)
{
	int temp = 0;
	for (int i = length-1; i >0; i--)
	{
		for (int j = 0; j < i; j++)
		{
			if (list[j] > list[j + 1])
			{
				temp = list[j];
				list[j] = list[j + 1];
				list[j + 1] = temp;
			}
		}
	}
}

bool sort::BinarySearch(int left, int right,int value)
{
	if (left >= right)
	{
		return false;
	}
	int mid = (left + right) / 2;
	if (list[mid] == value)
	{
		return true;
	}
	else if (value < list[mid])
	{
		BinarySearch(left, mid - 1, value);
	}
	else if (value > list[mid])
	{
		BinarySearch(mid + 1, right, value);
	}
}

void sort::Quick_sort(int* list)
{
	
}

int UnionFind::find(int root)
{
	while (pre[root] != root)
	{
		root = pre[root];
	}
	return root;
}

void UnionFind::join(int x, int y)
{
	int root_x = find(x);
	int root_y = find(y);
	if (root_x != root_y)
	{
		pre[root_x] = root_y;
	}
}

struct tree_node* BinarySearchTree::FindMinNode(struct tree_node* root_node)
{
	struct tree_node* Max_node = root_node;
	while (Max_node->left)
	{
		Max_node = Max_node->left;
	}

	return Max_node;
}

bool BinarySearchTree::DeleteTreeNode(struct tree_node* root_node,int value)   //没有写完，还未考虑完所有的情况
{
	struct tree_node* Node = FindNode(root, value);
	if (Node == NULL)
	{
		printf("找不到删除的值");
		return false;
	}
	else
	{
		if (Node->left && Node->right)  //第一种情况，被删除结点有两个子结点时
		{
			struct tree_node* replace_node=FindMinNode(Node->right);
			if (Node->parent == NULL)   //如果被删除的结点是根结点
			{
				Node->left->parent = replace_node;
				Node->right->parent = replace_node;
				if (replace_node->right != NULL)    //也存replace_node->left==NULL情况，需另外讨论
				{
					replace_node->right->parent = replace_node->parent;
					replace_node->parent->left = replace_node->right;

				}
				replace_node->left = Node->left;
				replace_node->right = Node->right;
				root = replace_node;
				free(Node);
				return true;
			}
			//左处理未完成
			//if (Node->parent->left && Node->parent->left->data == Node->data) //如果是左子结点
			//{
			//	if (replace_node->right != NULL)
			//	{
			//		replace_node->right->parent = replace_node->parent;
			//		replace_node->parent->left = replace_node->right;

			//	}
			//	replace_node->parent = Node->parent;
			//	Node->left->parent = replace_node;
			//	Node->right->parent = replace_node;
			//	replace_node->left = Node->left;
			//	replace_node->right = Node->right;
			//	Node->parent->left = replace_node;
			//	replace_node->parent->left = NULL;
			//	free(Node);
			//	return true;

			//}
			else if (Node->parent->right && Node->parent->right->data == Node->data) //如果是右子结点
			{
				if (replace_node->right != NULL)
				{
					replace_node->right->parent = replace_node->parent;
					replace_node->parent->left = replace_node->right;
				}
				replace_node->parent = Node->parent;
				Node->left->parent = replace_node;
				Node->right->parent = replace_node;
				replace_node->left = Node->left;
				replace_node->right = Node->right;
				Node->parent->right = replace_node;
				free(Node);
				return true;
			}
		}
	}
}

struct tree_node* BinarySearchTree::FindNode(struct tree_node* root_node, int value)
{
	if (root_node == NULL)    //终止递归用if来判断
	{
		return false;
	}
	else
	{
		if (root_node->data == value)
		{
			return root_node;
		}
		else if (value < root_node->data)
		{
			FindNode(root_node->left, value);
		}
		else if (value > root_node->data)
		{
			FindNode(root_node->right, value);
		}
	}
}

void BinarySearchTree::InitialBinarySearchTree(struct tree_node* root_node,int value)
{
	struct tree_node* new_node = (struct tree_node*)malloc(sizeof(struct tree_node));
	if (new_node == NULL)
	{
		exit(1);
	}
	new_node->data = value;
	new_node->left = NULL;
	new_node->right = NULL;  //left和right初始化NULL是必不可少的
	new_node->parent = NULL;
	if (root_node == NULL)  //只存在于第一次创建root结点时的情况
	{
		root_node = new_node;
		if (root == NULL)
		{
			root = root_node;
		}
	}
	else
	{
		if (value < root_node->data)
		{
			if (root_node->left == NULL)
			{
				root_node->left = new_node;
				new_node->parent = root_node;
			}
			else
			{
				InitialBinarySearchTree(root_node->left, value);
			}
		}
		else
		{
			if (root_node->right == NULL)
			{
				root_node->right = new_node;
				new_node->parent = root_node;
			}
			else
			{
				InitialBinarySearchTree(root_node->right, value);
			}
		}
	}
}

void BinarySearchTree::PreTraversal(struct tree_node* root_node)
{
	if (root_node)   //树的遍历因为用到了函数递归，所以要用if而不是while，while的情况下在当前循环root_node永远是真的所以会死循环
	{
		printf("elemnt is %d\n", root_node->data);
		PreTraversal(root_node->left);
		PreTraversal(root_node->right);
	}
}

void BinarySearchTree::MidTraversal(struct tree_node* root_node)
{
	if (root_node)
	{
		MidTraversal(root_node->left);
		printf("elemnt is %d\n", root_node->data);
		MidTraversal(root_node->right);
	}
}

void BinarySearchTree::RearTraversal(struct tree_node* root_node)
{
	if (root_node)
	{
		RearTraversal(root_node->left);
		RearTraversal(root_node->right);
		printf("elemnt is %d\n", root_node->data);
	}
}

bool queue::is_empty()
{
	if (front == NULL && rear == NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void queue::enqueue(int value)
{
	struct node* new_node = (struct node*)malloc(sizeof(struct node));
	/*if (new_node == NULL)
	{
		printf("false");
		exit(1);
	}*/
	new_node->data = value;
	new_node->next = NULL;
	if (front == NULL && rear == NULL)
	{
		front = new_node;
		rear = new_node;
	}
	else
	{
		rear->next = new_node;
		rear = new_node;   //因为front和rear都是指向头结点，所以rear->next=new_node等于front->next=new_node的效果
	}
}

int queue::dequeue()
{
	if (!is_empty())
	{
		int result = front->data;
		struct node* p = front;
		front = front->next;
		free(p);
		return result;
	}
	else
	{
		printf("false");
		return 1;
	}

}

void queue::Traversal()
{
	struct node* temp = front;
	while (temp != NULL)
	{
		printf("element is %d\n", temp->data);
		temp = temp->next;
	}
}

bool stack::is_empty()
{
	if (top == NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void stack::Push(int value)
{
	struct node* new_node = (struct node*)malloc(sizeof(struct node));
	new_node->data = value;
	if (top == NULL)
	{
		new_node->next = NULL;
		top = new_node;
	}
	else
	{
		new_node->next = top;
		top = new_node;
	}
}

int stack::Pop()
{
	int result=0;
	struct node* p = top;

	if (!is_empty())
	{
		result = top->data;
		top = top->next;
	}
	free(p);
	return result;
}

void stack::Traversal()
{
	struct node* temp = top;
	while (temp != NULL)
	{
		printf("%d\n", temp->data);
		temp = temp->next;
	}
}

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
	a.TraversalList();
	Stack a;
	a.Push(10);
	a.Push(20);
	printf("%d\n",a.Pop());
	a.Push(30);
	a.Push(40);
	a.Traversal();
	Queue a;
	a.enqueue(0);
	a.enqueue(10);
	a.enqueue(20);
	a.dequeue();
	a.Traversal();
	BinarySearchTree a;
	a.InitialBinarySearchTree(a.root,41);
	a.InitialBinarySearchTree(a.root, 20);
	a.InitialBinarySearchTree(a.root, 65);
	a.InitialBinarySearchTree(a.root, 11);
	a.InitialBinarySearchTree(a.root, 29);
	a.InitialBinarySearchTree(a.root, 32);
	a.InitialBinarySearchTree(a.root, 50);
	a.InitialBinarySearchTree(a.root, 91);
	a.InitialBinarySearchTree(a.root, 72);
	a.InitialBinarySearchTree(a.root, 99);
	a.InitialBinarySearchTree(a.root, 27);
	a.DeleteTreeNode(a.root, 20);
	unionfind a;
	for (int i = 0; i < 10; i++)
	{
		a.pre[i] = i;
	}
	a.join(0, 7);
	a.join(2, 8);
	a.join(7, 8);
	for (int i = 0; i < 10; i++)
	{
		printf("%d,", a.pre[i]);
	}
	*/
	sort a;
	/*a.bubble_sort(a.list);
	for (int i = 0; i < 10; i++)
	{
		printf("%d,",a.list[i]);
	}
	bool b=a.BinarySearch(0, a.length, 10);
	if (b)
	{
		printf("yes");
	}
	else
	{
		printf("false");
	}*/
	return 0;
}
