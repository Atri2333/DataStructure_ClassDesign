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
	std::cout << "当天日期：" << _Time.Year << "年" << _Time.Month << "月"
		<< _Time.Day << "日" << std::endl;

	int cntS = 0, cntM = 0, cntL = 0;
	ClearList(S, _Time, cntS);
	UpdateListInFile(S);
	ClearList(M, _Time, cntM);
	UpdateListInFile(M);
	ClearList(L, _Time, cntL);
	UpdateListInFile(L);

	std::cout << "已清除过期包裹：\n小型包裹： " << cntS << " 个\n中型包裹： " << cntM << " 个\n大型包裹： "
		<< cntL << " 个\n";
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
		std::cout << "用户 " << _UserList[userid].Name << " 无包裹！\n";
		return OK;
	}
	if (_mode)
	{
		std::cout << "通过电话号码匹配方式获取用户 " << _UserList[userid].Name << " 的包裹中：\n";
		PickListByTel(S, _UserList[userid].Tel, Pick_Cnt[userid]);
		PickListByTel(M, _UserList[userid].Tel, Pick_Cnt[userid]);
		PickListByTel(L, _UserList[userid].Tel, Pick_Cnt[userid]);
		std::cout << "成功获取包裹 " << Pick_Cnt[userid] << " 份！";
	}
	else
	{
		int x = rand() % User_Parcel_ID[userid].size();
		while (x > 1) ++it, --x;
		Parcel RET;
		std::string str = *it;
		std::cout << "通过取件码 " << str <<" 匹配方式查询用户 " << _UserList[userid].Name << " 的包裹：\n";
		st1 = PickListByID(S, str, RET);
		if(st1 == FAILPICK)st2 = PickListByID(M, str, RET);
		if (st1 == FAILPICK && st1 == st2) st3 = PickListByID(L, str, RET);
		if (st1 == st2 && st2 == st3)
			std::cout << "取包裹失败！";
		else
		{
			++Pick_Cnt[userid];
			std::cout << "取包裹成功！现输出包裹信息：" << std::endl;
			PrintParcelData(RET);
			std::cout << "取出剩余包裹中...\n";
			PickListByTel(S, _UserList[userid].Tel, Pick_Cnt[userid]);
			PickListByTel(M, _UserList[userid].Tel, Pick_Cnt[userid]);
			PickListByTel(L, _UserList[userid].Tel, Pick_Cnt[userid]);
			std::cout << "成功获取包裹 " << Pick_Cnt[userid] << " 份！";
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
		std::cout << "随机产生包裹：\n";
		n0 = rand() % (500 - S.Size);
		n1 = rand() % (100 - M.Size);
		n2 = rand() % (50 - L.Size);
		std::cout << "小型包裹 " << n0 << " 份" << std::endl;
		std::cout << "中型包裹 " << n1 << " 份" << std::endl;
		std::cout << "大型包裹 " << n2 << " 份" << std::endl;
		std::cout << "现加入到对应的货架..." << std::endl;
		for (int i = 0; i < n0; ++i)
		{
			st = CreateParcel(S);
			if (st == OVERSIZE)
				puts("小型货架容量已满！");
			else if (st == SYSTEMERROR)
				puts("系统错误！添加包裹失败！");
		}
		for (int i = 0; i < n1; ++i)
		{
			st = CreateParcel(M);
			if (st == OVERSIZE)
				puts("中型货架容量已满！");
			else if (st == SYSTEMERROR)
				puts("系统错误！添加包裹失败！");
		}
		for (int i = 0; i < n2; ++i)
		{
			st = CreateParcel(L);
			if (st == OVERSIZE)
				puts("大型货架容量已满！");
			else if (st == SYSTEMERROR)
				puts("系统错误！添加包裹失败！");
		}
		std::cout << "添加完毕！日志同步更新中\n";
		std::cout << "按任意键产生取包裹事件\n";
		system("pause");
		system("cls");
		UpdateListInFile(S);
		UpdateListInFile(M);
		UpdateListInFile(L);
		int _M = rand() % MAX_PERSON;
		if (!_M) ++_M;
		std::cout << "当天有 " << _M << " 名用户来取包裹\n";
		for (int i = 0; i < _M; ++i)
			puts(""),
			PickParcel(Permutation[i]),
			User_Parcel_ID[Permutation[i]].clear(),
			puts("");
		UpdateListInFile(S);
		UpdateListInFile(M);
		UpdateListInFile(L);
		std::cout << "所有用户均取出包裹！按任意键进行数据统计：\n";
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
		std::cout << "统计信息如下：\n";
		std::cout << "总取出包裹量：" << _sum << " 份\n";
		std::cout << "取出最多包裹(" << mxx << "份)的用户：" << _UserList[mx].Name << std::endl;
		printf("平均取出量：%.3lf 个\n", aver);
		std::cout << "最近一周清理的包裹数量：" << dust_sum << std::endl;
		std::cout << "按Y/y进行下一天模拟:\n";
		std::string ch;
		std::cin >> ch;
		if (!(ch == "Y" || ch == "y"))
			break;
		UpDate(_Time);
	}
	return 0;
}