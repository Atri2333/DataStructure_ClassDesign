#include<cstdio>
#include<iostream>
#include<vector>
#include<string>
#include<cassert>
#include<cstring>
using namespace std;
#define rep(i,a,n) for(int i = a;i < n; ++i)
#define per(i,a,n) for(int i = n - 1; i >= a; --i)
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
const ll mod = 1000000007;
ll powmod(ll a, ll b) { ll ret = 1; a %= mod; assert(b >= 0); for (; b; b >>= 1) { if (b & 1)ret = ret * a%mod; a = a * a%mod; }return ret; }
ll gcd(ll a, ll b) { return b ? gcd(b, a%b) : a; }
ll lcm(ll a, ll b) { return a / gcd(a, b)*b; }

int A[4][4];
int F[1111111];
bool vis[1111111];

int Hash()
{
	int ret = 0;
	rep(i, 1, 4)
		rep(j, 1, 4)
		ret = ret * 3 + A[i][j];
	return ret;
}

bool Alice()
{
	rep(i, 1, 4)
	{
		if (A[i][1] == A[i][2] && A[i][2] == A[i][3] && A[i][1] == 1)
			return true;
		if (A[1][i] == A[2][i] && A[2][i] == A[3][i] && A[1][i] == 1)
			return true;
	}
	return A[2][2] == 1 && ((A[1][1] == A[2][2] && A[2][2] == A[3][3]) || (A[3][1] == A[2][2] && A[2][2] == A[1][3]));
}

bool Bob()
{
	rep(i, 1, 4)
	{
		if (A[i][1] == A[i][2] && A[i][2] == A[i][3] && A[i][1] == 2)
			return true;
		if (A[1][i] == A[2][i] && A[2][i] == A[3][i] && A[1][i] == 2)
			return true;
	}
	
	return A[2][2] == 2 && ((A[1][1] == A[2][2] && A[2][2] == A[3][3]) || (A[3][1] == A[2][2] && A[2][2] == A[1][3]));
}

int blank()
{
	int ret = 0;
	rep(i, 1, 4)
		rep(j, 1, 4)
		if (!A[i][j])
			++ret;
	return ret;
}

int DFS(int x)
{
	int sta = Hash();
	if (vis[sta]) return F[sta];
	vis[sta] = true;
	if (Alice())
		return F[sta] = blank() + 1;
	else if (Bob())
		return F[sta] = -(blank() + 1);
	if (blank() == 0)
		return F[sta] = 0;
	int ret;
	if (x == 1) ret = -2333;
	else ret = 2333;
	rep(i,1,4)
		rep(j,1,4)
		if (!A[i][j])
		{
			A[i][j] = x;
			int d = DFS(0x3 ^ x);
			if (x == 1) CMAX(ret, d);
			else CMIN(ret, d);
			A[i][j] = 0;
		}
	return F[sta] = ret;
}
int T;
int main()
{
	cin >> T;
	while (T--)
	{
		memset(vis, 0, sizeof vis);
		rep(i, 1, 4)
			rep(j, 1, 4)
			cin >> A[i][j];
		cout << DFS(1) << endl;
	}
	return 0;
}