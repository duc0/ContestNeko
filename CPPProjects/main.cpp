#include<iostream>
#include<stdio.h>
#include<algorithm>
#include<math.h>
#include<vector>
#include<set>
#include<stdlib.h>
#include<string.h>
#include<queue>
#include<stack>
#include<assert.h>
#include<limits.h>
#define tr(i) for(typeof(i.begin()) it=i.begin(); it!=i.end();it++)
#define pb push_back
#define mp make_pair
#define REP(i,n) for(int i=0;i<n;i++)
#define rep(i,s,n) for(int i=s;i<n;i++)
#define s(n) scanf("%d",&n)
#define XX first
#define X first
#define Y second
#define all(a) a.begin(),a.end()
#define YY second.first
#define ZZ second.second
#define fill(a,b) memset(a,b,sizeof(a))
#define DREP(a) sort(all(a)); a.erase(unique(all(a)),a.end());
#define INDEX(arr,ind) (lower_bound(all(arr),ind)-arr.begin())
#define SZ(x) (int)(x.size())
#define lin(val,j) (DP[j]-val*D[j])
using namespace std;
typedef long long LL;
typedef pair<int,int> pii;
typedef pair<int,pii> piii;
#define MN 1000000
int a[MN];
int pos[MN+10];
int DP[MN];
int main()
{
  int n; s(n);
  REP(i,n) s(a[i]);
  int mx=1;
  REP(i,MN+10) pos[i]=-1;
  for(int i=n-1;i>=0;i--)
  {
    DP[i]=1;
    for(int j=2;(a[i]*j)<=MN;j++)
    {
      if(pos[j*a[i]]==-1) continue;
      DP[i]=max(DP[i],1+DP[pos[j*a[i]]]);
    }
    mx=max(mx,DP[i]);
    pos[a[i]]=i;
  }
  cout<<mx<<endl;
  return 0;
}