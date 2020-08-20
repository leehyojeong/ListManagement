#include "Member.h"


Member::~Member()
{
}

void Member::showMem(int a) {
	const char* id = m_id.c_str();
	const char* name = m_name.c_str();
	const char* phone = m_phone.c_str();
	const char* etc = m_etc.c_str();
	cout << setw(10) << id << setw(a + 1) << name << setw(12) << phone;//setw���� +1�� �׸� ���� ������ ����� ����, a=�̸��ִ����
	cout << setw(8);
	if (m_check)
		cout << " O";
	else
		cout << " X";
	if (m_money == -1)//���αݾ��� ������ ��� flag�� -1�� �����ؼ� �Ʒ� ��¿� '��'�� ������ �ʴ´�.
		cout << setw(12) << "" << setw(2) << "";
	else
		cout << setw(12) << m_money << setw(2) << "��";
	cout << setw(30) << etc << endl;
	//�� ��ĭ�̸� �� �� ����
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
		m_check = false;//�������� ���� �� ���� �ݾ��� ���� ������ ����

	m_etc= member.at(5);
}