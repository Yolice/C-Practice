// ConsoleApplication1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include<stdio.h>

int unsort_list[100] = {3,44,38,5,47,15,36,26,27,2,46,4,19,50,48};
const int length = 15;
const int counting_length = 9;
void print_list(int* first)
{
	int i = 0;
	while (i<length)
	{
		printf("%d ",unsort_list[i]);
		i++;
	}
}

void select_sort(int* unsort_list)
{
	int temp = 0;
	for (int i = 0; i < length; i++)
	{
		int min_index = i;
		for (int j = i; j < length - i; j++)
		{
			if (unsort_list[j] < unsort_list[min_index])
			{
				min_index = j;
			}
		}
		temp = unsort_list[i];
		unsort_list[i] = unsort_list[min_index];
		unsort_list[min_index] = temp;
	}
}

void insert_sort(int* unsort_list)
{
	int temp = 0;
	for (int i = 0; i < length; i++)
	{
		int insert_value_index = i;
		for (int j = i - 1; j >= 0; j--)
		{
			if (unsort_list[insert_value_index] < unsort_list[j])
			{
				temp = unsort_list[insert_value_index];
				unsort_list[insert_value_index] = unsort_list[j];
				unsort_list[j] = temp;
				insert_value_index = j;
			}
		}
	}
}

void counting_sort(int* first)
{
	int storage_array[100];
	for (int i = 0; i < 100; i++)
	{
		storage_array[i] = 0;
	}
	while (*first != '\0')
	{
		if (storage_array[*first] != 0)
		{
			storage_array[*first]++;
		}
		else
		{
			storage_array[*first] = 1;
		}
		first++;
	}
	int ouput_array[length];
	int* reload_point = ouput_array;
	for (int i = 0; i < 100; i++)
	{
		if (storage_array[i])
		{
			for (int j = 0; j < storage_array[i]; j++)
			{
				*reload_point = i;
				reload_point++;
			}
		}
	}
	/*reload_point = ouput_array;
	for (int i = 0; i < length; i++)
	{
		printf("%d ", *reload_point);
		reload_point++;
	}*/
	
}


void bucket_sort(int* unsort_list)
{
	struct Bucket* Bucket_Sort_Array[10] = {NULL};
	for (int i = 0; i < length; i++)
	{
		int put_index = *unsort_list / 10;
		struct Bucket* new_node = (struct Bucket*)malloc(sizeof(struct Bucket));
		new_node->value = *unsort_list;
		new_node->next = NULL;
		if (Bucket_Sort_Array[put_index])  //插入排序
		{
			struct Bucket* first = Bucket_Sort_Array[put_index];
			struct Bucket* first_prev = Bucket_Sort_Array[put_index];
			if (new_node->value < first->value)
			{
				new_node->next = first;
				Bucket_Sort_Array[put_index] = new_node;
			}
			else
			{
				while (first->next && new_node->value > first->value)
				{
					first = first->next;
				}
				if (first->next) //中间case
				{
					while (first_prev->next != first)
					{
						first_prev = first_prev->next;
					}
					first_prev->next = new_node;
					new_node->next = first;
				}
				else //末尾case
				{
					first->next = new_node;
				}
			}
		}
		else
		{
			Bucket_Sort_Array[put_index] = new_node;
		}
		unsort_list++;
	}
	for (int i = 0; i < 10; i++)
	{
		while (Bucket_Sort_Array[i])
		{
			printf("%d ", Bucket_Sort_Array[i]->value);
			Bucket_Sort_Array[i] = Bucket_Sort_Array[i]->next;
		}
	}
}



int main()
{
	int* first = unsort_list;
	//counting_sort(first);
	//insert_sort();
	//print_list(first);
}

