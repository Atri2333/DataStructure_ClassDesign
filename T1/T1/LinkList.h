#ifndef LINKLIST_H
#define LINKLIST_H
#include"Parcel.h"
#include<set>
#include<algorithm>
typedef int Status;

#define OK 1 //正确
#define SYSTEMERROR 0 //系统错误
#define OVERSIZE -1 //超过限制
#define FAILPICK 2 //未找到包裹

std::set<std::string> User_Parcel_ID[MAX_PERSON];

typedef struct LNode
{
	Parcel Data;
	LNode *next;
}LNode;

typedef struct
{
	LNode *Head;
	int MaxSize,Size;
	bool *Used;
}LinkList;

Status CreateID(int x, Parcel &P)
{
	P.id = x;
	P.ID.clear();
	P.ID += (P.Size + '0');
	P.ID += '-';
	P.ID += (x / 100 + '0'); x %= 100;
	P.ID += (x / 10 + '0'); x %= 10;
	P.ID += (x + '0');
	return OK;
}

Status UpdateListInFile(LinkList &L)
{
	std::fstream file("Update.log",std::ios::app);
	file << "货架更新：";
	if (L.MaxSize == 500)
		file << "小";
	else if (L.MaxSize == 100)
		file << "中";
	else
		file << "大";
	file << std::endl;
	LNode *p = L.Head->next; int cnt = 0;
	while (p != NULL)
	{
		file << "包裹" << ++cnt << "：" << std::endl;
		PrintParcelData(p->Data,file);
		file << "——————————————————————" << std::endl;
		p = p->next;
	}
	file.flush();
	file.close();
	return OK;
}

Status CreateList(LinkList &L,const int _Size)
{
	L.Head = new LNode;
	if (L.Head == NULL) 
		return SYSTEMERROR;
	L.Head->next = NULL;
	L.MaxSize = _Size;
	L.Size = 0;
	L.Used = new bool[_Size + 1];
	if (L.Used == NULL)
		return SYSTEMERROR;
	memset(L.Used, 0, (_Size + 1) * sizeof(bool));
	return OK;
}

Status AppendList(LinkList &L, Parcel &P)
{
	if (L.Size == L.MaxSize)
		return OVERSIZE;
	for(int i = 1; i <= L.MaxSize; ++i)
		if (!L.Used[i])
		{
			CreateID(i, P);
			L.Used[i] = true;
			break;
		}
	LNode *p = L.Head->next,*pre = L.Head;
	while (p != NULL && p->Data.ID < P.ID)
		pre = p, p = p->next;
	LNode *new_p = new LNode;
	if (new_p == NULL)
		return SYSTEMERROR;
	new_p->Data = P;
	new_p->next = p;
	pre->next = new_p;
	++L.Size;
	return OK;
}

Status PickListByID(LinkList &L, std::string &ID, Parcel &ret)
{
	LNode *pre = L.Head, *now = L.Head->next;
	while (now != NULL)
	{
		if (now->Data.ID == ID)
		{
			pre->next = now->next;
			ret = now->Data;
			--L.Size;
			L.Used[ret.id] = false;
			delete now;
			return OK;
			now = pre->next;
		}
		else
		{
			pre = now;
			now = now->next;
		}
	}
	return FAILPICK;
}

Status PickListByTel(LinkList &L, std::string Tel, int &ret)
{
	LNode *pre = L.Head, *now = L.Head->next;
	while (now != NULL)
	{
		if (now->Data.user.Tel == Tel)
		{
			++ret;
			pre->next = now->next;
			Parcel ret = now->Data;
			--L.Size;
			L.Used[ret.id] = false;
			delete now;
			now = pre->next;
		}
		else
		{
			pre = now;
			now = now->next;
		}
	}
	return OK;
}

Status ClearList(LinkList &L, Date &D,int &cnt)
{
	LNode *pre = L.Head, *now = L.Head->next;
	while (now != NULL)
	{
		if (Sub(D,now->Data.ArrDate) >= 2)
		{
			pre->next = now->next;
			--L.Size; ++cnt;
			L.Used[now->Data.id] = false;
			for (int i = 0; i < MAX_PERSON; ++i)
			{
				auto it = User_Parcel_ID[i].find(now->Data.ID);
				if (it != User_Parcel_ID[i].end())
				{
					User_Parcel_ID[i].erase(it);
				}
			}
			delete now;
			now = pre->next;
		}
		else
		{
			pre = now;
			now = now->next;
		}
	}
	return OK;
}

Status DestroyList(LinkList &L)
{
	LNode *p = L.Head->next;
	while (p != NULL)
	{
		LNode *tmp = p;
		p = p->next;
		delete tmp;
	}
	delete L.Head;
	L.Head = NULL;
	L.MaxSize = L.Size = 0;
	delete[] L.Used;
	return OK;
}
#endif // !LINKLIST_H