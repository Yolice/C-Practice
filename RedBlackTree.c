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
		printf("There is empty red_black_tree!!!\n");
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

struct Tree_node* Search(int value,struct Tree_node* root)
{
	if (root==NULL)
	{
		return false;
	}
	else if (root->value == value)
	{
		return root;
	}
	else
	{
		if (value < root->value)
		{
			Search(value, root->left);
		}
		else
		{
			Search(value, root->right);
		}
	}
}

void Recolor_Rotation(struct Tree_node* delete_node)
{
	if(delete_node->color == RED || delete_node==root)
	{
		delete_node->color = BLACK; //递归出口2
	}
	else if (delete_node->color == BLACK)
	{
		if (delete_node == delete_node->parent->left)  //如果是左子树
		{
			if (delete_node->parent->right == NULL || delete_node->parent->right->color == BLACK)  //right应该不可能为nil，如果nil违反了红黑树定义,即黑深度不同
			{
				if ((delete_node->parent->right->left == NULL || delete_node->parent->right->left->color == BLACK) && (delete_node->parent->right->right == NULL || delete_node->parent->right->right->color == BLACK))
				{
					delete_node->parent->right->color = RED;
					Recolor_Rotation(delete_node->parent);
				}
				else if ((delete_node->parent->right->right == NULL || delete_node->parent->right->right->color == BLACK) && delete_node->parent->right->left->color == RED)
				{
					delete_node->parent->right->color = RED;
					delete_node->parent->right->left->color = BLACK;
					Right_rotation(delete_node->parent->right);
					Recolor_Rotation(delete_node);
				}
				else if (delete_node->parent->right->right->color == RED)  //递归的出口1
			    {
				delete_node->parent->right->color = delete_node->parent->color;
				delete_node->parent->color = BLACK;
				delete_node->parent->right->right->color = BLACK;
				Left_rotation(delete_node->parent);
			    }
			}
			else if (delete_node->parent->right->color == RED)
			{
				delete_node->parent->right->color = BLACK;
				delete_node->parent->color = RED;
				Left_rotation(delete_node->parent);
				Recolor_Rotation(delete_node);
			}
		}

		else if (delete_node == delete_node->parent->right)  //右子树case
		{
			if (delete_node->parent->left == NULL || delete_node->parent->left->color == BLACK)
			{
				if ((delete_node->parent->left->left == NULL || delete_node->parent->left->left->color == BLACK) && (delete_node->parent->left->right == NULL || delete_node->parent->left->right->color == BLACK))
				{
					delete_node->parent->left->color = RED;
					Recolor_Rotation(delete_node->parent);
				}
				else if ((delete_node->parent->left->left == NULL || delete_node->parent->left->left->color == BLACK) && (delete_node->parent->left->right->color == RED))
				{
					delete_node->parent->left->color = RED;
					delete_node->parent->left->right->color = BLACK;
					Left_rotation(delete_node->parent->left);
					Recolor_Rotation(delete_node);
				}
				else if (delete_node->parent->left->left->color == RED)
			    {
				delete_node->parent->left->color = delete_node->parent->color;
				delete_node->parent->color = BLACK;
				delete_node->parent->left->left->color = BLACK;
				Right_rotation(delete_node->parent);
			    }
			}
			else if (delete_node->parent->left->color == RED)
			{
				delete_node->parent->left->color = BLACK;
				delete_node->parent->color = RED;
				Right_rotation(delete_node->parent);
				Recolor_Rotation(delete_node);
			}
		}
	}
}



void Delete_Operation(struct Tree_node* delete_node)
{
	int temp=0;
	if (delete_node->left == NULL && delete_node->right == NULL)  //case 1 所有case都可以换成case来处理，递归出口
	{
		if (delete_node == root)
		{
			root = NULL;
			return;
		}
		if (delete_node->color == RED)   //红色直接删除即可
		{
			if (delete_node == delete_node->parent->left)
			{
				delete_node->parent->left = NULL;
			}
			else if(delete_node == delete_node->parent->right)
			{
				delete_node->parent->right = NULL;
			}
			free(delete_node);
		}
		else if (delete_node->color == BLACK)
		{
			Recolor_Rotation(delete_node);  //黑色就处理下旋转调色
			if (delete_node == delete_node->parent->left)
			{
				delete_node->parent->left = NULL;
			}
			else if(delete_node == delete_node->parent->right)
			{
				delete_node->parent->right = NULL;
			}
			free(delete_node);
		}

	}
	else if (delete_node->left && delete_node->right == NULL)
	{
		temp = delete_node->value;
		delete_node->value = delete_node->left->value;
		delete_node->left->value = temp;
		Delete_Operation(delete_node->left);
	}
	else if (delete_node->right && delete_node->left == NULL)
	{
		temp = delete_node->value;
		delete_node->value = delete_node->right->value;
		delete_node->right->value = temp;
		Delete_Operation(delete_node->right);
	}
	else if (delete_node->left && delete_node->right)
	{
		temp = delete_node->value;
		struct Tree_node* replace_node=delete_node->right;
		while (replace_node->left)
		{
			replace_node = replace_node->left;
		}
		delete_node->value = replace_node->value;
		replace_node->value = temp;
		Delete_Operation(replace_node);
	}
	else
	{
		printf("error!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");  //这个case不应该出现
		exit(1);
	}
}


void Delete_node(int value)
{
	struct Tree_node* delete_node=Search(value, root);
	if (delete_node)
	{
		Delete_Operation(delete_node);
	}
	else
	{
		printf("False,can't find value\n");
	}
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

	Delete_node(12);
	Delete_node(1);
	Delete_node(9);
	Delete_node(2);
	Delete_node(0);
	Delete_node(11);
	Delete_node(7);
	Delete_node(19);
	Delete_node(4);
	Delete_node(15);
	Delete_node(18);
	Delete_node(5);
	Delete_node(14);
	Delete_node(13);
	Delete_node(10);
	Delete_node(16);
	Delete_node(6);
	Delete_node(3);
	Delete_node(8);
	Delete_node(17);
	Traversal(root);

	return 0;
}
