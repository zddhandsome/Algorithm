#include<iostream>
using namespace std;
 int main(){
 	int a[1000];
 	int b,n;
 	cin>>n;
 	for(int i=0;i<n;i++){
 	cin>>a[i];
	 }
	 cin>>b;
	 for(int i=0;i<=n;i++){
	 	if(b==a[i]){
	 		cout<<i;
	 		break;
		 }
		 if(i==n){
		 	cout<<"0";
		 }
	 }
	 return 0;
 } 
