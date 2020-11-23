// ConsoleApplication1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include<stdio.h>
#include<stdlib.h>

int unsort_list[100] = { 99,44,38,3,47,15,36,26,27,2,46,4,19,50,48 };
const int length = 15;
const int counting_length = 9;

int SortReady[length];

struct Bucket
{
	int value;
	struct Bucket* next;
};

void print_list(int* first)
{
	int i = 0;
	while (i < length)
	{
		printf("%d ", unsort_list[i]);
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


int* bucket_sort(int* unsort_list)
{
	struct Bucket* Bucket_Sort_Array[10] = { NULL };
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
	int* SortReady_point = SortReady;
	int* SortReady_head = SortReady_point;
	for (int i = 0; i < 10; i++)
	{
		while (Bucket_Sort_Array[i])
		{
			*SortReady_point = Bucket_Sort_Array[i]->value;
			SortReady_point++;
			Bucket_Sort_Array[i] = Bucket_Sort_Array[i]->next;
		}
	}
	return SortReady;
}

int get_max(int* unsort_list, int n)
{
	int max = -666;
	for (int i = 0; i < n; i++)
	{
		if (*unsort_list > max)
		{
			max = *unsort_list;
		}
		unsort_list++;
	}
	return max;
}


void radix_bucket_sort(int* unsort_list, int bit)
{
	struct Bucket* Bucket_Sort_Array[5] = { NULL };  //每个桶范围是2，从0-1,2-3,4-5这样，形成0-9
	for (int i = 0; i < length; i++)
	{
		int put_index = (((*unsort_list / bit) % 10) / 2) % 5;
		struct Bucket* new_node = (struct Bucket*)malloc(sizeof(struct Bucket));
		new_node->value = *unsort_list;
		new_node->next = NULL;
		if (Bucket_Sort_Array[put_index])
		{
			struct Bucket* first = Bucket_Sort_Array[put_index];
			struct Bucket* first_prev = Bucket_Sort_Array[put_index];

			if (new_node->value / bit % 10 < first->value / bit % 10)
			{
				new_node->next = first;
				Bucket_Sort_Array[put_index] = new_node;
			}
			else
			{
				while (new_node->value / bit % 10 >= first->value / bit % 10 && first->next)
				{
					first = first->next;
				}
				if (new_node->value / bit % 10 < first->value / bit % 10)
				{
					while (first_prev->next != first)
					{
						first_prev = first_prev->next;
					}
					if (first_prev->next) //中间case
					{
						first_prev->next = new_node;
						new_node->next = first;
					}
					else  //末尾case
					{
						first->next = new_node;
					}
				}
				else  //末尾case
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
	int* SortReady_point = SortReady;
	for (int i = 0; i < 5; i++)
	{
		while (Bucket_Sort_Array[i])
		{
			*SortReady_point = Bucket_Sort_Array[i]->value;
			SortReady_point++;
			Bucket_Sort_Array[i] = Bucket_Sort_Array[i]->next;
		}
	}
}


void radix_sort(int* unsort_list)  //只例句两位数情况
{
	radix_bucket_sort(unsort_list, 1);
	for (int i = 0; i < length; i++)
	{
		printf("%d ", SortReady[i]);
	}
	printf("\n");
	radix_bucket_sort(SortReady, 10);
	for (int i = 0; i < length; i++)
	{
		printf("%d ", SortReady[i]);
	}
}

void quick_sort(int left, int right)
{
	int pivot, i, j, temp;
	if (left > right)
	{
		return;
	}
	pivot = unsort_list[left];
	i = left;
	j = right;
	while (i < j)
	{
		while (i < j && unsort_list[j] >= pivot)
		{
			j--;
		}
		while (i < j && unsort_list[i] <= pivot)
		{
			i++;
		}
		if (i < j)
		{
			temp = unsort_list[i];
			unsort_list[i] = unsort_list[j];
			unsort_list[j] = temp;
		}
	}
	unsort_list[left] = unsort_list[j];
	unsort_list[j] = pivot;
	for (int k = 0; k < 15; k++)
	{
		printf("%d ", unsort_list[k]);
	}
	printf("\n");
	quick_sort(left, j - 1);
	quick_sort(j + 1, right);
}

int quick_select(int left,int right,int index)
{
	int pivot, i, j, temp;
	pivot = unsort_list[left];
	i = left;
	j = right;
	while (i < j)
	{
		while (i < j && unsort_list[j] >= pivot)
		{
			j--;
		}
		while (i < j && unsort_list[i] <= pivot)
		{
			i++;
		}
		if (i < j)
		{
			temp = unsort_list[i];
			unsort_list[i] = unsort_list[j];
			unsort_list[j] = temp;
		}
	}
	unsort_list[left] = unsort_list[j];
	unsort_list[j] = pivot;
	if (j == index)
	{
		printf("arr[%d] is %d\n", index,unsort_list[index]);
		return unsort_list[index];
	}
	else if (index < j)
	{
		quick_select(left, j - 1, index);
	}
	else
	{
		quick_select(j + 1, right, index);
	}
}


int main()
{
	quick_select(0,14,14);
	//radix_sort(unsort_list);
	//bucket_sort(first);
	//insert_sort();
	//print_list(first);
}

