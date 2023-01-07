#ifndef PARCEL_H
#define PARCEL_H
#include<iostream>
#include<fstream>
#include"Date.h"
#include"User.h"

#define SMALL 1
#define MEDIUM 2
#define LARGE 3

typedef struct Parcel
{
	std::string ID;
	int id;
	User user;
	int Size;
	Date ArrDate;
}Parcel;

void PrintParcelData(Parcel &P,std::fstream &fp)
{
	fp << "包裹编号：" << P.ID << std::endl;
	fp << "包裹取件人：" << P.user.Name << std::endl;
	fp << "包裹取件人电话：" << P.user.Tel << std::endl;
	fp << "包裹类型：";
	switch (P.Size)
	{
	case SMALL: fp << "小"; break;
	case MEDIUM:fp << "中"; break;
	case LARGE:fp << "大"; break;
	default: fp << "未知";
	}
	fp << std::endl;
	fp << "包裹到达日期：" << P.ArrDate.Year << "年" << P.ArrDate.Month << "月"
		<< P.ArrDate.Day << "日" << std::endl;
}

void PrintParcelData(Parcel &P)
{
	std::cout << "包裹编号：" << P.ID << std::endl;
	std::cout << "包裹取件人：" << P.user.Name << std::endl;
	std::cout << "包裹取件人电话：" << P.user.Tel << std::endl;
	std::cout << "包裹类型：";
	switch (P.Size)
	{
	case SMALL: std::cout << "小"; break;
	case MEDIUM:std::cout << "中"; break;
	case LARGE:std::cout << "大"; break;
	default: std::cout << "未知";
	}
	std::cout << std::endl;
	std::cout << "包裹到达日期：" << P.ArrDate.Year << "年" << P.ArrDate.Month << "月"
		<< P.ArrDate.Day << "日" << std::endl;
}
#endif // !PARCEL_H
