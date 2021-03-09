typedef struct          
{        
    char vertex[VertexNum];                                //�����         
    int edges[VertexNum][VertexNum];                       //�ڽӾ���,�ɿ����߱�         
    int n,e;                                               //ͼ�е�ǰ�Ķ������ͱ���         
}MGraph; 
 
typedef struct node  
{  
    int u;                                                 //�ߵ���ʼ����   
    int v;                                                 //�ߵ���ֹ����   
    int w;                                                 //�ߵ�Ȩֵ   
}Edge; 

void kruskal(MGraph G)  
{  
    int i,j,u1,v1,sn1,sn2,k;  
    int vset[VertexNum];                                    //�������飬�ж����������Ƿ���ͨ   
    int E[EdgeNum];                                         //������еı�   
    k=0;                                                    //E������±��0��ʼ   
    for (i=0;i<G.n;i++)  
    {  
        for (j=0;j<G.n;j++)  
        {  
            if (G.edges[i][j]!=0 && G.edges[i][j]!=INF)  
            {  
                E[k].u=i;  
                E[k].v=j;  
                E[k].w=G.edges[i][j];  
                k++;  
            }  
        }  
    }     
    heapsort(E,k,sizeof(E[0]));                            //�����򣬰�Ȩֵ��С��������       
    for (i=0;i<G.n;i++)                                    //��ʼ����������   
    {  
        vset[i]=i;  
    }  
    k=1;                                                   //���ɵı��������Ҫ�պ�Ϊ�ܱ���   
    j=0;                                                   //E�е��±�   
    while (k<G.n)  
    {   
        sn1=vset[E[j].u];  
        sn2=vset[E[j].v];                                  //�õ����������ڵļ��ϱ��   
        if (sn1!=sn2)                                      //����ͬһ���ϱ���ڵĻ����ѱ߼�����С������   
        {
            printf("%d ---> %d, %d",E[j].u,E[j].v,E[j].w);       
            k++;  
            for (i=0;i<G.n;i++)  
            {  
                if (vset[i]==sn2)  
                {  
                    vset[i]=sn1;  
                }  
            }             
        }  
        j++;  
    }  
}  
