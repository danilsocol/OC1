
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <stdlib.h> 
#include "OC1.h"

using namespace std;


typedef struct _Anketa
{
	char name[50];
	int age;
} Anketa;

void Viewing()
{
	Anketa anketa;
	DWORD bytes;
	HANDLE hFile;
	hFile = CreateFile(L"Text.dat", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	SetFilePointer(hFile, sizeof(Anketa), 0, FILE_BEGIN);
	ReadFile(hFile, &anketa, sizeof(Anketa), &bytes, NULL);
	CloseHandle(hFile);
	printf("%d \n", anketa.age);
}

void Editing()
{



}

void AddNew()
{
	DWORD bytes;
	HANDLE hFile;
	hFile = CreateFile(L"Text.dat", GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	cout << "Создайте сво анкету" << endl;
	Anketa newAnketa;
	cout << "Введите свое имя" << endl;
	cin >> newAnketa.name;
	cout << "Введите свой возраст" << endl;
	cin >> newAnketa.age;

	WriteFile(hFile, &newAnketa, sizeof(Anketa), &bytes, NULL);
	CloseHandle(hFile);

}


int main()
{
	setlocale(LC_ALL, "Russian");

	while (true)
	{
		/*HANDLE hFile;
		hFile = CreateFile(L"Text.dat", GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);*/

		char num;
		cout << "Выберете действие 1 - Просмотр анкеты, 2 - Редактирование анкеты, 3 - Добавление новой анкеты" << endl;
		cin >> num;
		if (num == '1')
			Viewing();
		else if (num == '2')
			Editing();
		else if (num == '3')
			AddNew();
	}


}