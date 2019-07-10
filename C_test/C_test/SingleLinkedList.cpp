#include "pch.h"
#include <iostream>

using namespace std;

enum MAIN_MENU
{
	MM_NONE,
	MM_INSERT,
	MM_DELETE,
	MM_SEARCH,
	MM_OUTPUT,
	MM_EXIT
};



#define NAME_SIZE 32

typedef struct _tagStudent
{
	char strName[NAME_SIZE];
	int iNumber;
	int iKor;
	int iEng;
	int iMath;
	int iTotal;
	int fAvg;
}STUDENT, *PSTUDENT;

typedef struct _tagNode
{
	STUDENT tStudent;
	_tagNode* pNext;
}NODE, *PNODE;

typedef struct _tagList
{
	PNODE pBegin;
	PNODE pEnd;
	int iSize;
}LIST, * PLIST;

int InputInt() {
	int iInput;
	cin >> iInput;
	if (cin.fail()) {
		cin.clear();
		cin.ignore(1024, '\n');
		return INT_MAX;
	}

	return iInput;
}

void InitList(PLIST pList) {
	pList->pBegin = NULL;
	pList->pEnd = NULL;
	pList->iSize = 0;
}

int OutputMenu() {
	system("cls");
	cout << "1. 학생추가" << endl;
	cout << "2. 학생삭제" << endl;
	cout << "3. 학생수정" << endl;
	cout << "4. 학생조회" << endl;
	cout << "5. 종료" << endl;
	cout << "메뉴를 선택하세요 : ";
	int iInput = InputInt();

	if (iInput <= MM_NONE || iInput > MM_EXIT)
		return MM_NONE;

	return iInput;
}

void InputString(char* pString, int iSize) {
	cin.clear();
	cin.ignore(1024, '\n');
	cin.getline(pString, iSize - 1);

}

void Insert(PLIST pList) {

	system("cls");
	cout << "=========== 학생추가 ==============" << endl;

	STUDENT tStudent = {};

	cout << "이름 : ";
	InputString(tStudent.strName, NAME_SIZE);

	cout << "학번 : ";
	tStudent.iNumber = InputInt();

	cout << "국어 : ";
	tStudent.iKor = InputInt(); 

	cout << "영어 : ";
	tStudent.iEng = InputInt();

	cout << "수학 : ";
	tStudent.iMath = InputInt();

	tStudent.iTotal = tStudent.iKor + tStudent.iEng + tStudent.iMath;
	tStudent.fAvg = tStudent.iTotal / 3.f;

	PNODE pNode = new NODE;

	pNode->pNext = NULL;
	pNode->tStudent = tStudent;

	if (pList->pBegin == NULL) {
		pList->pBegin = pNode;
	}
	else {
		pList->pEnd->pNext = pNode;
	}

	pList->pEnd = pNode;

	++pList->iSize;
}

void ClearList(PLIST pList) {

	PNODE pNode = pList->pBegin;

	while (pNode != NULL)
	{
		PNODE pNext = pNode->pNext;
		delete pNode;
		pNode = pNext;
	}

	pList->pBegin = NULL;
	pList->pEnd = NULL;
	pList->iSize = 0;

}

void OutputStudent(const PSTUDENT pStudent) {

	cout << "이름 : " << pStudent->strName << "\t학번 : " << pStudent->iNumber << endl;
	cout << "국어 : " << pStudent->iKor << "\t영어 : " << pStudent->iEng << endl;
	cout << "수학 : " << pStudent->iMath << endl;
	cout << "총점 : " << pStudent->iTotal << "\t평균 : " << pStudent->fAvg << endl;
}


void Output(PLIST pList) {

	system("cls");
	cout << "=========== 학생출력 ==============" << endl;

	PNODE pNode = pList->pBegin;


	//데이터가 생성 되면 무조건 노드는 널이 아니고 
	//마지막 데이터는 널이기에 마지막 까지 돈다 
	while (pNode != NULL)
	{
		OutputStudent(&pNode->tStudent);
		pNode = pNode->pNext;
	}

	cout << "학생수 : " << pList->iSize << endl;

	system("pause");
}

int main()
{
	LIST tList;
	InitList(&tList);

	while (true)
	{
		int iMenu = OutputMenu();

		if (iMenu == MM_EXIT) {
			break;
		}

		switch (iMenu)
		{
		case MM_INSERT:
			Insert(&tList);
			break;
		case MM_DELETE:
			break;
		case MM_SEARCH:
			break;
		case MM_OUTPUT:
			Output(&tList);
			break;
		case MM_EXIT:
			break;

		default:
			break;
		}

		
	}

	ClearList(&tList);
	return 0;
}