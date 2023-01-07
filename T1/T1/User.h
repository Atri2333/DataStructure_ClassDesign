#ifndef USER_H
#define USER_H
#include<string>
#define MAX_PERSON 25
typedef struct User
{
	std::string Name;
	std::string Tel;
	bool operator ==(const User &v)const
	{
		return Tel == v.Tel;
	}
}User;
User _UserList[MAX_PERSON];

void CreateUser()
{
	_UserList[0].Name = "史凯文";
	_UserList[0].Tel = "114514";
	_UserList[1].Name = "文史凯";
	_UserList[1].Tel = "1919810";
	_UserList[2].Name = "凯文史";
	_UserList[2].Tel = "88488848";
	_UserList[3].Name = "雨霖小姐";
	_UserList[3].Tel = "12345678910";
	_UserList[4].Name = "雨霖大姐";
	_UserList[4].Tel = "01987654321";
	_UserList[5].Name = "迪尔桑凯文";
	_UserList[5].Tel = "15156622992";
	_UserList[6].Name = "迪尔道特雨霖";
	_UserList[6].Tel = "18652055281";
	_UserList[7].Name = "迪尔格兰德桑阿泄";
	_UserList[7].Tel = "19807872289";
	_UserList[8].Name = "池答辩";
	_UserList[8].Tel = "77777777777";
	_UserList[9].Name = "你的答辩真的好迟";
	_UserList[9].Tel = "2828282828";
	_UserList[10].Name = "皮哥";
	_UserList[10].Tel = "55555555555";
	_UserList[11].Name = "魏哥";
	_UserList[11].Tel = "66666666666";
	_UserList[12].Name = "Hop哥";
	_UserList[12].Tel = "18212124641";
	_UserList[13].Name = "Roll King!";
	_UserList[13].Tel = "18858288177";
	_UserList[14].Name = "亚托克斯";
	_UserList[14].Tel = "23333333";
	_UserList[15].Name = "木瓜星灵";
	_UserList[15].Tel = "23333333333";
	_UserList[16].Name = "鸡哥";
	_UserList[16].Tel = "110";
	_UserList[17].Name = "Van♂";
	_UserList[17].Tel = "2222222222";
	_UserList[18].Name = "魔♂男";
	_UserList[18].Tel = "9595959595";
	_UserList[19].Name = "杰哥不要啊";
	_UserList[19].Tel = "114";
	_UserList[20].Name = "无E烦";
	_UserList[20].Tel = "514";
	_UserList[21].Name = "易建联♂";
	_UserList[21].Tel = "1919";
	_UserList[22].Name = "直布罗陀";
	_UserList[22].Tel = "810";
	_UserList[23].Name = "瓦尔只因里";
	_UserList[23].Tel = "6";
	_UserList[24].Name = "老八";
	_UserList[24].Tel = "7474974";
}
#endif // !USER_H
