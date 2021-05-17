#include <iostream>
using namespace std;
typedef float Type;

//Sort函数的目的是将集装箱的序号按照重量从小到大排序
void Sort(Type w[],int t[],int n) {
	int temp;
	for(int i=1; i<=n; i++) {
		t[i]=i;   //初始时默认集装箱序号为升序
	}
	for(int i=1; i<=n; i++) {
		for(int j=1; j<=n-1; j++) {
			if(w[j]>w[j+1]) { //如果前者比后者重交换其序号
				temp=t[j];
				t[j]=t[j+1];
				t[j+1]=temp;
			}
		}
	}
}


//c为轮船载重量，n为集装箱数目
//w[]表示集装箱的重量
//x[]表示集装箱是否装入轮船，x[i]=0或1

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
	cout<<"请输入集装箱数目："; 
	cin>>n;
	cout<<"请输入轮船装载重量：";
	cin>>c;
	Type w[n+1];
	cout<<"请输入每个集装箱的重量："; 
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
