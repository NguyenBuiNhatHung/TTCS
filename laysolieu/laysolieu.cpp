#include<stdio.h>
#include <stdlib.h>
#define MAX 10000000
#define INPUT "points2.inp"
#define OUTPUT "points2.out"
//
void readfile();
int n,m;
int td[MAX],c[MAX];
FILE* fp;
unsigned long long amount_swap=0;
unsigned long long amount_compare=0;
void readfile()
{
	fp=fopen(INPUT,"r");
	if(fp==NULL)
	{
		printf("File not found");
		return;
	}
	fscanf(fp,"%d",&n);
	for(int i=0; i<n; i++)
	{
		fscanf(fp,"%d",&td[i]);
	}
	fclose(fp);
}

void printfile()
{
	for(int i=0; i<n; i++)
	{
		printf("%d	",td[i]);
	}
}

void selection_sort()
{
	int i, j, k;
	for (i = 0; i< n; i++)
	{
		k = i;
		for (j = i+1; j < n; j++)
		{
			amount_compare++;
			if (td[j] < td[k]) k = j;
		}
		td[i] = td[i] + td[k];
		td[k] = td[i] - td[k];
		td[i] = td[i] - td[k];
		amount_swap++;
	}
}

void insertion_sort()
{
	int i, j, k, temp;
	for (i = 1; i < n; i++)
	{
		temp = td[i];
		j = i - 1;

		while (j >= 0 && td[j] > temp)
		{
			td[j + 1] = td[j];
			j--;
			amount_compare++;
			amount_swap++;
		}

		td[j + 1] = temp;
		amount_compare++;
	}
	
}

void bubble_sort()
{
	fp = fopen(OUTPUT, "w");
	int i, j, temp, no_exchange;
	i = 1;
	do
	{
		no_exchange = 0;
		for (j = n - 1; j >= i; j--)
		{
			if (td[j - 1] > td[j])
			{
				temp = td[j - 1];
				td[j - 1] = td[j];
				td[j] = temp;
				no_exchange = 1;
				amount_compare++;
				amount_swap++;
			}
			amount_compare++;
		}
		i++;
	} while (no_exchange || (i == n - 1));
}

void quick(int left, int right) 
{
	int i, j;
	int x, y;
	i = left; j = right;
	x = td[left];
	do 
	{
		while (td[i] < x && i < right)
		{
			i++;
			amount_compare++;
		}
		while (td[j] > x && j > left)
		{
			j--;
			amount_compare++;
		}
		if (i <= j)
		{
			y = td[i];
			td[i] = td[j];
			td[j] = y;
			i++;
			j--;
			amount_compare++;
			amount_swap++;
		}
	} while (i <= j);
	if (left < j) 
	{
		quick(left, j);
	}
	if (i < right) 
	{
		quick(i, right);
	}
}

void quick_sort()
{
	amount_compare = 0;
	amount_swap = 0;
	quick(0, n - 1);
	fp = fopen(OUTPUT, "w");
}

void upheap(int m)
{
	int x;
	x = td[m];
	while ((td[(m - 1) / 2] <= x) && (m > 0))
	{
		td[m] = td[(m - 1) / 2];
		m = (m - 1) / 2;
		amount_swap++;
		amount_compare++;
	}
	td[m] = x;
}

void insert_heap(int x)
{
	td[m] = x;
	upheap(m);
	m++;
}

void downheap(int k)
{
	int j, x;
	x = td[k];
	while (k <= (m - 2) / 2)
	{
		j = 2 * k + 1;
		if (j < m - 1 && td[j] < td[j + 1]) j++;
		if (x >= td[j]) break;
		td[k] = td[j];
		k = j;
		amount_swap++;
		amount_compare++;
	}
	td[k] = x;
}

int remove_node()
{
	int temp;
	temp = td[0];
	td[0] = td[m];
	m--;
	downheap(0);
	return temp;
}

void heap_sort()
{
	int i;
	m = 0;
	for (i = 0; i <= n - 1; i++)
	{
		insert_heap(td[i]);
		amount_compare++;
		amount_swap++;
	}
	m = n - 1;
	for (i = n - 1; i >= 0; i--)
	{
		td[i] = remove_node();
		amount_compare++;
		amount_swap++;
	}
}
void merge(int al, int am, int ar)
{
    int i, j, k;
    int n1 = am - al + 1;
    int n2 = ar - am;
    
    //tao mang tam thoi luu tru cac phan tu
    int L[n1], R[n2];
    
    //sao chep du lieu vao cac mang tam thoi
    for (i = 0; i < n1; i++)
    {
        L[i] = td[al + i];
    }
    for (j = 0; j < n2; j++)
    {
        R[j] = td[am + 1 + j];
    }
    //tron cac mang tam thoi vao mang goc td[]
    i = 0;
    j = 0;
    k = al;
    
    while (i < n1 && j < n2)
    {
        amount_compare++;
        if (L[i] <= R[j])
        {
            td[k] = L[i];
            i++;
        }
        else
        {
            td[k] = R[j];
            j++;
        }
        k++;
    }
    
    //sao chep cac phan tu con lai cua mang L[] vao mang goc td[]
    while (i < n1)
    {
        td[k] = L[i];
        i++;
        k++;
    }
    
    //sao chep cac phan tu con lai cua mang R[] vao mang td[]
    while (j < n2)
    {
        td[k] = R[j];
        j++;
        k++;
    }
}

void merge_sort(int left, int right)
{
    if (left < right)
    {
        int middle = left + (right - left) / 2;
        
        //goi de quy de sap xep nua dau va nua sau
        merge_sort(left, middle);
        merge_sort(middle + 1, right);
        
        //hop nhat 2 mang da sap xep
        merge(left, middle, right);
    }
   
}
int main()
{
	readfile();
	//selection_sort();
	//insertion_sort();
	//bubble_sort();
	//quick_sort();
	//heap_sort();
	merge_sort(0, n - 1);
	
	//ghi file
	fp = fopen(OUTPUT, "w");
	fprintf(fp, "%llu %llu\n", amount_compare, amount_swap);
	for (int i = 0; i < n; i++)
	{
		fprintf(fp, "%d ", td[i]);
	}
	fclose(fp);
	return 0;
}
