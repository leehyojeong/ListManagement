#include "Manager.h"
#include "Member.h"
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
using namespace std;

Manager::Manager()
	:menu(true), nameLength(0),errCheck(false)

{
}

Manager::~Manager()
{
}
void Manager::menuInfo() {
	cout << "장부 관리 프로그램" << endl;
	cout << "   1. 전체" << endl;
	cout << "   2. 정렬" << endl;
	cout << "   3. 검색" << endl;
	cout << "   4. 종료" << endl;
}

void Manager::showMenu()
{
	menuInfo();
	y = 1;	//0으로 설정되어 있던 커서의 y좌표를 1로 옮김
	gotoxy(x, y);
	cout << "→";
	while (menu) {
		system("cls");
		menuInfo();
		gotoxy(0, y);
		cout << "→";
		switch (getch()) {
		case 13:
			system("cls");
			switch (y) {
			case 1:
				menu1_show();
				break;
			case 2:
				if (errCheck)
					break;
				else
					menu2_sort();
				break;
			case 3:
				if (errCheck)
					break;
				else
					menu3_search();
				break;
			case 4:
				menu4_exit();
				break;
			}
			break;
		case 72:
			if (y == 1)
				break;
			else {
				y--;
				break;
			}
		case 80:
			if (y == 4)
				break;
			else {
				y++;
				break;
			}
		default:
			break;
		}
		gotoxy(0, y);
	}
}
void Manager::openFile()
{
	bool checkFile = false;
	string filePath = "test.txt";
	// read File
	ifstream openFile(filePath.data()); // text file open
	if (openFile.is_open()) { // 정상
		string line;
		int count_line = 0;
		while (getline(openFile, line)) {
			if (!checkFile)
				checkFile = true;
			count_line++;
			//cout << line << endl;
			stringSplit(line);
			if (correctCheck()) {//오류 없음
				w_people++;
				if (m_sav.at(3) == "O" || m_sav.at(3) == "o") {//납부여부
					nen_people++;
					w_money += stoi(m_sav.at(4));
				}
				m_org.push_back(m_sav);
			}
			else {
				m_err.push_back(count_line);
				errCheck = true;
			}
			m_sav.clear();
			//오류 있는지 판단하는 함수 추가후
		}
		openFile.close();

		if (!checkFile) {
			cout << "파일이 비어있습니다" << endl;
			return;
		}

		//m_sort 정렬해놓기 - sort();

		sorting();
		showMenu();
	}
}

void Manager::keyDownESC()
{
	while (1) {
		if (kbhit())
		{
			switch (getch()) {
			case 27:
				system("cls");
				showMenu();
				return;
			}
		}
	}
}

bool Manager::IsKorean(char ch)
{

	//(한글자||자음,모음)
	if ((0xAC00 <= ch && ch <= 0xD7A3) || (0x3131 <= ch && ch <= 0x318E))
		return true;
	else
		return false;

}
bool Manager::correctCheck() {

	bool checkValue = true; // 여과망 걸러지듯이 다통과해야 true

	// 학번 예외처리
	if (m_sav.at(0).size() != ID_LENGTH_MAX && checkValue)
		checkValue = false;
	for (int i = 0; i < m_sav.at(0).size(); i++) {
		if ((m_sav.at(0).at(i) < 0 || m_sav.at(0).at(i)) > 9 && checkValue)
			checkValue = false;
		else if (!checkValue) break;
	}
	 
	// 이름 예외처리
	for (int i = 0; i < m_sav.at(1).size(); i++) {
		if (nameLength < m_sav.at(1).size())
			nameLength = m_sav.at(1).size();
		if (m_sav.at(1).at(i) == ' ' && checkValue)
			checkValue = false;
		else if (!checkValue) break;
		if ((m_sav.at(1).at(i) >= 33 && m_sav.at(1).at(i) <= 47) ||
			(m_sav.at(1).at(i) >= 58 && m_sav.at(1).at(i) <= 64) ||
			(m_sav.at(1).at(i) >= 91 && m_sav.at(1).at(i) <= 96) ||
			(m_sav.at(1).at(i) >= 123 && m_sav.at(1).at(i) <= 126)) {
			checkValue = false;
			break;
		}
	}

	// 전화번호 예외처리
	if (m_sav.at(2).size() != PHONE_LENGTH_MAX && checkValue)
		checkValue = false;
	for (int i = 0; i < m_sav.at(2).size(); i++) {
		if ((m_sav.at(2).at(i) < '0' || m_sav.at(2).at(i)) > '9' && checkValue)
			checkValue = false;
		else if (!checkValue) break;
	}

	// 납부여부 예외처리
	if (!(m_sav.at(3) == "O" || m_sav.at(3) == "o" || m_sav.at(3) == "x" || m_sav.at(3) == "X") && checkValue)
		checkValue = false;

	// 금액 예외처리
	for (int i = 0; i < m_sav.at(4).size(); i++) {
		if (m_sav.at(4).at(i) == ' ')
			continue;
		if (m_sav.at(4).at(i) < '0' || m_sav.at(4).at(i) > '9' && checkValue)
			checkValue = false;
		else if (!checkValue) break;
	}

	// 비고 예외처리
	if (m_sav.at(5).size() > ETC_LENGTH_MAX || m_sav.at(5).size() < 0 && checkValue)
		checkValue = false;

	return checkValue;
}

void Manager::stringSplit(string line) {

	char delimiters = '$';

	char* temp = new char[line.size() + 1];
	strcpy(temp, line.c_str()); // string -> char* 전환
	int count = 0;
	int savIndex = 0;
	for (int i = 0; i < line.size() + 1; i++) {
		if (m_sav.size() == 5) {
			m_sav.push_back(line.substr(savIndex));
			break;
		}

		if (temp[i] != delimiters) {
			if (temp[i] == NULL)
				m_sav.push_back(line.substr(savIndex, count));
			count++;
		}
		else {
			if (count == 0)
				m_sav.push_back(" ");
			else
				m_sav.push_back(line.substr(savIndex, count));
			savIndex = i + 1;
			count = 0;
		}
	}
	delete temp;
}
void Manager::Info() {
	cout << "파일 이름 : test.txt" << endl;
	cout << "총 인원수:" << w_people << "명, " << "납부한 사람 수:" << nen_people << "명, " << "합계금액:" << w_money << "원" << endl;
	cout << setw(10) << "학번" << setw(nameLength + 1) << "이름" <<
		setw(12) << "전화번호" << setw(12) << " 납부여부" <<
		setw(9) << "금액" << setw(17) << "비고" << endl;
}
void Manager::menu1_show()
{
	cout << "파일 불러오기에 성공했습니다." << endl;
	for (int i = 0; i < m_err.size(); i++) {
		cout << "파일의 " << m_err.at(i) << "번째 줄에서 오류가 발생하였습니다." << endl;
	}
	Sleep(3000);//첫번째 줄에  기본 정보 (제목) 출력하기위해 화면을 지우고 다시 쓴다.

	system("cls");
	gotoxy(0, 0);
	Info();
	for (int i = 0; i < m_org.size(); i++) {
		m_org.at(i).showMem(nameLength);
	}
	keyDownESC();
}

void Manager::menu2_sort()
{
	Info();
	for (int i = 0; i < m_sort.size(); i++) {
		if (!m_sort.at(i).getCheck())
			m_sort.at(i).showMem(nameLength);//안낸사람
	}
	for (int i = 0; i < m_sort.size(); i++) {//낸사람
		if (m_sort.at(i).getCheck())
			m_sort.at(i).showMem(nameLength);
	}
	keyDownESC();
}
void Manager::menu3_search()
{
	bool flag = true;
	if (flag) {
		string name;
		cin >> name;
		for (int i = 0; i < m_sort.size(); i++) {
			if (m_sort.at(i).getName() == name)
				m_sort.at(i).showMem(nameLength);// 출력형식
		}
		flag = false;
	}
	keyDownESC();

}
void Manager::menu4_exit()
{
	system("cls");
	cout << "종료하시겠습니까?(y/Y)" << endl;

	while (1) {
		getch();
		char ch = getche();
		if (ch == 'y' || ch == 'Y') {
			menu = false;
			return;
		}
		else return;
	}
}
void Manager::sorting()
{
	for (int i = 0; i < m_org.size(); i++) {
		m_sort.push_back(m_org.at(i));
	}

	sort(m_sort.begin(), m_sort.end());
}

void Manager::gotoxy(int x, int y)
{
	COORD Cur = { x,y };

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}

void Manager::whenExit()
{
	while (1) {
		if (getch() == 27) {
			gotoxy(0, y);
			char ans;
			cout << "메뉴로 돌아가시겠습니까(Y/N)?";
			cin >> ans;

			if (ans == 'Y') {
				cout << "메뉴로 돌아가는중..." << endl;
				Sleep(2000);
				system("cls");
				showMenu();
			}

			else if (ans == 'N') {
				system("cls");
				switch (y) {
				case 1:
					menu1_show();
					break;
				case 2:
					menu2_sort();
					break;
				case 3:
					menu3_search();
					break;
				case 4:
					menu4_exit();
					break;
				}
				break;
			}

			else {
				//gotoxy(0, y);
				cout << "잘못된 입력입니다.";
				break;
			}
		}
	}
}