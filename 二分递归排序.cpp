#include<iostream>
using namespace std;
int a[1000],b[1000];

int merge(int a[],int low,int mid,int high){
	int j,k,h;
	j=low;
	h=mid+1;
	k=low;
	while(j<=mid&&h<=high){//���������ݱȽϣ��Ž����������� 
		if(a[j]<a[h]){
			b[k++]=a[j++];
		}
		else {
			b[k++]=a[h++];
		}
	}
	//��ʣ�����ݷ��븨��������
	while(j<=mid){
		b[k++]=a[j++];
	} 
	while(h<=high){
		b[k++]=a[h++];
	}
	for(k=low;k<=high;k++){//�������������ݸ��Ƶ���Ӧԭ����λ���� 
		a[k]=b[k];
	}
}
void mergeSort(int a[],int low,int high){
	if(low<high){
		int mid=(low+high)/2;
		mergeSort(a,low,mid);
		mergeSort(a,mid+1,high);
		merge(a,low,mid,high);
	}
}
int main(){
	int n,low,high;
	cin>>n>>low>>high;
	for(int i=0;i<n;i++){
		cin>>a[i];
	}
	mergeSort(a,low,high);
	for(int i=0;i<n;i++){
		cout<<a[i]<<" ";
	}
	return 0;
}
