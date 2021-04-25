#include<stdio.h>
#define ARRAY_SIZE 1010

void insertsort(int a[],int low,int high) {
	int i,j,key;
	for(i=low+1; i<=high; i++) {
		key=a[i];
		for(j=i-1; j>=low&&key<a[j]; j--) {
			a[j+1]=a[j];
		}
		a[j+1]=key;
	}
}

void swap(int a[],int i,int j) {
	int tmp=a[i];
	a[i]=a[j];
	a[j]=tmp;
}

int partition(int a[],int p,int r,int pivot) {
	int x,i=p-1,j,tmp;
	for(j=p; j<r; j++) {
		if(a[j]==pivot) {
			swap(a,j,r);
		}
	}
	x=a[r];

	for(j=p; j<r; j++) {
		if(a[j]<=x) {
			i++;
			swap(a,i,j);
		}
	}
	swap(a,r,i+1);
	return i+1;
}

int select(int a[],int l,int r,int k) {
	int group,i,left,right,mid,pivot,p,left_num;
	if(r-l+1<=5) {
		insertsort(a,l,r);
		return a[l+k-1];
	}

	group=(r-l+1+5)/5;
	for(i=0; i<group; i++) {
		left=l+5*i;
		right = (l+5*i+4)>r?r:l+5*i+4;
		mid=(left+right)/2;
		insertsort(a,left,right);
		swap(a,l+i,mid);
	}
	pivot=select(a,l,l+group-1,(group+1)/2);
	p = partition(a,l,r,pivot);
	left_num = p-1;
	if(k==left_num+1)
		return a[p];
	else if(k<=left_num)
		return select(a,l,p-1,k);
	else
		return select(a,p+1,r,k-left_num-1);
}
int a[ARRAY_SIZE];
int n,k;
int main() {
	printf("请输入元素总数和寻找第k小的数：");
	scanf("%d %d",&n,&k);
	printf("请输入这些元素:") ;
	for(int i=0; i<n;i++)
		scanf("%d",&a[i]);
	printf("%d\n",select(a,0,n-1,k));
	return 0;
}
