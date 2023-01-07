#include<vector>
#include<cassert>
#include<iostream>
#include<cstdlib>
#include<random>
#include<cstring>
using namespace std;
#define rep(i,a,n) for(int i = a;i <= n; ++i)
#define per(i,a,n) for(int i = n; i >= a; --i)
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
typedef double db;
mt19937 mrand(random_device{}());
const ll mod = 998244353;
int rnd(int x) { return mrand() % x; }
ll powmod(ll a, ll b) { ll ret = 1; a %= mod; assert(b >= 0); for (; b; b >>= 1) { if (b & 1)ret = ret * a %mod; a = a * a %mod; }return ret; }
ll gcd(ll a, ll b) { return b ? gcd(b, a%b) : a; }
ll lcm(ll a, ll b) { return a / gcd(a, b)*b; }

int n;
bool vis[110];
int main()
{
	cin >> n;
	while (n--)
	{
		int c;
		cin >> c;
		bool tag;
		rep(i, 1, 20)
		{
			rep(j, 1, 5 - c + 1)
			{
				tag = true;
				rep(k, 1, c)
					tag &= !vis[(i - 1) * 5 + j + k - 1];
				if (tag)
				{
					rep(k, 1, c)
						cout << (i - 1) * 5 + j + k - 1 << ' ',
						vis[(i - 1) * 5 + j + k - 1] = true;
					cout << endl;
					break;
				}
			}
			if (tag)
				break;
		}
		if (tag)
			continue;
		rep(i, 1, 100)
		{
			if (!vis[i])
			{
				vis[i] = true;
				--c;
				cout << i << ' ';
				if (!c)
					break;
			}
		}
		cout << endl;
	}
	return 0;
}