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
	fp << "������ţ�" << P.ID << std::endl;
	fp << "����ȡ���ˣ�" << P.user.Name << std::endl;
	fp << "����ȡ���˵绰��" << P.user.Tel << std::endl;
	fp << "�������ͣ�";
	switch (P.Size)
	{
	case SMALL: fp << "С"; break;
	case MEDIUM:fp << "��"; break;
	case LARGE:fp << "��"; break;
	default: fp << "δ֪";
	}
	fp << std::endl;
	fp << "�����������ڣ�" << P.ArrDate.Year << "��" << P.ArrDate.Month << "��"
		<< P.ArrDate.Day << "��" << std::endl;
}

void PrintParcelData(Parcel &P)
{
	std::cout << "������ţ�" << P.ID << std::endl;
	std::cout << "����ȡ���ˣ�" << P.user.Name << std::endl;
	std::cout << "����ȡ���˵绰��" << P.user.Tel << std::endl;
	std::cout << "�������ͣ�";
	switch (P.Size)
	{
	case SMALL: std::cout << "С"; break;
	case MEDIUM:std::cout << "��"; break;
	case LARGE:std::cout << "��"; break;
	default: std::cout << "δ֪";
	}
	std::cout << std::endl;
	std::cout << "�����������ڣ�" << P.ArrDate.Year << "��" << P.ArrDate.Month << "��"
		<< P.ArrDate.Day << "��" << std::endl;
}
#endif // !PARCEL_H
