#include<time.h>
#include<queue>
#include"LinkList.h"
#define ATRIKAWAII 233
Date _Time;
LinkList S, M, L;
std::queue<int> _Q;
int dust_sum;
int Permutation[MAX_PERSON],Pick_Cnt[MAX_PERSON];

void Init()
{
	system("cls");
	for (int i = 0; i < MAX_PERSON; ++i)
		Permutation[i] = i, 
		Pick_Cnt[i] = 0;
	for (int i = 0; i < rand() % ATRIKAWAII; ++i)
	{
		int x = rand() % MAX_PERSON, y = rand() % MAX_PERSON;
		std::swap(Permutation[x], Permutation[y]);
	}
	std::cout << "�������ڣ�" << _Time.Year << "��" << _Time.Month << "��"
		<< _Time.Day << "��" << std::endl;

	int cntS = 0, cntM = 0, cntL = 0;
	ClearList(S, _Time, cntS);
	UpdateListInFile(S);
	ClearList(M, _Time, cntM);
	UpdateListInFile(M);
	ClearList(L, _Time, cntL);
	UpdateListInFile(L);

	std::cout << "��������ڰ�����\nС�Ͱ����� " << cntS << " ��\n���Ͱ����� " << cntM << " ��\n���Ͱ����� "
		<< cntL << " ��\n";
	_Q.push(cntS + cntM + cntL);
	dust_sum += cntS + cntM + cntL;
}

Status CreateParcel(LinkList &L)
{
	int userid = rand() % MAX_PERSON;
	Parcel P;
	P.ArrDate = _Time;
	if (L.MaxSize == 500)
		P.Size = SMALL;
	else if (L.MaxSize == 100)
		P.Size = MEDIUM;
	else P.Size = LARGE;
	P.user = _UserList[userid];
	Status ret = AppendList(L, P);
	User_Parcel_ID[userid].insert(P.ID);
	return ret;
}

Status PickParcel(int userid)
{
	Status st1 = FAILPICK,st2 = FAILPICK,st3 = FAILPICK;
	int _mode = rand() % 2;
	auto it = User_Parcel_ID[userid].begin();
	if (it == User_Parcel_ID[userid].end())
	{
		std::cout << "�û� " << _UserList[userid].Name << " �ް�����\n";
		return OK;
	}
	if (_mode)
	{
		std::cout << "ͨ���绰����ƥ�䷽ʽ��ȡ�û� " << _UserList[userid].Name << " �İ����У�\n";
		PickListByTel(S, _UserList[userid].Tel, Pick_Cnt[userid]);
		PickListByTel(M, _UserList[userid].Tel, Pick_Cnt[userid]);
		PickListByTel(L, _UserList[userid].Tel, Pick_Cnt[userid]);
		std::cout << "�ɹ���ȡ���� " << Pick_Cnt[userid] << " �ݣ�";
	}
	else
	{
		int x = rand() % User_Parcel_ID[userid].size();
		while (x > 1) ++it, --x;
		Parcel RET;
		std::string str = *it;
		std::cout << "ͨ��ȡ���� " << str <<" ƥ�䷽ʽ��ѯ�û� " << _UserList[userid].Name << " �İ�����\n";
		st1 = PickListByID(S, str, RET);
		if(st1 == FAILPICK)st2 = PickListByID(M, str, RET);
		if (st1 == FAILPICK && st1 == st2) st3 = PickListByID(L, str, RET);
		if (st1 == st2 && st2 == st3)
			std::cout << "ȡ����ʧ�ܣ�";
		else
		{
			++Pick_Cnt[userid];
			std::cout << "ȡ�����ɹ��������������Ϣ��" << std::endl;
			PrintParcelData(RET);
			std::cout << "ȡ��ʣ�������...\n";
			PickListByTel(S, _UserList[userid].Tel, Pick_Cnt[userid]);
			PickListByTel(M, _UserList[userid].Tel, Pick_Cnt[userid]);
			PickListByTel(L, _UserList[userid].Tel, Pick_Cnt[userid]);
			std::cout << "�ɹ���ȡ���� " << Pick_Cnt[userid] << " �ݣ�";
		}
	}
	return OK;
}

int main()
{
	std::fstream file("Update.log", std::ios::out);
	file.close();
	Status st;
	CreateUser();
	srand((unsigned)time(NULL));
	time_t now = time(NULL);
	struct tm p;
	localtime_s(&p, &now);
	_Time.Year = p.tm_year + 1900;
	_Time.Month = p.tm_mon + 1;
	_Time.Day = p.tm_mday;
	CreateList(S, 500);
	CreateList(M, 100);
	CreateList(L, 50);
	while (ATRIKAWAII)
	{
		Init();
		int n0, n1, n2;
		std::cout << "�������������\n";
		n0 = rand() % (500 - S.Size);
		n1 = rand() % (100 - M.Size);
		n2 = rand() % (50 - L.Size);
		std::cout << "С�Ͱ��� " << n0 << " ��" << std::endl;
		std::cout << "���Ͱ��� " << n1 << " ��" << std::endl;
		std::cout << "���Ͱ��� " << n2 << " ��" << std::endl;
		std::cout << "�ּ��뵽��Ӧ�Ļ���..." << std::endl;
		for (int i = 0; i < n0; ++i)
		{
			st = CreateParcel(S);
			if (st == OVERSIZE)
				puts("С�ͻ�������������");
			else if (st == SYSTEMERROR)
				puts("ϵͳ������Ӱ���ʧ�ܣ�");
		}
		for (int i = 0; i < n1; ++i)
		{
			st = CreateParcel(M);
			if (st == OVERSIZE)
				puts("���ͻ�������������");
			else if (st == SYSTEMERROR)
				puts("ϵͳ������Ӱ���ʧ�ܣ�");
		}
		for (int i = 0; i < n2; ++i)
		{
			st = CreateParcel(L);
			if (st == OVERSIZE)
				puts("���ͻ�������������");
			else if (st == SYSTEMERROR)
				puts("ϵͳ������Ӱ���ʧ�ܣ�");
		}
		std::cout << "�����ϣ���־ͬ��������\n";
		std::cout << "�����������ȡ�����¼�\n";
		system("pause");
		system("cls");
		UpdateListInFile(S);
		UpdateListInFile(M);
		UpdateListInFile(L);
		int _M = rand() % MAX_PERSON;
		if (!_M) ++_M;
		std::cout << "������ " << _M << " ���û���ȡ����\n";
		for (int i = 0; i < _M; ++i)
			puts(""),
			PickParcel(Permutation[i]),
			User_Parcel_ID[Permutation[i]].clear(),
			puts("");
		UpdateListInFile(S);
		UpdateListInFile(M);
		UpdateListInFile(L);
		std::cout << "�����û���ȡ�����������������������ͳ�ƣ�\n";
		system("pause");
		system("cls");
		double aver = 0;
		int mx = -1, mxx = 0, _sum = 0;
		for (int i = 0; i < _M; ++i)
		{
			_sum += Pick_Cnt[Permutation[i]];
			if (Pick_Cnt[Permutation[i]] > mxx)
				mxx = Pick_Cnt[Permutation[i]],
				mx = Permutation[i];
		}
		aver = 1.0 * _sum / _M;
		while (_Q.size() > 7)
			dust_sum -= _Q.front(),
			_Q.pop();
		std::cout << "ͳ����Ϣ���£�\n";
		std::cout << "��ȡ����������" << _sum << " ��\n";
		std::cout << "ȡ��������(" << mxx << "��)���û���" << _UserList[mx].Name << std::endl;
		printf("ƽ��ȡ������%.3lf ��\n", aver);
		std::cout << "���һ������İ���������" << dust_sum << std::endl;
		std::cout << "��Y/y������һ��ģ��:\n";
		std::string ch;
		std::cin >> ch;
		if (!(ch == "Y" || ch == "y"))
			break;
		UpDate(_Time);
	}
	return 0;
}