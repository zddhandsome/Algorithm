#include<iostream>
#include<cstdio>
#define MAX_VEX 100
#define INF 65535
using namespace std;
struct Graph{
	char vexs[MAX_VEX];
	int arc[MAX_VEX][MAX_VEX];
	int numvex,numarc; 
}; 
void CreateGraph(Graph &G){
	int vi,vj,w;
	cout<<"please enter the number of vertexes and arc :\n";
	cin>>G.numvex>>G.numarc;
	for(int i=0;i<G.numvex;i++){
		printf("Please enter the NO.%d name of vex:",i+1);
		cin>>G.vexs[i];
	}
	for(int i = 0;i<G.numvex;i++){
		for(int j = 0;j<G.numvex;j++){
			G.arc[i][j] = INF; 
		}
	}
	cout<<endl;
	for(int i = 0;i<G.numarc;i++){
		cout<<"Enter the subscripts and weights from vertex vi to vertex vj:";
	cin>>vi>>vj>>w;
	G.arc[vi][vj]=w;
	G.arc[vj][vi]=w;
	}
}
void Floyd(Graph G){
	int dis[MAX_VEX][MAX_VEX],path[MAX_VEX][MAX_VEX];
	for(int i = 0;i<G.numvex;i++){
		for(int j = 0;j<G.numvex;j++){
			if(i!=j) dis[i][j] = G.arc[i][j];
			else dis[i][j]=0;
			path[i][j]=j;
		}
	}
	for(int k = 0;k<G.numvex;k++){
		for(int i = 0;i<G.numvex;i++){
			for(int j = 0;j<G.numvex;j++){
				if(dis[i][k]+dis[k][j]<dis[i][j]){
					dis[i][j]=dis[i][k]+dis[k][j];
					path[i][j] = path[i][k];
				}
			}
		}
	}
	for(int i=0;i<G.numvex;i++){
		for(int j = 0;j<G.numvex;j++){
			printf("%3d",dis[i][j]);
		}
		cout<<endl;
	} 
}
void DispalyGraph(Graph G){
	for(int i = 0;i<G.numvex;i++){
		printf("%c",G.vexs[i]);
		cout<<endl;
		for(int i = 0;i<G.numvex;i++){
			for(int j = 0;j<G.numvex;j++){
				if(G.arc[i][j]==INF) printf("%6s","¡Þ"); 
				else printf("%6d",G.arc[i][j]);
			}
			cout<<endl;
		}
	}
	
	}
int main(){
		Graph G;
		CreateGraph(G);
		DispalyGraph(G);
		Floyd(G);
		return 0;
	}
