#include<stdio.h>
#include<math.h>
#include<graphics.h>
#include <stdlib.h>
#define MAX 100
#define INPUT "points.inp"
#define INPUT1 "points1.inp"

void readfile();
void readfile1();
void intoado(struct mt[MAX], int size);
void arrow(int x);
void deleted_arrow(int x);
void push_for_insert(int vitri);
void confirm(int x);
void swap(int a,int b);

struct toado{
	int x;
	int y;
	int value;
};

struct toado td[MAX];
int npoints;
FILE* fp;
char buffer[10];
int flag;
void swap(int a,int b)
{
	int tam=td[a].value;
	td[a].value=td[b].value;
	td[b].value=tam;
}
void readfile(){
	fp=fopen(INPUT,"r");
	if(fp==NULL){
		printf("File not found");
		return;
	}
	fscanf(fp,"%d",&npoints);
	printf("So luong cac diem: %d",npoints);
	for(int i=0; i<npoints; i++){
		fscanf(fp,"%d %d %d",&td[i].x, &td[i].y,&td[i].value);
	}
	fclose(fp);
}
void readfile1(){
	fp=fopen(INPUT1,"r");
	if(fp==NULL){
		printf("File not found");
		return;
	}
	fscanf(fp,"%d",&npoints);
	printf("So luong cac diem: %d",npoints);
	for(int i=0; i<npoints; i++){
		fscanf(fp,"%d %d %d",&td[i].x, &td[i].y,&td[i].value);
	}
	fclose(fp);
}
void intoado(struct toado mt[MAX], int size){
	printf("\ntoa do cac dinh: \n");
	for(int i=0; i<size; i++){
		printf("%d  %d %d\n",mt[i].x, mt[i].y, mt[i].value);
	}
}

void init(){
	for(int i=0; i<npoints; i++){
		
	}
}

void vediem(struct toado diem){
	setcolor(WHITE);
	//setlinestyle(int linestyle, unsigned upattern, int thickness);
	setlinestyle(0,1,2);
	//setfillstyle(int pattern, int color)
	//setfillstyle(1,14);
	circle(diem.x, diem.y, 20);
	//floodfill(int x, int y, int border_color)
	//floodfill(mt[i].x, mt[i].y,WHITE);
	//settextstyle(int font , int direction , int charsize);
	settextstyle(1,0,3);
	outtextxy(diem.x-9, diem.y-14,itoa(diem.value, buffer, 10));
}

void veds(struct toado mt[MAX], int size){
	for(int i=0; i<size; i++){
		vediem(mt[i]);
		delay(200);
	}
}

void pointcolor(struct toado diem)
{
	switch(flag)
	{
		case 0: {	setcolor(WHITE); break;	}
		case 1: {	setcolor(RED); break;	}
		case 2: {	setcolor(GREEN); break;	}
		case 3: {	setcolor(BLACK); break;	}
		case 4: {	setcolor(YELLOW); break;	}
	}
	circle(diem.x, diem.y, 20);
	settextstyle(1,0,3);
	outtextxy(diem.x-9, diem.y-14,itoa(diem.value, buffer, 10));
}
void sign(int vitri)
{
	while(td[vitri].y<250)
	{
		//xoa gia tri o diem hien tai
		flag=3; // setcolor black
		pointcolor(td[vitri]);
		++td[vitri].y;//dich chuyen xuong duoi 1 diem pixel
		//in ra lai diem sau khi dich chuyen
		flag=0;
		pointcolor(td[vitri]);
		delay(15);
	}
}
void resign_for_select(int a,int b)
{
	if(a!=b)
		while(td[a].y>200)
		{
			//xoa gia tri o diem hien tai
			flag=3; // setcolor black
			pointcolor(td[a]);
			pointcolor(td[b]);
			--td[a].y;
			--td[b].y;//dich chuyen xuong duoi 1 diem pixel
			//in ra lai diem sau khi dich chuyen
			flag=0;
			pointcolor(td[a]);
			pointcolor(td[b]);
			delay(15);
		}
	else
		while(td[a].y>200)
		{
			//xoa gia tri o diem hien tai
			flag=3; // setcolor black
			pointcolor(td[a]);
			--td[a].y;//dich chuyen xuong duoi 1 diem pixel
			//in ra lai diem sau khi dich chuyen
			flag=0;
			pointcolor(td[a]);
			delay(15);
		}
}
void push_for_select(int a,int b)
{
	int n=td[b].x-td[a].x;
	for(int i=0;i<n;i++)
	{
		flag=3; // setcolor black
		pointcolor(td[a]);
		pointcolor(td[b]);
		++td[a].x;
		--td[b].x;//dich chuyen sang phai 1 diem pixel
		//in ra lai diem sau khi dich chuyen
		
		flag=0;
		pointcolor(td[a]);
		pointcolor(td[b]);
		delay(15);
	}
	struct toado tam=td[b];
	td[b]=td[a];
	td[a]=tam;
}
void selection_sort()
{
	for(int i=0; i<npoints-1; i++)
	{
		arrow(td[i].x);
		delay(500);
		sign(i);//danh dau vi tri can hoan doi
		delay(1500);
		struct toado tam=td[i];
		int vitri = i;
		for(int j=i+1; j<npoints; j++)
		{
			if(tam.value>td[j].value)
			{
				tam = td[j];
				vitri = j;
			}
		}
		
		//danh dau vi tri duoc chon
		sign(vitri);
		//swap 2 gia tri nay lai
		if(i!=vitri)
		{
			push_for_select(i,vitri);
		}
		//in ra lai 2 gia tri sau khi swap la mau xanh
		flag=0;
		pointcolor(td[vitri]);
		pointcolor(td[i]);
		delay(1000);//delay de xem sau khi swap
		//chuyen 2 gia tri sau swap thanh mau trang
		resign_for_select(i,vitri);
		deleted_arrow(td[i].x);
		confirm(td[i].x);
		//sau khi ve dong 1 lan cho 10 diem thi ve lan 2
		delay(1000);
	}
	delay(5000);//tam dung de xem xet day so
}
void arrow(int x)
{
	//x la 150
	setcolor(WHITE);
	line(x,150,x-20,130);
	line(x,150,x+20,130);
	line(x,150,x,100);
}
void deleted_arrow(int x)
{
	setcolor(BLACK);
	line(x,150,x-20,130);
	line(x,150,x+20,130);
	line(x,150,x,100);
	flag=0;
}
void confirm(int x)
{
	setcolor(GREEN);
	line(x,150,x-20,130);
	line(x,150,x+30,115);
	delay(500);
	setcolor(BLACK);
	line(x,150,x-20,130);
	line(x,150,x+30,115);
}
void push_for_insert(int vitri)
{
	for(int i=0;i<50;i++)
	{
		flag=3; // setcolor black
		
		pointcolor(td[vitri]);
		pointcolor(td[vitri+1]);
		deleted_arrow(td[vitri+1].x);
		++td[vitri].x;
		--td[vitri+1].x;//dich chuyen sang phai 1 diem pixel
		//in ra lai diem sau khi dich chuyen
		
		flag=0;
		pointcolor(td[vitri]);
		pointcolor(td[vitri+1]);
		arrow(td[vitri+1].x);
		delay(15);
	}
	deleted_arrow(td[vitri+1].x);
	struct toado tam=td[vitri+1];
	td[vitri+1]=td[vitri];
	td[vitri]=tam;
}

void insertion_sort()
{
	for (int i = 1; i < npoints; i++)
	{
		sign(i);
		int j=i-1;int check=0;
		arrow(td[j+1].x);
		delay(3000);
		int tam=td[i].value;
		while(j>0)
		{
			if(tam>td[j].value) break;
			deleted_arrow(td[j+1].x);
			push_for_insert(j);
			j--;
			delay(750);
			check=1;
		}
		if(check==0)
		{
			deleted_arrow(td[j+1].x);
			confirm(td[j+1].x);
			resign_for_select(j+1,j+1);
		 } 
		else
		{
			deleted_arrow(td[j].x);
			confirm(td[j+1].x);
			resign_for_select(j+1,j+1);
		}
		delay(1500);
	}
	delay(5000);//tam dung de xem xet day so
}
void push_for_bubble(int a,int b)
{
	while(td[a].y>150 && td[b].y<250)
	{
		//xoa gia tri o diem hien tai
		flag=3; // setcolor black
		pointcolor(td[a]);
		pointcolor(td[b]);
		--td[a].y;++td[b].y;//dich chuyen xuong duoi 1 diem pixel
		//in ra lai diem sau khi dich chuyen
		flag=0;
		pointcolor(td[a]);
		pointcolor(td[b]);
		delay(15);
	}
	for(int i=0;i<50;i++)
	{
		flag=3; // setcolor black
		pointcolor(td[a]);
		pointcolor(td[b]);
		++td[a].x;
		--td[b].x;//dich chuyen sang phai 1 diem pixel
		//in ra lai diem sau khi dich chuyen
		flag=0;
		pointcolor(td[a]);
		pointcolor(td[b]);
		delay(15);
	}
	while(td[a].y<200 && td[b].y>200)
	{
		//xoa gia tri o diem hien tai
		flag=3; // setcolor black
		pointcolor(td[a]);
		pointcolor(td[b]);
		++td[a].y;--td[b].y;//dich chuyen xuong duoi 1 diem pixel
		//in ra lai diem sau khi dich chuyen
		flag=0;
		pointcolor(td[a]);
		pointcolor(td[b]);
		delay(15);
	}
	struct toado tam=td[b];
	td[b]=td[a];
	td[a]=tam;
}
void bubble_sort()
{
	int i, j, temp, no_exchange;
	i = 1;
	do
	{
		no_exchange = 0;
		for (j=npoints-1; j >= i; j--)
		{
			flag=2;
			pointcolor(td[j]);
			pointcolor(td[j-1]);
			delay(750);
			if (td[j-1].value > td[j].value)
			{
				flag=1;
				pointcolor(td[j]);
				pointcolor(td[j-1]);
				delay(1000);
				push_for_bubble(j-1,j);
				delay(1000);
				no_exchange = 1;
			}
			flag=0;
			pointcolor(td[j]);
			pointcolor(td[j-1]);
			confirm(td[j-1].x+25);
		}
		i++;
		delay(500);
	}
	while (no_exchange || (i == npoints-1));
}

void ve_heap(int a,int b)
{
	float dx = td[b].x - td[a].x;
	float dy = td[b].y - td[a].y;
	float length = sqrt(dx * dx + dy * dy);
	
	float unit_dx = dx / length;
	float unit_dy = dy / length;
	
	int offset_x = unit_dx * 25;
	int offset_y = unit_dy * 25;
	
	int point1_x = td[a].x + offset_x;
	int point1_y = td[a].y + offset_y;
	
	int point2_x = td[b].x - offset_x;
	int point2_y = td[b].y - offset_y;
	
	line(point1_x, point1_y, point2_x, point2_y);
}
void heap_sort()
{
	for(int i=0;i<npoints;i++)
	{
		if((2*i+1)<npoints)
		{
			ve_heap(i,2*i+1);
		}
		if((2*i+2)<npoints)
		{
			ve_heap(i,2*i+2);
		}
	}
	int n=npoints;
	while(n>1)
	{
		int i=(n-2)/2;
		for(;i>=0;i--)
		{
			flag=2;
			pointcolor(td[i]);
			flag=1;
			pointcolor(td[2*i+1]);
			if(2*i+2<n)	pointcolor(td[2*i+2]);
			delay(1500);
			if(2*i+1<n&&2*i+2<n)
			{
				if(td[2*i+1].value>td[i].value&&td[2*i+1].value>td[2*i+2].value)
				{
					flag=0;
					pointcolor(td[2*i+2]);
					flag=1;
					pointcolor(td[2*i+1]);
					pointcolor(td[i]);
					delay(750);
					//hoan doi 2 gia tri
					swap(i,2*i+1);
					flag=2;
					pointcolor(td[2*i+1]);
					pointcolor(td[i]);
					delay(500);
					flag=0;
					pointcolor(td[2*i+1]);
					pointcolor(td[i]);
				}
				if(td[2*i+2].value>td[i].value&&td[2*i+2].value>td[2*i+1].value)
				{
					flag=0;
					pointcolor(td[2*i+1]);
					flag=1;
					pointcolor(td[2*i+2]);
					pointcolor(td[i]);
					delay(750);
					//hoan doi 2 gia tri
					swap(i,2*i+2);
					flag=2;
					pointcolor(td[2*i+2]);
					pointcolor(td[i]);
					delay(500);
					flag=0;
					pointcolor(td[2*i+2]);
					pointcolor(td[i]);
				}
				flag=0;
				pointcolor(td[2*i+1]);
				pointcolor(td[2*i+2]);
			}
			else
				if(2*i+1<n)
				{
					if(td[2*i+1].value>td[i].value)
					{
						flag=1;
						pointcolor(td[2*i+1]);
						pointcolor(td[i]);
						delay(1000);
						//hoan doi 2 gia tri
						swap(i,2*i+1);
						flag=2;
						pointcolor(td[2*i+1]);
						pointcolor(td[i]);
						delay(1000);
						flag=0;
						pointcolor(td[2*i+1]);
						pointcolor(td[i]);
					}
				}
			flag=0;
			pointcolor(td[i]);
			pointcolor(td[2*i+1]);
			if(2*i+2<n)	pointcolor(td[2*i+2]);
			delay(1000);
		}
		flag=1;
		pointcolor(td[0]);
		pointcolor(td[n-1]);
		swap(0,n-1);
		delay(1000);
		pointcolor(td[0]);
		pointcolor(td[n-1]);
		delay(1000);
		flag=0;
		pointcolor(td[0]);
		pointcolor(td[n-1]);
		delay(1000);
		flag=4;
		pointcolor(td[n-1]);
		delay(1000);
		--n;
	}
}
void wall(int left,int right)
{
	setcolor(WHITE);
	line(td[left].x-25,td[left].y,td[left].x-25,td[left].y-100);
	line(td[right].x+25,td[right].y,td[right].x+25,td[right].y-100);
}
void re_wall(int left,int right)
{
	setcolor(BLACK);
	line(td[left].x-25,td[left].y,td[left].x-25,td[left].y-100);
	line(td[right].x+25,td[right].y,td[right].x+25,td[right].y-100);
}
void push_for_quick(int a,int b)
{
	int des=td[b].x-td[a].x;
	while(td[a].y>150 && td[b].y<250)
	{
		//xoa gia tri o diem hien tai
		flag=3; // setcolor black
		pointcolor(td[a]);
		pointcolor(td[b]);
		--td[a].y;++td[b].y;//dich chuyen xuong duoi 1 diem pixel
		//in ra lai diem sau khi dich chuyen
		flag=0;
		pointcolor(td[a]);
		pointcolor(td[b]);
		delay(15);
	}
	for(int i=0;i<des;i++)
	{
		flag=3; // setcolor black
		pointcolor(td[a]);
		pointcolor(td[b]);
		++td[a].x;
		--td[b].x;//dich chuyen sang phai 1 diem pixel
		//in ra lai diem sau khi dich chuyen
		flag=0;
		pointcolor(td[a]);
		pointcolor(td[b]);
		delay(15);
	}
	while(td[a].y<200 && td[b].y>200)
	{
		//xoa gia tri o diem hien tai
		flag=3; // setcolor black
		pointcolor(td[a]);
		pointcolor(td[b]);
		++td[a].y;--td[b].y;//dich chuyen xuong duoi 1 diem pixel
		//in ra lai diem sau khi dich chuyen
		flag=0;
		pointcolor(td[a]);
		pointcolor(td[b]);
		delay(15);
	}
	struct toado tam=td[b];
	td[b]=td[a];
	td[a]=tam;
}
void quick(int left,int right)
{
	wall(left,right);
	int i=left+1,j=right;
	int x=td[left].value,y;
	sign(left);
	do
	{
		while(td[i].value<=x && i<right)
		{
			i++;
		}
		flag=1;
		pointcolor(td[i]);
		arrow(td[i].x);
		delay(1000);
		while(td[j].value>x && j>left)
		{
			j--;
		}
		flag=1;
		pointcolor(td[j]);
		arrow(td[j].x);
		delay(1000);
		deleted_arrow(td[j].x);
		deleted_arrow(td[i].x);
		if(i<j)
		{
			push_for_quick(i,j);
			delay(1500);
			flag=2;
			pointcolor(td[j]);
			pointcolor(td[i]);
			delay(1000);
			flag=0;
			pointcolor(td[j]);
			pointcolor(td[i]);
			delay(1000);
			i++;j--;
		}
		else	
		{
			delay(1000);
			flag=0;
			pointcolor(td[j]);
			pointcolor(td[i]);
			delay(1000);
		}
	}while (i<j);
	sign(j);
	push_for_select(left,j);
	resign_for_select(left,j);
	delay(1000);
	re_wall(left,right);
	delay(1000);
	if (left<j) quick(left,j);
	if (i<right) quick(i,right);
}
void quick_sort()
{
	quick(0,npoints-1);
}
void sign_for_merge(int l,int r)
{
	if(l!=r)
		for(int i=0;i<50;i++)
		{
			for(int j=l;j<=r;j++)
			{
				flag=3; // setcolor black
				pointcolor(td[j]);
				++td[j].y;//dich chuyen xuong duoi 1 diem pixel
				//in ra lai diem sau khi dich chuyen
				flag=0;
				pointcolor(td[j]);
				delay(15);
			}
		}
	else
	{
		for(int i=0;i<50;i++)
		{
			//xoa gia tri o diem hien tai
			flag=3; // setcolor black
			pointcolor(td[l]);
			++td[l].y;//dich chuyen xuong duoi 1 diem pixel
			//in ra lai diem sau khi dich chuyen
			flag=0;
			pointcolor(td[l]);
			delay(15);
		}
	}
}
void resign_for_merge(int l,int r)
{
	if(l!=r)
		for(int i=0;i<=50;i++)
		{
			for(int j=l;j<=r;j++)
			{
				flag=3; // setcolor black
				pointcolor(td[j]);
				--td[j].y;//dich chuyen xuong duoi 1 diem pixel
				//in ra lai diem sau khi dich chuyen
				flag=0;
				pointcolor(td[j]);
				delay(15);
			}
			
		}
	else
		for(int i=0;i<50;i++)
		{
			//xoa gia tri o diem hien tai
			flag=3; // setcolor black
			pointcolor(td[l]);
			--td[l].y;//dich chuyen xuong duoi 1 diem pixel
			//in ra lai diem sau khi dich chuyen
			flag=0;
			pointcolor(td[l]);
			delay(15);
		}
}
void merge(int al, int am, int ar)
{
	flag=1;
	for(int i=al;i<=ar;i++)
	{
		pointcolor(td[i]);
	}
	
	for(int i=0;i<10;i++)
	{
		for(int j=al;j<=ar;j++)
		{
			flag=2;
			pointcolor(td[j]);
			delay(50);
			flag=1;
			pointcolor(td[j]);
			delay(50);
		}
		
	}
    int i, j, k;
    int n1 = am - al + 1;
    int n2 = ar - am;
    
    //tao mang tam thoi luu tru cac phan tu
    int L[n1], R[n2];
    
    //sao chep du lieu vao cac mang tam thoi
    for (i = 0; i < n1; i++)
    {
        L[i] = td[al + i].value;
    }
    for (j = 0; j < n2; j++)
    {
        R[j] = td[am + 1 + j].value;
    }
    //tron cac mang tam thoi vao mang goc td[]
    i = 0;
    j = 0;
    k = al;
    
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            td[k].value = L[i];
            i++;
        }
        else
        {
            td[k].value = R[j];
            j++;
        }
        k++;
    }
    
    //sao chep cac phan tu con lai cua mang L[] vao mang goc td[]
    while (i < n1)
    {
        td[k].value = L[i];
        i++;
        k++;
    }
    
    //sao chep cac phan tu con lai cua mang R[] vao mang td[]
    while (j < n2)
    {
        td[k].value = R[j];
        j++;
        k++;
    }
    flag=2;
	for(int i=al;i<=ar;i++)
	{
		pointcolor(td[i]);
	}
	delay(500);
	flag=0;
	for(int i=al;i<=ar;i++)
	{
		pointcolor(td[i]);
	}
	delay(1000);
	
}

void merge_sort(int left, int right)
{
    if (left < right)
    {
        int middle = left + (right - left) / 2;
        
        //goi de quy de sap xep nua dau va nua sau
        sign_for_merge(left,middle);
        merge_sort(left, middle);
        resign_for_merge(left,middle);
        
        sign_for_merge(middle+1,right);
        merge_sort(middle + 1, right);
        resign_for_merge(middle+1,right);
        
        //hop nhat 2 mang da sap xep
        
        merge(left, middle, right);
    }
}
int main(){
	//Doc noi dung file
	int kind;
	int condition=0;
	initwindow(600,600);
	do
	{
		readfile();
		//in ra toa do cac diem
		//ve cac diem ra man hinh
		veds(td,npoints);
		printf("\n1:Selection sort\n2:Insertion_sort\n3:Bubble_sort\n4:Quick_sort\n5:Heap_sort\n6:Merge_sort\n7:Exit");
		printf("\nChon loai sap xep : ");scanf("%d",&kind);
		switch(kind)
		{
			case 1:
				{
					selection_sort();
					break;
				}
			case 2:
				{
					insertion_sort();
					break;
				}
			case 3:
				{
					bubble_sort();
					break;
				}
			case 4:
				{
					quick_sort();
					break;
				}
			case 5:
				{
					cleardevice();
					readfile1();
					veds(td,npoints);
					heap_sort();
					break;
				}
			case 6:
				{
					merge_sort(0,npoints-1);
					break;
				}
			case 7:
				{
					condition=1;
					break;
				}
		}
		cleardevice();
		system("cls");
	}while(!condition);
//	initwindow(600,600);
//	readfile();
//	veds(td,npoints);
//	merge_sort(0,npoints-1);
	getch();
}

