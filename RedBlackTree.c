#include<stdio.h>
#include<stdlib.h>

enum Color
{
	BLACK,RED
};

struct Tree_node
{
	Color color;
	int value;
	struct Tree_node* parent;
	struct Tree_node* left;
	struct Tree_node* right;
};

Tree_node* root = NULL;

void Left_rotation(struct Tree_node* current_node)
{
	if (current_node == root)
	{
		struct Tree_node* temp = current_node->right->left;
		current_node->right->left = current_node;
		current_node->parent = current_node->right;
		if (temp)
		{
			temp->parent = current_node;
			current_node->right = temp;
		}
		else
		{
			current_node->right = NULL;
		}
		root = current_node->parent;
	}
	else
	{
		if (current_node->value < current_node->parent->value) //左子树
		{
			current_node->parent->left = current_node->right;
		}
		else   //右子树
		{
			current_node->parent->right = current_node->right;
		}
		struct Tree_node* temp = current_node->right->left;
		current_node->right->left = current_node;
		current_node->right->parent = current_node->parent;
		current_node->parent = current_node->right;
		if (temp)
		{
			temp->parent = current_node;
			current_node->right = temp;
		}
		else
		{
			current_node->right = NULL;
		}
	}
}

void Right_rotation(struct Tree_node* current_node)
{
	if (current_node == root)
	{
		struct Tree_node* temp = current_node->left->right;
		current_node->left->right = current_node;
		current_node->parent = current_node->left;
		if (temp)
		{
			temp->parent = current_node;
			current_node->left = temp;
		}
		else
		{
			current_node->left = NULL;
		}
		root = current_node->parent;
	}
	else
	{
		if (current_node->value < current_node->parent->value) //左子树
		{
			current_node->parent->left = current_node->left;
		}
		else   //右子树
		{
			current_node->parent->right = current_node->left;
		}
		struct Tree_node* temp = current_node->left->right;
		current_node->left->right = current_node;
		current_node->left->parent = current_node->parent;
		current_node->parent = current_node->left;
		if (temp)
		{
			temp->parent = current_node;
			current_node->left = temp;
		}
		else
		{
			current_node->left = NULL;
		}
	}

}

void Balance_operation(struct Tree_node* current_node)
{
	if (current_node == root)
	{
		root->color = BLACK;
		return;
	}
	if (current_node->parent->color == BLACK)
	{
		return;
	}
	if (current_node->parent->value < current_node->parent->parent->value && ( current_node->parent->parent->right == NULL || current_node->parent->parent->right->color==BLACK ))  //父节点是左儿子
	{
		if (current_node->value < current_node->parent->value)
		{
			current_node->parent->color = BLACK;
			current_node->parent->parent->color = RED;
			Right_rotation(current_node->parent->parent);
		}
		else
		{
			struct Tree_node* parent_node = current_node->parent;
			Left_rotation(current_node->parent);
			Balance_operation(parent_node);

		}
	}
	else if (current_node->parent->value > current_node->parent->parent->value && (current_node->parent->parent->left==NULL || current_node->parent->parent->left->color == BLACK))
	{
		if (current_node->value > current_node->parent->value)
		{
			current_node->parent->color = BLACK;
			current_node->parent->parent->color = RED;
			Left_rotation(current_node->parent->parent);
		}
		else
		{
			struct Tree_node* parent_node = current_node->parent;
			Right_rotation(current_node->parent);
			Balance_operation(parent_node);
		}
	}
	else if (current_node->parent->parent->left->color == RED && current_node->parent->parent->right->color == RED) //叔父节点都为红时
	{
		current_node->parent->parent->color = RED;
		current_node->parent->parent->left->color = BLACK;
		current_node->parent->parent->right->color = BLACK;
		Balance_operation(current_node->parent->parent);
	}
}

void Insert(Tree_node* insert_node,Tree_node* root)
{
	if (insert_node->value < root->value)
	{
		if (root->left == NULL)
		{
			root->left = insert_node;
			insert_node->parent = root;
			if (root->color == RED)
			{
				Balance_operation(insert_node);  //对插入节点做平衡检查
			}
		}
		else
		{
			Insert(insert_node, root->left);
		}
	 }
	else
	{
		if (root->right == NULL)
		{
			root->right = insert_node;
			insert_node->parent = root;
			if (root->color == RED)
			{
				Balance_operation(insert_node);
			}
		}
		else
		{
			Insert(insert_node, root->right);
		}
	}
}


void Insert_node(int value)
{
	if (root == NULL)
	{
		Tree_node* new_node = (struct Tree_node*)malloc(sizeof(struct Tree_node));
		new_node->color = BLACK;
		new_node->parent = NULL;
		new_node->left = NULL;
		new_node->right = NULL;
		new_node->value = value;
		root = new_node;
		return;
	}
	Tree_node* new_node = (struct Tree_node*)malloc(sizeof(struct Tree_node));
	new_node->color = RED;
	new_node->parent = NULL;
	new_node->left = NULL;
	new_node->right = NULL;
	new_node->value = value;
	Insert(new_node, root);
}



void Traversal(struct Tree_node* head)
{
	if (head == NULL)
	{
		return;
	}
	printf("values:%d ", head->value);
	if (head->color)
	{
		printf("colors:red\n");
	}
	else 
	{
		printf("colors:black\n");
	}
	Traversal(head->left);
	Traversal(head->right);
}

int main()
{
	Insert_node(12);
	Insert_node(1);
	Insert_node(9);
	Insert_node(2);
	Insert_node(0);
	Insert_node(11);
	Insert_node(7);
	Insert_node(19);
	Insert_node(4);
	Insert_node(15);
	Insert_node(18);
	Insert_node(5);
	Insert_node(14);
	Insert_node(13);
	Insert_node(10);
	Insert_node(16);
	Insert_node(6);
	Insert_node(3);
	Insert_node(8);
	Insert_node(17);
	Traversal(root);
	return 0;
}
