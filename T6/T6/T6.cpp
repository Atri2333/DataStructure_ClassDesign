#include<vector>
#include<random>
#include<string>
#include<cassert>
#include<cmath>
#include<fstream>
#include<algorithm>
#include<queue>
#include<ctime>
#include<iostream>
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
const ll mod = INT_MAX;
int rnd(int x) { return mrand() % x; }
ll powmod(ll a, ll b) { ll ret = 1; a %= mod; assert(b >= 0); for (; b; b >>= 1) { if (b & 1)ret = ret * a%mod; a = a * a%mod; }return ret; }
ll gcd(ll a, ll b) { return b ? gcd(b, a%b) : a; }
ll lcm(ll a, ll b) { return a / gcd(a, b)*b; }

const int n = 50000;
int Cache[50010];
int A[50010];

void Debug()
{
	rep(i, 1, n)
		printf("%d ", A[i]);
	putchar('\n');
}

void CreateData()
{
	fstream FILE("data.txt", ios::out);
	rep(i, 1, n)
		Cache[i] = fabs(rnd(mod));
	sort(Cache + 1, Cache + n + 1);
	rep(i, 1, n)
		FILE << Cache[i] << ' ';
	per(i, 1, n)
		FILE << Cache[i] << ' ';
	rep(j, 1, 8)
	{
		rep(i, 1, n)
			FILE << (int)fabs(rnd(mod)) << ' ';
	}
	FILE.close();
}

void Check()
{
//	printf("%d %d\n", A[1], A[n]);
	rep(i, 1, n - 1)
		assert(A[i] <= A[i + 1]);
}

void Insert(int i)
{
	int tmp = A[i];
	int j;
	for (j = i; j > 1; --j)
		if (tmp < A[j - 1])
			A[j] = A[j - 1];
		else break;
	A[j] = tmp;
}

void InsertSort()
{
	rep(i, 2, n)
		Insert(i);
}

void ShellInsert(int d)
{
	rep(i, d + 1, n)
	{
		if (A[i] < A[i - d])
		{
			int tmp = A[i], j;
			for (j = i; j > d; j -= d)
				if (tmp < A[j - d])
					A[j] = A[j - d];
				else break;
			A[j] = tmp;
		}
	}
}

void ShellSort() //Hibbard增量序列
{
	int d[30], tot = 0;
	rep(j, 1, 20)
	{
		d[j] = (1 << j) - 1;
		if (d[j] >= n)
			break;
		++tot;
	}
	per(i, 1, tot)
		ShellInsert(d[i]);
}

void BubbleSort()
{
	rep(i, 1, n)
	{
		rep(j, 1, n - i)
			if (A[j] > A[j + 1])
			{
				int tmp = A[j];
				A[j] = A[j + 1];
				A[j + 1] = tmp;
			}
	}
}

int Partition(int l, int r)
{
	int tmp = A[(l+r)>>1];
	A[(l + r) >> 1] = A[l];
	A[l] = tmp;
	while (l < r)
	{
		while (l < r && A[r] >= tmp)
			--r;
		A[l] = A[r];
		while (l < r && A[l] <= tmp)
			++l;
		A[r] = A[l];
	}
	A[l] = tmp;
	return l;
}

void QSort(int l, int r)
{
	if (l < r)
	{
		int p = Partition(l, r);
		QSort(l, p-1);
		QSort(p + 1, r);
		
	}
}

void QuickSort()
{
	QSort(1, n);
}

void SelectSort()
{
	rep(i, 1, n)
	{
		int k = i;
		rep(j, i + 1, n)
			if (A[k] > A[j])
				k = j;
		int tmp = A[i];
		A[i] = A[k];
		A[k] = tmp;
	}
}

void HeapAdjust(int l, int r)
{
	int tmp = A[l];
	int i = l, j = i << 1;
	while (j <= r)
	{
		if (j + 1 <= r && A[j + 1] > A[j])
			++j;
		if (tmp > A[j])
			break;
		A[i] = A[j];
		i = j;
		j <<= 1;
	}
	A[i] = tmp;
}

void HeapSort()
{
	per(i, 1, n / 2)
		HeapAdjust(i, n);
	per(i, 2, n)
	{
		swap(A[1], A[i]);
		HeapAdjust(1, i - 1);
	}
}

void Merge(int l, int mid, int r)
{
	int T[50010],tot = 0;
	int i = l, j = mid + 1;
	while (i <= mid && j <= r)
	{
		if (A[i] < A[j])
			T[++tot] = A[i++];
		else
			T[++tot] = A[j++];
	}
	while(i <= mid)
		T[++tot] = A[i++];
	while (j <= r)
		T[++tot] = A[j++];
	rep(k, l, r)
		A[k] = T[k - l + 1];
}

void MSort(int d)
{
	int i = 1;
	while (i + 2 * d <= n)
	{
		Merge(i, i + d - 1, i + 2 * d - 1);
		i += d << 1;
	}
	if (i + d <= n)
		Merge(i, i + d - 1, n);
}

void MergeSort()
{
	for (int i = 1; i <= n; i <<= 1)
		MSort(i);
}

int Q[50010][10]; //手写队列，在VS环境下比STL快100倍（

void RadixSort()
{
	
	int l[10], r[10];
//	queue<int> Q[10];
	ll bas = 1;
	rep(i, 1, 10)
	{
		bas *= 10;
		rep(j, 0, 9)
			l[j] = 1, r[j] = 0;
		rep(j, 1, n)
		{
			int m = (A[j] % bas) / (bas / 10);
			Q[++r[m]][m] = A[j];
		}
		int k = 0;
		rep(j, 0, 9)
			while (l[j] <= r[j])
				A[++k] = Q[l[j]++][j];
	}
}

void Solve()
{
	clock_t start,end;
	string s[9] = { "直接插入排序","希尔排序","冒泡排序","快速排序","选择排序","堆排序","归并排序","基数排序" };
	double Tim[9][12];
	fstream FILE("data.txt", ios::in);
	rep(j, 0, 9)
	{
		cout << "第" << j + 1 << "组数据";
		if (j == 0) printf("(升序)");
		if (j == 1) printf("(降序)");
		printf("：\n");
		rep(i, 1, n)
			FILE >> Cache[i];
		rep(i, 1, n)
			A[i] = Cache[i];
		start = clock();
		InsertSort(); Check();
		end = clock();
		Tim[0][j] = (double)(end - start);
		cout << s[0] << "用时(ms)：" << Tim[0][j] << endl;
		rep(i, 1, n)
			A[i] = Cache[i];
		start = clock();
		ShellSort(); Check();
		end = clock();
		Tim[1][j] = (double)end - start;
		cout << s[1] << "用时(ms)：" << Tim[1][j] << endl;
		rep(i, 1, n)
			A[i] = Cache[i];
		start = clock();
		BubbleSort(); Check();
		end = clock();
		Tim[2][j] = (double)end - start;
		cout << s[2] << "用时(ms)：" << Tim[2][j] << endl;
		rep(i, 1, n)
			A[i] = Cache[i];
		start = clock();
		QuickSort(); Check();
		end = clock();
		Tim[3][j] = (double)end - start;
		cout << s[3] << "用时(ms)：" << Tim[3][j] << endl;
		rep(i, 1, n)
			A[i] = Cache[i];
		start = clock();
		SelectSort(); Check();
		end = clock();
		Tim[4][j] = (double)end - start;
		cout << s[4] << "用时(ms)：" << Tim[4][j] << endl;
		rep(i, 1, n)
			A[i] = Cache[i];
		start = clock();
		HeapSort(); Check();
		end = clock();
		Tim[5][j] = (double)end - start;
		cout << s[5] << "用时(ms)：" << Tim[5][j] << endl;
		rep(i, 1, n)
			A[i] = Cache[i];
		start = clock();
		MergeSort(); Check();
		end = clock();
		Tim[6][j] = (double)end - start;
		cout << s[6] << "用时(ms)：" << Tim[6][j] << endl;
		rep(i, 1, n)
			A[i] = Cache[i];
		start = clock();
		RadixSort(); Check();
		end = clock();
		Tim[7][j] = (double)end - start;
		cout << s[7] << "用时(ms)：" << Tim[7][j] << endl;
	//	Debug();
	}
	FILE.close();
	rep(i, 0, 7)
	{
		Tim[i][10] = 0;
		rep(j, 2, 9)
			Tim[i][10] += Tim[i][j];
	//	cout << Tim[i][10] << endl;
		Tim[i][10] /= 8;
	}
	printf("查看最终结果:\n");
	system("pause");
	system("cls");
	printf("————————————————————————————————————\n");
	printf("排序方法(ms)            升序数据          降序数据          随机数据\n");
	rep(i, 0, 7)
	{
		cout << s[i];
		rep(j, 1, 26 - s[i].size())
			putchar(' ');
		int wei = 0,tmp = Tim[i][0];
		while (tmp) ++wei, tmp /= 10; if (!wei) ++wei;
		cout << Tim[i][0];
		rep(j, 1, 18 - wei)
			putchar(' ');
		wei = 0, tmp = Tim[i][1];
		while (tmp) ++wei, tmp /= 10; if (!wei) ++wei;
		cout << Tim[i][1];
		rep(j, 1, 18 - wei)
			putchar(' ');
		cout << (int)Tim[i][10] << endl;
	}
	printf("————————————————————————————————————\n");
}

int main()
{
	srand((unsigned)time(NULL));
	CreateData();
	Solve();
	return 0;
}