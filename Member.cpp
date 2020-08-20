#include "Member.h"


Member::~Member()
{
}

void Member::showMem(int a) {
	const char* id = m_id.c_str();
	const char* name = m_name.c_str();
	const char* phone = m_phone.c_str();
	const char* etc = m_etc.c_str();
	cout << setw(10) << id << setw(a + 1) << name << setw(12) << phone;//setw에서 +1은 항목 사이 공백을 만들기 위해, a=이름최대길이
	cout << setw(8);
	if (m_check)
		cout << " O";
	else
		cout << " X";
	if (m_money == -1)//납부금액이 공백인 경우 flag를 -1롤 설정해서 아래 출력에 '원'을 붙이지 않는다.
		cout << setw(12) << "" << setw(2) << "";
	else
		cout << setw(12) << m_money << setw(2) << "원";
	cout << setw(30) << etc << endl;
	//돈 빈칸이면 원 안 적기
}

Member::Member(vector<string> member) 
{
	m_id=member.at(0);
	m_name=member.at(1);
	m_phone= member.at(2);
	m_check = true;
	if (member.at(4) == " ")
		m_money = -1;
	else
		m_money = atoi(member.at(4).c_str());

	if (m_money == -1)
		m_check = false;//공백으로 놔둘 시 납부 금액이 없는 것으로 간주

	m_etc= member.at(5);
}