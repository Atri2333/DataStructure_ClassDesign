#ifndef DATE_H
#define DATE_H
typedef struct Date
{
	int Day, Month, Year;
	bool operator ==(const Date &v)const
	{
		return Day == v.Day && Month == v.Month && Year == v.Year;
	}
}Date;

int Month_Days[13] = { 114514,31,28,31,30,31,30,31,31,30,31,30,31 };

inline bool pd4(Date &D)
{
	if (D.Year % 4 == 0 && D.Year % 100 || D.Year % 400 == 0)
		return true;
	return false;
}

inline void UpDate(Date &D)
{
	if (D.Day < Month_Days[D.Month])
		++D.Day;
	else if(D.Day == Month_Days[D.Month])
	{
		if (pd4(D) && D.Month == 2) ++D.Day;
		else if (D.Month == 12)
		{
			++D.Year;
			D.Day = D.Month = 1;
		}
		else
		{
			++D.Month;
			D.Day = 1;
		}
	}
	else
	{
		++D.Month;
		D.Day = 1;
	}
}

int Sub(Date a, Date b)
{
	int ret = 0;
	while (!(a == b)) ++ret, UpDate(b);
	return ret;
}
#endif