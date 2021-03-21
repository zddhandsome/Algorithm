#include <stdio.h>
#include <stdlib.h>
#define VertexMax 20 //��󶥵���Ϊ20
#define MaxInt 32767 //��ʾ�����������ʾ �� 

typedef char VertexType; //ÿ��������������Ϊ�ַ��� 

typedef struct
{
	VertexType Vertex[VertexMax];//��Ŷ���Ԫ�ص�һά���� 
	int AdjMatrix[VertexMax][VertexMax];//�ڽӾ����ά���� 
	int vexnum,arcnum;//ͼ�Ķ������ͱ���  
}MGraph;

int LocateVex(MGraph *G,VertexType v)//����Ԫ��v��һά���� Vertex[] �е��±꣬�������±� 
{
	int i;
	
	for(i=0;i<G->vexnum;i++)
	{
		if(v==G->Vertex[i])
		{
			return i; 
		} 
	 } 
	 
	 printf("No Such Vertex!\n");
	 return -1;
}

void CreateDN(MGraph *G) 
{
	int i,j;
	//1.���붥�����ͱ��� 
	printf("���붥������ͱ�����\n");
	printf("������ n="); 
	scanf("%d",&G->vexnum);
	printf("��  �� e="); 
	scanf("%d",&G->arcnum);

	//2.���붥��Ԫ�� 
	printf("���붥��Ԫ��(����ո����)��");
	scanf("%s",G->Vertex);
	printf("\n");
	//3.�����ʼ��
	for(i=0;i<G->vexnum;i++) 
	 for(j=0;j<G->vexnum;j++)
	    {
	    	G->AdjMatrix[i][j]=MaxInt;
		}
	
	 //4.�����ڽӾ���
	 int n,m;
	 VertexType v1,v2;
	 int w;//v1->v2��Ȩֵ 
	 
	 printf("����·����·�����ȣ�\n");
	 for(i=0;i<G->arcnum;i++)
	 {
	 	printf("�����%d��·����Ϣ��",i+1);
	 	scanf(" %c%c,%d",&v1,&v2,&w);
	 	n=LocateVex(G,v1); //��ȡv1����Ӧ����Vertex�����е����� 
	 	m=LocateVex(G,v2); //��ȡv2����Ӧ����Vertex�����е�����
	 	
	 	if(n==-1||m==-1)
		 {
		 	printf("NO This Vertex!\n");
		 	return;
		  } 
	
	   G->AdjMatrix[n][m]=w;
	 }
}

void print(MGraph G)
{
	int i,j;
	printf("\n-----------------------------------------------");
	printf("\n �ڽӾ���\n\n"); 
		
		printf("\t ");
		for(i=0;i<G.vexnum;i++)
		printf("\t%c",G.Vertex[i]);
		printf("\n");
		 
		for(i=0;i<G.vexnum;i++)
	   {
	   	  printf("\t%c",G.Vertex[i]);
	   	  
		  for(j=0;j<G.vexnum;j++)
	    {
	    	
	    	if(G.AdjMatrix[i][j]==MaxInt)
	 	    printf("\t��");
	 	    else printf("\t%d",G.AdjMatrix[i][j]);
	    }
	      printf("\n");
	   }
	 
}

void displayPath(int dist[],int path[],MGraph *G,VertexType start)
{
	int i,k,j=0;
	int temp[VertexMax];//��ʱ���� 
	VertexType target;//Ŀ��ص� 
	int loc=0; 
	
	for(i=0;i<VertexMax;i++)
	temp[i]=-1;
	
	printf("\n-----------------------------------------------\n");
	printf("���չʾ��\n");
	printf("\n\n");
	//��ӡdist���� 
	printf("\tdist[i]:\n\t");
	for(i=0;i<G->vexnum;i++)
	printf("\t%d",i);
	printf("\n\t"); 
	  for(i=0;i<G->vexnum;i++)
    {
    	printf("\t%d",dist[i]);
	}
	printf("\n");
	
	printf("\n\n");
	//��ӡpath���� 
	printf("\n\tpath[i]:\n\t");
	for(i=0;i<G->vexnum;i++)
	printf("\t%d",i);
	printf("\n\t"); 
	for(i=0;i<G->vexnum;i++)
    {
    	printf("\t%d",path[i]);
	}
     
    printf("\n\n"); 
	 //���·�� 
	 printf("���·��:\n\n"); 
	for(i=0;i<G->vexnum;i++)
	{
		loc=i;
		j=0;
		while(loc!=-1)
    	{
    		temp[j]=loc;
    		loc=path[loc];
    		j++;
		}
		
		if(j-1==0&&G->Vertex[temp[j-1]]==start)
			{
				printf("\t");
				printf("%c->%c:%cΪ��ʼ��!",start,G->Vertex[i],G->Vertex[temp[j-1]]);
			}
			else if(j-1==0&&G->Vertex[temp[j-1]]!=start)
			{
				printf("\t");
				printf("%c->%c:%c���ɴ�%c",start,G->Vertex[i],start,G->Vertex[temp[j-1]]);
			}
			else
			{
				printf("\t");
				printf("%c->%c:",start,G->Vertex[i]);
				for(j=j-1;j>=0;j--)
				{
					printf("%c ",G->Vertex[temp[j]]);
				}
				printf("(��·������:%d)",dist[i]);
			}
	    for(k=0;k<20;k++)
	    temp[k]=-1;
	 
	 printf("\n\n"); 

	}
}

int FindMinDist(int dist[],int s[],int vexnum) 
{
	int i;
	int loc;
	int min=MaxInt+1;
	for(i=0;i<vexnum;i++)
	{
		if(s[i]==0)//ֻ��s[i]=0�Ķ�����в��� 
		{
			if(dist[i]<min)
			{
				min=dist[i];
				loc=i;
			}
		}
	}
	return loc;//����dist����СԪ�ص��±� 
}

void ShortestPath_Dijkstra(MGraph *G,VertexType start)
{
	int i,j,num;
	int loc;
	int min;
	int dist[VertexMax];//���·���������� 
	int path[VertexMax];//���·������ 
	int s[VertexMax];//������S��1����ö����Ѵ������ڼ���S��0����ö���δ���������ڼ���S�����ڼ���V-S�� 
	
	//1.��ʼ��dist��path���� 
	loc=LocateVex(G,start);//��ȡԴ����±�λ�� 
	for(i=0;i<G->vexnum;i++)
	{
		dist[i]=G->AdjMatrix[loc][i];
		
		if(dist[i]!=MaxInt)
		{
			path[i]=loc;
		}
		else
		{
			path[i]=-1;
		}	  
	} 
    
    //2.��ʼ��S���飨s���飺������S��1�����Ԫ�����ڼ���S(�Ѵ���Ķ���)��0��Ԫ�ز����ڼ���S(δ����Ķ���)�� 
    for(i=0;i<G->vexnum;i++)
	{
		s[i]=0;
	} 
	s[loc]=1;//������ʼ��(Դ��)�Դ������ 
	num=1;
	
	//3.
	while(num<G->vexnum)
	{
		min=FindMinDist(dist,s,G->vexnum);//��dist�����в������Ӧs[i]=0����δ�������СֵԪ�� 
		s[min]=1;//���ҵ�����̱�����Ӧ�ĵĶ�����뼯��S
		
		for(i=0;i<G->vexnum;i++)//�����µĶ���󣬸���dist��path���� 
		{
			if((s[i]==0)&&(dist[i]>dist[min]+G->AdjMatrix[min][i]))//
			{
				dist[i]=dist[min]+G->AdjMatrix[min][i];
				path[i]=min;//min->i
			}
		}
	    num++;	
	} 
    displayPath(dist,path,G,start);//չʾdist���顢path���鼰���·�� 
    
} 

int main() 
{
	MGraph G;
	VertexType start;
	
	CreateDN(&G);
	print(G); 
	
	printf("������ʼ�㣺"); 
	scanf(" %c",&start);
	printf("\n");
	ShortestPath_Dijkstra(&G,start);
	
	 
	return 0;
}

