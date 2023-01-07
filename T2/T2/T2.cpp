#include<string>
#include<stack>
#include<iostream>
#include<cmath>
#define OK 1
#define ERROR 0 //��������
#define ILLEGALCHAR 2 //���ַǷ��ַ���������������
#define OP_ERROR 3 //������λ�ò��Ϸ�������"1+*2"
#define NUM_ERROR 4 //���ֲ��Ϸ�������1.2.3,.250,666.
#define BRACKET_ERROR 5 //���Ų��Ϸ�������(()))
#define DIV_ERROR 6 //����Ϊ0
//Ȼ��ǵ�����һ��ͷβ�ַ���Ϊ'#'�����


#define EPS 1e-10
int sgn(double x)
{
	if (std::fabs(x) < EPS)
		return 0;
	else if (x > 0)
		return 1;
	else
		return -1;
}

std::string _ORG, A;

int STATUS = 1, __L, __R;
char _cache[6] = { '+','-','*','/','(',')' };

typedef struct Node
{
	bool pd; //0Ϊ��������1Ϊ������
	char ch;
	double num;
	Node(){}
}Node;
Node Cache[2333]; 

int n;
void ClearSpace() //ȥ���ո�
{
	for (auto ch : _ORG)
	{
		if (ch != ' ')
			A.push_back(ch);
	}
}

bool LegalCh(char ch) //�����ж��Ƿ�Ϸ�
{
	if (ch <= '9' && ch >= '0')
		return true;
	for (int i = 0; i < 6; ++i)
		if (ch == _cache[i])
			return true;
	return ch == '.';
}

inline bool isNum(char ch)
{
	return ch <= '9' && ch >= '0';
}

inline bool isOpt(char ch)
{
	for (int i = 0; i < 6; ++i)
		if (ch == _cache[i])
			return true;
	return false;
}

Node Read(int pos) //��ȡ��������Ҫ�ж����ֵĺϷ���
{
	__L = __R = pos;
	Node ret;
	if (isOpt(A[pos])/* && !(A[pos] == '-' && (A[pos-1]=='(' || A[pos-1] == '#'))*/) //���ж�һ��'-'��Ϊ���ŵ����
	{
		ret.ch = A[pos];
		ret.pd = false;
		return ret;
	}
	else//�������
	{
		ret.pd = true;
		int dotcnt = 0,poss = -1; //�ж�
		int zf = 1; //����
		if (A[pos] == '-')
			zf = -1, ++__L,++__R;
		while (!isOpt(A[__R]) && A[__R] != '#')
		{
			dotcnt += A[__R] == '.';
			if (A[__R] == '.') poss = __R;
			++__R;
		}
		--__R;
		if (dotcnt > 1 || A[__R] == '.' || A[__L] == '.')
		{
			STATUS = NUM_ERROR;
			return ret;
		}
		ret.num = 0;
		if (poss == -1) //����
		{
			for (int i = __L; i <= __R; ++i)
				ret.num = ret.num * 10 + A[i] - '0';
		}
		else
		{
			for (int i = __L; i <= poss-1; ++i)
				ret.num = ret.num * 10 + A[i] - '0';
			double c = 1;
			for (int i = poss + 1; i <= __R; ++i)
			{
				c *= 0.1;
				ret.num += (A[i] - '0') * c;
			}
		}
		//ret.num *= zf;
		return ret;
	}
}

void Log_Error()
{
	switch (STATUS)
	{
		case 2:
			puts("���󣺳��ַǷ��ַ�"); 
			printf("�����ֶ�[%d-%d]:", __L + 1, __R + 1);
			putchar('"');
			for (int i = __L; i <= __R; ++i) putchar(A[i]);
			putchar('"'); puts(""); break;
		case 3:
			puts("���󣺲�����λ�ò��Ϸ�"); 
			printf("�����ֶ�[%d-%d]:", __L + 1, __R + 1);
			putchar('"');
			for (int i = __L; i <= __R; ++i) putchar(A[i]);
			putchar('"'); puts(""); break;
		case 4:
			puts("���󣺳��ַǷ����ֶ�"); 
			printf("�����ֶ�[%d-%d]:", __L + 1, __R + 1);
			putchar('"');
			for (int i = __L; i <= __R; ++i) putchar(A[i]);
			putchar('"'); puts(""); break;
		case 5:
			puts("�������Ų�ƥ��");
			break;
		case 6:
			puts("���󣺴��ڳ���Ϊ0");
			break;
		default:
			puts("�����ҳ�����Ҳ��֪���Ĵ��ˣ������Ǵ���");
	}
	
}

void Init()
{
	puts("��������ʽ��");
	std::getline(std::cin,_ORG);
	ClearSpace();
//	printf("���ʽ����Ϊ��%d\n", A.size());
	if (A[0] != '#' || A[A.size() - 1] != '#')
	{
		puts("����ͷβ����'#'������");
		exit(EXIT_FAILURE);
	}
//	puts("��ѯ�Ƿ���ڷǷ��ַ�...");
	for(int i = 1; i < A.size() - 1; ++i)
		if (!LegalCh(A[i]))
		{
			__L = __R = i;
			STATUS = ILLEGALCHAR;
			return;
		}
//	puts("��ѯ�Ƿ���ڷǷ�������...");
	for (int i = 1; i < A.size() - 2; ++i)
	{
		if (isOpt(A[i]) && isOpt(A[i + 1]))
		{
			if (A[i] == ')' || A[i + 1] == '(')
				continue;
			if (A[i] == '(' && A[i + 1] == '-')
				continue;
			__L = i; __R = i + 1;
			STATUS = OP_ERROR;
			return;
		}
		if (isNum(A[i]) && A[i + 1] == '(' || A[i] == ')' && isNum(A[i + 1]))
		{
			__L = i; __R = i + 1;
			STATUS = OP_ERROR;
			return;
		}
	}
	if (isOpt(A[A.size() - 2]) && A[A.size() - 2] != ')')
	{
		__L = __R = A.size() - 2;
		STATUS = OP_ERROR;
		return;
	}
	int i = 1;
//	puts("��ѯ�Ƿ���ڷǷ�����...");
	while (i < A.size() - 1)
	{
//		printf("i = %d\n", i);
		if (A[i] == '-' && (A[i - 1] == '(' || A[i - 1] == '#'))
		{
			Cache[++n].pd = true; Cache[n].num = -1;
			Cache[++n].pd = false; Cache[n].ch = '*';
			++i;
			continue;
		}
		Cache[++n] = Read(i);
		if (STATUS != OK)
			return;
//		if (Cache[n].pd) printf("Ϊ���� %lf\n", Cache[n].num);
//		else printf("Ϊ������ %c\n", Cache[n].ch);
		i = __R + 1;
	}
//	puts("��ѯ�Ƿ���������Ŵ���������...");
	int now = 0;
	for (int i = 1; i <= n; ++i)
	{
		if (Cache[i].pd == false)
		{
			if (Cache[i].ch == '(')
				++now;
			else if (Cache[i].ch == ')')
				--now;
		}
		if (now < 0)
		{
			STATUS = BRACKET_ERROR;
			return;
		}
	}
	if (now)
	{
		STATUS = BRACKET_ERROR;
		return;
	}
}

char cmp(char a, char b)
{
//	printf("cmp: a = %c b = %c\n", a, b);
	switch (a)
	{
	case '+':
	case '-':
		if (b == '+' || b == '-' || b == ')')
			return '>';
		else
			return '<';
	case '*':
	case '/':
		if (b == '(')
			return '<';
		else
			return '>';
	case '(':
		if (b == ')')
			return '=';
		else
			return '<';
	case ')':
		return '>';
	default:
		puts("CMP!");
		STATUS = ERROR;
		return '?';
	}
}

double Operate(double a, double b, char opt)
{
//	printf("a = %lf b = %lf opt = %c\n", a, b, opt);
	switch (opt)
	{
	case '+':
		return a + b;
	case '-':
		return a - b;
	case '*':
		return a * b;
	case '/':
		if (sgn(b) == 0)
		{
			STATUS = DIV_ERROR;
			return 114514;
		}
		return a / b;
	default:
		puts("OPT!");
		STATUS = ERROR;
		return 114514;
	}
}

double cal()
{
	Cache[++n].pd = false; Cache[n].ch = ')';
	std::stack<double> OPND;
	std::stack<char> OPTR;
	OPTR.push('(');
	double a, b, c; char opt;
	int _tot = 0;
	for (int i = 1; i <= n;)
	{
	//	printf("i = %d\n", i);
		if (Cache[i].pd)
			OPND.push(Cache[i].num), ++i,
			printf("��%d��������push OPND %lf\n", ++_tot,OPND.top());
		else
		{
			switch (cmp(OPTR.top(), Cache[i].ch))
			{
			case '<':
				OPTR.push(Cache[i].ch);
				++i;
				printf("��%d��������push OPTR %c\n", ++_tot, OPTR.top());
				break;
			case '>':
				b = OPND.top(); OPND.pop(); printf("��%d��������pop OPND %lf\n", ++_tot, b);
				a = OPND.top(); OPND.pop(); printf("��%d��������pop OPND %lf\n", ++_tot, a);
				opt = OPTR.top(); OPTR.pop(); printf("��%d��������pop OPTR %c\n", ++_tot, opt);
				c = Operate(a, b, opt);
				OPND.push(c); printf("��%d��������push OPND %lf\n", ++_tot, c);
				break;
			case '=':
				OPTR.pop();
				printf("��%d��������pop OPTR %c\n", ++_tot, '(');
				++i;
				break;
			default:
				STATUS = ERROR;
				break;
			}
		}
		if (STATUS != OK)
			return 0;
	//	printf("OPND:");
		
	}
	return OPND.top();
}

int main()
{
	Init();
	if (STATUS != OK)
	{
		Log_Error();
		return 0;
	}
	double ans = cal();
	if (STATUS != OK)
	{
		Log_Error();
		return 0;
	}
	printf("������Ϊ��%lf", ans);
	return 0;
}
