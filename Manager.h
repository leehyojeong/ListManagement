#pragma once
#include "Member.h"
#include <algorithm>
#include <ctype.h> // 이름 예외처리용 
#include <conio.h>
#include <windows.h>
#define ID_LENGTH_MAX 9
#define PHONE_LENGTH_MAX 11
#define ETC_LENGTH_MAX 30

class Manager
{
private:
	vector<string> m_sav;
	vector<Member> m_org;
	vector<Member> m_sort;
	vector<int> m_err;
	bool menu;
	int nameLength;
	bool errCheck;
public:
	void keyDownESC();
	Manager();
	bool IsKorean(char ch);
	void showMenu();
	void openFile();
	void menu1_show();
	void menu2_sort();
	void menu3_search();
	void menu4_exit();
	void sorting();
	void stringSplit(string line);
	bool correctCheck();
	void Info();
	~Manager();
	void menuInfo();

	void gotoxy(int x, int y);
	int x = 0;
	int y = 0;
	void whenExit();

	int w_people = 0;
	int nen_people = 0;
	int w_money = 0;

};
