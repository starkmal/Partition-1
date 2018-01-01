#include<stdio.h>
#include<vector>
#define cmax(a,b) (b>a?a=b:a)
#define cmin(a,b) (b<a?a=b:a)
using namespace std;
const int N=150005;
int La[N],To[N*2],Ne[N*2],TOT;
int n,Q,A,S,Size[N],Fa[N],MIN,Root;
bool vis[N];
typedef pair<int,int> pp;
vector<pp> Dist[N];
void AE(int x,int y,int z) {
	To[++TOT]=y;
	Ne[TOT]=La[x];
	La[x]=TOT;
	Le[TOT]=z;
}
void GenSize(int u,int f) {
	int i,j,k,v,MAX=0;
	Size[u]=1;
	for(i=La[u];i;i=Ne[i]) {
		v=To[i];if(vis[v]||v==f) continue;
		GenSize(v,u);Size[u]+=Size[v];
		cmax(MAX,Size[v]);
	}
	if(S-Size[u]>MAX) MAX=S-Size[u];
	if(MAX<MIN) MIN=MAX,Root=u;
}
int FindRoot(int u,int s) {
	S=s;GenSize(u,0);return Root; 
}
void init() {
	
}
int main() {
	
}
