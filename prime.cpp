#include<stdio.h>

#define MAX 10000
#define VUMN 10+1   //这里，没有id为0的点，所以id号范围是1~10

int edge[VUMN][VUMN]={/*输入的邻接矩阵*/};
int lowcost[VUMN]={0};   //记录Vnew中每个点到V中邻接点的最短边
int addvnew[VUMN];         //标记某点是否加入Vnew
int adjecent[VUMN]={0};     //记录V中与Vnew最邻近的点

void prim(int start){
	int sumweight = 0;
	int i,j,k = 0;
	for(i = 1;i<VUMN;i++){            //顶点是从1开始 
		lowcost[i] = edge[start][i];
		addvnew[i] = -1;   //将所有点至于Vnew之外，V之内，这里只要对应的为-1，就表示在Vnew之外
	}
	
	addvnew[start] = 0;    //将起始点start加入Vnew 
	adjecent[start] = start;
	
	for(i=1;i<VUMN-1;i++){
		int min = MAX;
		int v = -1;
		for(j=1;j<VUMN;j++){
			if(addvnew[j]!=-1&&lowcost[j]<min)   //在Vnew之外寻找最短路径
			{
			min = lowcost[j];
			v = j; 
		}
	} 
	if(v!=-1){
		printf("%d %d %d\n",adjecent[v],v,lowcost[v]);
		addvnew[v] = 0;    //将V加入到Vnew中
		
		sumweight+=lowcost[v];        //计算路径长度之和
		for(j=1;j<VUMN;j++){
			if(addvnew[j]==-1&&edge[v][j]<lowcost[j]){
				lowcost[j]=edge[v][j];      //此时V点加入Vnew需要更新lowcost
				adjecent[j] = v; 
			}
		} 
	}
} 
printf("the minmum weight is %d\n",sumweight);
}

//int main(){
//	int i = 0,start = 0;
//	int j = 0;
//	for(i=0;i<VUMN;i++){ 
//	for(j=0;j<VUMN;j++){
//			scanf("%d%d",&edge[i][j]);
//				prim(edge[i][j]);
//	}
//	} 
//	return 0;
//}
