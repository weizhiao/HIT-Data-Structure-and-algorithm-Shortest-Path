#include<stdio.h>
#include<stdlib.h>

//图的邻接矩阵存储结构
struct mtgraph
{
    int n;//顶点数和边数
    int edge[16][16];//邻接矩阵
    int verlist[16];
};

typedef struct mtgraph*MTGraph;

int FindMinD(int D[16],int S[16]);
void Dijkstra(MTGraph G,int D[16],int P[16],int S[16]);
void Floyd(int A[16][16],MTGraph G,int P[16][16]);
void PrintEdge(MTGraph G);
MTGraph CreateMTGraph();
int Getbit(int num,int bit);

int main()
{
    MTGraph G=CreateMTGraph();
    PrintEdge(G);
    int A[16][16];
    int P1[16][16];
    int D[16];
    int P[16];
    int S[16];
    Dijkstra(G,D,P,S);
    Floyd(A,G,P1);
    printf("最短的次数为:%d\n",A[0][15]);
    int num=15;
    printf("(1111)");
    while(num!=0)
    {
        num=P[num];
        printf("(");
        for(int k=4; k>=1; k--)
        {
            printf("%d",Getbit(num,k));
        }
        printf(")",num);
    }
    system("pause");
    return 0;
}

int Getbit(int num,int bit)
{
    int temp=num;
    for(int i=0; i<bit-1; i++)
    {
        temp=temp/2;
    }
    return temp%2;
}

void PrintEdge(MTGraph G)
{
    for(int i=0; i<G->n; i++)
    {
        for(int j=0; j<G->n; j++)
        {
            if(G->edge[i][j]==1)
            {
                printf("(");
                for(int k=4; k>=1; k--)
                {
                    printf("%d",Getbit(i,k));
                }
                printf(",");
                for(int k=4; k>=1; k--)
                {
                    printf("%d",Getbit(j,k));
                }
                printf(")\n");
            }
        }
    }
}

MTGraph CreateMTGraph()
{
    MTGraph G=malloc(sizeof(struct mtgraph));
    G->n=16;
    for(int i=0; i<=15; i++)
    {
        G->verlist[i]=i;
    }
    for(int i=0; i<G->n; i++)
    {
        for(int j=0; j<G->n; j++)
        {
            G->edge[i][j]=10000;
        }
    }
    for(int i=0; i<G->n; i++)
    {
        for(int j=0; j<G->n; j++)
        {
            int count=0;
            for(int k=1; k<4; k++)
            {
                if(Getbit(G->verlist[j],k)!=Getbit(G->verlist[i],k))
                {
                    count++;
                }
            }
            if(Getbit(G->verlist[i],4)!=Getbit(G->verlist[j],4)&&count<=1)
            {
                G->edge[i][j]=1;
            }
        }
    }
    for(int i=0; i<G->n; i++)
    {
        for(int j=0; j<G->n; j++)
        {
            if(Getbit(G->verlist[i],4)==1&&Getbit(G->verlist[i],3)==0&&Getbit(G->verlist[i],2)==0)
            {
                G->edge[i][j]=10000;
            }
            if(Getbit(G->verlist[i],4)==0&&Getbit(G->verlist[i],3)==1&&Getbit(G->verlist[i],2)==1)
            {
                G->edge[i][j]=10000;
            }
            if(Getbit(G->verlist[i],4)==0&&Getbit(G->verlist[i],2)==1&&Getbit(G->verlist[i],1)==1)
            {
                G->edge[i][j]=10000;
            }
            if(Getbit(G->verlist[j],4)==1&&Getbit(G->verlist[j],2)==0&&Getbit(G->verlist[j],1)==0)
            {
                G->edge[i][j]=10000;
            }
            if(Getbit(G->verlist[j],4)==1&&Getbit(G->verlist[j],3)==0&&Getbit(G->verlist[j],2)==0)
            {
                G->edge[i][j]=10000;
            }
            if(Getbit(G->verlist[j],4)==0&&Getbit(G->verlist[j],3)==1&&Getbit(G->verlist[j],2)==1)
            {
                G->edge[i][j]=10000;
            }
            if(Getbit(G->verlist[j],4)==0&&Getbit(G->verlist[j],2)==1&&Getbit(G->verlist[j],1)==1)
            {
                G->edge[i][j]=10000;
            }
            if(Getbit(G->verlist[j],4)==1&&Getbit(G->verlist[j],2)==0&&Getbit(G->verlist[j],1)==0)
            {
                G->edge[i][j]=10000;
            }
        }
    }
    return G;
}

int FindMinD(int D[16],int S[16])
{

    int min=2;
    int temp=10000;
    for(int i=1; i<16; i++)
    {
        if(D[i]<temp&&S[i]==0)
        {
            min=i;
            temp=D[i];
        }
    }
    return min;
}

void Dijkstra(MTGraph G,int D[16],int P[16],int S[16])
{
    S[0]=1;
    for(int i=1; i<16; i++)
    {
        S[i]=0;
        P[i]=0;
        D[i]=G->edge[0][i];
    }
    for(int i=1; i<16; i++)
    {
        int w=FindMinD(D,S);
        S[w]=1;
        for(int j=1; j<16; j++)
        {
            if(S[j]!=1)
            {
                int sum=D[w]+G->edge[w][j];
                if(sum<D[j])
                {
                    D[j]=sum;
                    P[j]=w;
                }
            }
        }
    }
}

void Floyd(int A[16][16],MTGraph G,int P[16][16]){
    for(int i=0;i<G->n;i++){
        for(int j=0;j<G->n;j++){
            A[i][j]=G->edge[i][j];
            P[i][j]=-1;
        }
    }
    for(int k=0;k<G->n;k++){
        for(int i=0;i<G->n;i++){
            for(int j=0;j<G->n;j++){
                if(A[i][k]+A[k][j]<A[i][j]){
                    A[i][j]=A[i][k]+A[k][j];
                    P[i][j]=k;
                }
            }
        }
    }
}
