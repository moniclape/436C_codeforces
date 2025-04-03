#include<bits/stdc++.h>
using namespace std;
#define LL long long
const int maxn=1e6+7;

char a[1003][11][11];
int c[1003][1003];
int F[1003];
int n,m,k,w;

struct Edge{
    int u,v,w;
} edge[maxn];
int tot;

void addedge(int u,int v,int w){
    edge[tot].u=u;
    edge[tot].v=v;
    edge[tot++].w=w;
}

bool cmp(Edge a,Edge b){
    return a.w<b.w;
}

int Find(int x){
    if(F[x]==-1) return x;
    else return F[x]=Find(F[x]);
}

int Kruskal(){
    memset(F,-1,sizeof(F));
    sort(edge,edge+tot,cmp);
    int cnt=0,ans=0;
    for(int i=0;i<tot; i++){
        int u=edge[i].u,v=edge[i].v,w=edge[i].w;
        int t1=Find(u),t2=Find(v);
        if(t1!=t2){
            ans+=w;
            F[t1]=t2;
            c[u][v]=c[v][u]=1;
            cnt++;
        }if(cnt==k) break;
    }
    return ans;
}

void getEdge(){
    for(int i=1; i<=k; i++){
        addedge(0,i,n*m);
    }
    for(int i=1; i<=k; i++){
        for(int j=i+1; j<=k; j++){
            int sum=0;
            for(int I=0; I<n; I++){
                for(int J=0; J<m; J++){
                    if(a[i][I][J]!=a[j][I][J]){
                        sum+=w;
                    }
                }
            }
            addedge(i,j,sum);
        }
    }
}

int vis[1010];
void dfs(int x){
    for(int i=0; i<=k; i++){
        if(c[x][i]==1&&vis[i]==0){
            vis[i]=1;
            printf("%d %d\n",i,x);
            dfs(i);
        }
    }
    return;
}

int main(){
    while(~scanf("%d%d%d%d",&n,&m,&k,&w)){
        for(int i=1; i<=k; i++){
            for(int j=0; j<n; j++){
                scanf("%s",a[i][j]);
            }
        }
        tot=0;
        getEdge();
        
        for(int i=0; i<=k; i++){
            for(int j=0; j<=k; j++){
                c[i][j]=0;
            }
        }
        int ans=Kruskal();
        printf("%d\n",ans);
        memset(vis,0,sizeof(vis));
        vis[0]=1;
        dfs(0);
    }
    return 0;
}
