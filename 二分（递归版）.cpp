#include<iostream>
using namespace std;

int Binarysearch(int a[],int b,int low,int high){
	int mid=(high+low)/2;
	if(a[mid]==b){
		return mid;
	}
	if(a[mid]<b){
		return Binarysearch(a,b,mid+1,high);
	}
	if(a[mid]>b) {
		return Binarysearch(a,b,low,mid-1);
	}
}
int main(){
	int a[1000];
	int n,b; 
	int low,high;
	cin>>n;
	cin>>low>>high;
	for(int i=0;i<n;i++){
		cin>>a[i];
	}
	cin>>b;
	int k=Binarysearch(a,b,low,high);
	cout<<k;
	return 0;
} 

