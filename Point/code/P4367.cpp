#include<stdio.h>
#include<vector>
#include<algorithm>
#define cmax(a,b) (b>a?a=b:a)
#define cmin(a,b) (b<a?a=b:a)
using namespace std;
const int N=150005,inf=1e9;
typedef long long ll;
const ll INF=1e18;
int La[N],To[N*2],Ne[N*2],Le[N*2],TOT;
int n,Q,A,S,Size[N],Fa[N],MIN,Root;
int C[N],root;
bool vis[N];int Dep[N],Dis[32][N],*dis,*predis;
typedef pair<int,ll> pp;
vector<pp> Dist[N],*dist;
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
	S=s;MIN=inf;GenSize(u,0);return Root; 
}
void GenDis(int u,int f) {
	int i,j,k,v;
	dist->push_back(pp(C[u],dis[u]-predis[u]));
	for(i=La[u];i;i=Ne[i]) {
		v=To[i];if(vis[v]||v==f) continue;
		dis[v]=dis[u]+Le[i];GenDis(v,u);
	}
}
void init(int u,int s,int dep) {
	int i,j,k,v;
	vis[u]=1;
	Dep[u]=dep;
	dis=Dis[dep];
	predis=Dis[dep-1];
	dist=Dist+u;
	dist->push_back(pp(inf+1,0));
	dist->push_back(pp(C[u],0-predis[u]));
	vector<pp> &t=*dist;
	for(i=La[u];i;i=Ne[i]) {
		v=To[i];if(vis[v]) continue;
		dis[v]=Le[i];GenDis(v,0);
	}
	sort(t.begin(),t.end());
	int len=t.size();
	for(i=len-2;i>=0;i--)
	t[i].second+=t[i+1].second;
	for(i=La[u];i;i=Ne[i]) {
		v=To[i];if(vis[v]) continue;
		if(Size[v]>Size[u]) Size[v]=s-Size[u];
		k=Size[v];v=FindRoot(v,k);
		Fa[v]=u;init(v,k,dep+1);
	}
}
ll getAns(int u,int L,int R) {
	ll ret=0;int x=u;
	while(u) {
		auto t1=lower_bound(Dist[u].begin(),Dist[u].end(),pp(L,-INF)),
			t2=upper_bound(Dist[u].begin(),Dist[u].end(),pp(R,INF));
		ret+=(t2-t1)*(Dis[Dep[u]][x]-Dis[Dep[u]-1][x])+t1->second-t2->second;
		u=Fa[u];
	}
	return ret;
}
int main() {
	int i,j,k,x,y,z,u,a,b;
	ll ans=0;
	scanf("%d%d%d",&n,&Q,&A);
	for(i=1;i<=n;i++) scanf("%d",&C[i]);
	for(i=1;i<n;i++) {
		scanf("%d%d%d",&x,&y,&z);
		AE(x,y,z);AE(y,x,z);
	}
	root=FindRoot(n,n);
	init(root,n,1);
	while(Q--) {
		scanf("%d%d%d",&u,&a,&b);
		a=(a+ans)%A;b=(b+ans)%A;
		if(a>b) swap(a,b);
		printf("%lld\n",ans=getAns(u,a,b));
	}
}
