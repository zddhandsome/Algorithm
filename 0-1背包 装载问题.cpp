#include <iostream>
using namespace std;
typedef float Type;

//Sort������Ŀ���ǽ���װ�����Ű���������С��������
void Sort(Type w[],int t[],int n) {
	int temp;
	for(int i=1; i<=n; i++) {
		t[i]=i;   //��ʼʱĬ�ϼ�װ�����Ϊ����
	}
	for(int i=1; i<=n; i++) {
		for(int j=1; j<=n-1; j++) {
			if(w[j]>w[j+1]) { //���ǰ�߱Ⱥ����ؽ��������
				temp=t[j];
				t[j]=t[j+1];
				t[j+1]=temp;
			}
		}
	}
}


//cΪ�ִ���������nΪ��װ����Ŀ
//w[]��ʾ��װ�������
//x[]��ʾ��װ���Ƿ�װ���ִ���x[i]=0��1

void Loading(int x[],Type w[],Type c,int n){
	int *t=new int [n+1];
	Sort(w,t,n);
	for(int i=1;i<=n;i++){
		x[i]=0;
	}
	for(int i=1;i<=n&&w[t[i]]<=c;i++){
		x[t[i]]=1;
		c=c-w[t[i]];
	}
} 

int main(){
	int n;
	Type c;
	cout<<"�����뼯װ����Ŀ��"; 
	cin>>n;
	cout<<"�������ִ�װ��������";
	cin>>c;
	Type w[n+1];
	cout<<"������ÿ����װ���������"; 
	for(int i=1;i<=n;i++){
		cin>>w[i];
	}
	int x[n+1];
	Loading(x,w,c,n);
	for(int i=1;i<=n;i++){
		cout<<x[i]<<" ";
	}
	return 0;
}
