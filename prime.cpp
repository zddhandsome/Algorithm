#include<stdio.h>

#define MAX 10000
#define VUMN 10+1   //���û��idΪ0�ĵ㣬����id�ŷ�Χ��1~10

int edge[VUMN][VUMN]={/*������ڽӾ���*/};
int lowcost[VUMN]={0};   //��¼Vnew��ÿ���㵽V���ڽӵ����̱�
int addvnew[VUMN];         //���ĳ���Ƿ����Vnew
int adjecent[VUMN]={0};     //��¼V����Vnew���ڽ��ĵ�

void prim(int start){
	int sumweight = 0;
	int i,j,k = 0;
	for(i = 1;i<VUMN;i++){            //�����Ǵ�1��ʼ 
		lowcost[i] = edge[start][i];
		addvnew[i] = -1;   //�����е�����Vnew֮�⣬V֮�ڣ�����ֻҪ��Ӧ��Ϊ-1���ͱ�ʾ��Vnew֮��
	}
	
	addvnew[start] = 0;    //����ʼ��start����Vnew 
	adjecent[start] = start;
	
	for(i=1;i<VUMN-1;i++){
		int min = MAX;
		int v = -1;
		for(j=1;j<VUMN;j++){
			if(addvnew[j]!=-1&&lowcost[j]<min)   //��Vnew֮��Ѱ�����·��
			{
			min = lowcost[j];
			v = j; 
		}
	} 
	if(v!=-1){
		printf("%d %d %d\n",adjecent[v],v,lowcost[v]);
		addvnew[v] = 0;    //��V���뵽Vnew��
		
		sumweight+=lowcost[v];        //����·������֮��
		for(j=1;j<VUMN;j++){
			if(addvnew[j]==-1&&edge[v][j]<lowcost[j]){
				lowcost[j]=edge[v][j];      //��ʱV�����Vnew��Ҫ����lowcost
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
