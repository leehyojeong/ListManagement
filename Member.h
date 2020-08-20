#pragma once
#include <iostream>
#include <string.h>
#include <vector>
#include <iomanip>
using namespace std;
class Member
{
private:
	string m_id;
	string m_name;
	string m_phone;
	bool m_check;
	int m_money;
	string m_etc;

public:
	bool operator<(const Member& mem) {//�������̵� ��ȯ���� bool, sorting���� ����
		return (m_id < mem.m_id);
	}	
	bool operator==(const Member& mem) {//�˻�
		return m_name == mem.m_name;
	}
	Member(vector<string> member);
	string getId() { return m_id; };
	string getName() { return m_name; };
	string getPhone() { return m_phone; };
	bool getCheck() { return m_check; };
	int getMoney() { return m_money; };
	string getEtc() { return m_etc; };
	void showMem(int a);
	~Member();
};