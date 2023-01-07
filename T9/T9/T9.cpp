#pragma GCC optimize(3)
#define _CRT_SECURE_NO_WARNINGS
#include<vector>
#include<map>
#include<set>
#include<random>
#include<iostream>
#include<cassert>
using namespace std;
#define rep(i,a,n) for(register int i = a;i <= n; ++i)
#define per(i,a,n) for(register int i = n; i >= a; --i)
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define all(x) (x).begin(),(x).end()
#define fi first
#define se second
#define SZ(x) ((int)(x).size())
#define CMIN(_a,_b) ((_a>_b)&&(_a=_b))
#define CMAX(_a,_b) ((_a<_b)&&(_a=_b))
typedef vector<int> VI;
typedef basic_string<int> BI;
typedef long long ll;
typedef pair<int, int> PII;
typedef pair<int, long long> PIL;
typedef double db;
mt19937 mrand(random_device{}());
const ll mod = 998244353;
int rnd(int x) { return mrand() % x; }
ll powmod(ll a, ll b) { ll ret = 1; a %= mod; assert(b >= 0); for (; b; b >>= 1) { if (b & 1)ret = ret * a%mod; a = a * a%mod; }return ret; }
ll gcd(ll a, ll b) { return b ? gcd(b, a%b) : a; }
ll lcm(ll a, ll b) { return a / gcd(a, b)*b; }

int n, m;
int cnt0, cnt1; //通信孤岛，通信对

typedef struct Node
{
	int u, v;
	ll x;
	Node(){}
	Node(int a,int b,ll c):u(a),v(b),x(c){}
}Node;

vector<Node> A[100010];
map<PII, int> M;
ll C[400010];

int tot;

void read(int &x)
{
	int f = 1;
	x = 0;
	char s = getchar();
	while (s<'0' || s>'9')
		s = getchar();
	while (s >= '0'&&s <= '9')
	{
		x = x * 10 + s - '0';
		s = getchar();
	}
	x *= f;
}

struct cmp
{
	bool operator ()(const PIL &a, const PIL &b)const
	{
		if (a.se == b.se)
			return a.fi < b.fi;
		return a.se > b.se;
	}
};

set<PIL, cmp> S[100010];

int main()
{
	read(n); read(m);
	cnt0 = n;
	rep(i, 1, m)
	{
	//	printf("Day%d:\n", i);
		int k;
		read(k);
		while (k--)
		{
			int u, v, x, y;
			read(u); read(v); read(x); read(y);
		//	scanf("%d%d%d%d", &u, &v, &x, &y);
			A[i].pb(Node(u, v, x));
			if (i + y <= m)
				A[i + y].pb(Node(u, v, -x));
		}
		for (auto p : A[i])
		{
			int u = p.u, v = p.v;
			int u1 = 0, v1 = 0, u2 = 0, v2 = 0; //对应的
			int x1 = 0, y1 = 0, x2 = 0, y2 = 0; //对应的对应的
			ll x = p.x;
		//	printf("u = %d v = %d x = %lld\n", u, v, x);
			if (!M.count(mp(u, v)))
				M[mp(u, v)] = ++tot;
			if (!M.count(mp(v, u)))
				M[mp(v, u)] = ++tot;
			int t1 = M[mp(u, v)], t2 = M[mp(v, u)];
			int s1 = S[u].size(), s2 = S[v].size();
			if (s1)
			{
				u1 = S[u].begin()->first;
				if(S[u1].size())x1 = S[u1].begin()->first;
			}
			if (s2)
			{
				v1 = S[v].begin()->first;
				if (S[v1].size())y1 = S[v1].begin()->first;
			}
			auto it = S[u].find(mp(v,C[t1]));
			if (it == S[u].end())
			{
				S[u].insert(mp(v, x));
				C[t1] = x;
			}
			else
			{
				C[t1] += x;
				S[u].erase(it);
				if(C[t1]) S[u].insert(mp(v, C[t1]));
			}
			it = S[v].find(mp(u, C[t2]));
			if (it == S[v].end())
			{
				S[v].insert(mp(u, x));
				C[t2] = x;
			}
			else
			{
				C[t2] += x;
				S[v].erase(it);
				if(C[t2]) S[v].insert(mp(u, C[t2]));
			}
			int s11 = S[u].size(), s22 = S[v].size();
			if (s1 == 0 && s11) --cnt0;
			if (s1 && s11 == 0) ++cnt0;
			if (s2 == 0 && s22) --cnt0;
			if (s2 && s22 == 0) ++cnt0;
			if (s11)
			{
				u2 = S[u].begin()->first;
				if (S[u2].size())x2 = S[u2].begin()->first;
			}
			if (s22)
			{
				v2 = S[v].begin()->first;
				if (S[v2].size())y2 = S[v2].begin()->first;
			}
			if (u1 == v && v1 == u)
			{
				if (u2 == v && v2 == u)
					continue;
				else --cnt1;
				if (u == x2) ++cnt1;
				if (v == y2) ++cnt1;
			}
			else if(u2 == v && v2 == u)
			{
				++cnt1;
				if (u == x1) --cnt1;
				if (v == y1) --cnt1;
			}
			else
			{
				if (u == x1 && u != x2) --cnt1;
				if (u != x1 && u == x2) ++cnt1;
				if (v == y1 && v != y2) --cnt1;
				if (v != y1 && v == y2) ++cnt1;
			}
		//	printf("cnt0 = %d cnt1 = %d\n", cnt0, cnt1);
		}
		int l;
		read(l);
		while (l--)
		{
			int id;
			read(id);
			if (!S[id].size())
				puts("0");
			else
				printf("%d\n", S[id].begin()->first);
		}
		int p0, p1;
		read(p0); read(p1);
		if (p0) printf("%d\n", cnt0);
		if (p1) printf("%d\n", cnt1);
	}
	return 0;
}