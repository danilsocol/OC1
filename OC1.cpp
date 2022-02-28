
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <stdlib.h> 
#include "OC1.h"
#include <string>
#include <string>

using namespace std;


typedef struct _Anketa
{
	char name[50];
	int age;
} Anketa;

HANDLE openFile(LPCWSTR nameOfFile) {
	HANDLE file = CreateFile(
		nameOfFile,
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ,
		NULL,
		OPEN_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);
	return file;
}

DWORD writeFile(HANDLE file, char* data, int size) {
	DWORD bytesWritten;
	WriteFile(
		file,
		data,
		size,
		&bytesWritten,
		NULL);
	return bytesWritten;
}

Anketa readFile(HANDLE file, int size) {
	Anketa data;
	DWORD bytesWritten;
	ReadFile(file,
		&data,
		size,
		&bytesWritten,
		NULL);
	return 	data;
}

void lockFile(HANDLE file, int start, int size, int access) {
	OVERLAPPED ol;
	ol.OffsetHigh = 0;
	ol.Offset = start;
	ol.hEvent = NULL;
	LockFileEx(file, access, 0, size, 0, &ol);
}

void writeProfileInFileAdd(HANDLE file, Anketa profile) {
	SetFilePointer(file, 0, 0, FILE_END);
	writeFile(file, (char*)&profile, sizeof(profile));
}

void writeProfileInFileEditing(HANDLE file, Anketa profile,int num) {
	SetFilePointer(file, sizeof(Anketa) * (num - 1), 0, FILE_BEGIN);
	writeFile(file, (char*)&profile, sizeof(profile));
}

Anketa readProfile(HANDLE file, int numOfResume) {
	int startPoint = sizeof(Anketa) * (numOfResume - 1);
	SetFilePointer(file, sizeof(Anketa) * (numOfResume - 1), 0, FILE_BEGIN);
	lockFile(file, startPoint, sizeof(Anketa), 0);
	return readFile(file, sizeof(Anketa));
}

void writeProfile(Anketa profile) {
	printf("%d\n", profile.age);
	printf("%s\n", profile.name);
}

void AddNew(HANDLE file)
{

	cout << "Create your profile" << endl;
	Anketa newAnketa;
	cout << "Enter your name" << endl;
	cin >> newAnketa.name;
	cout << "Enter your age" << endl;
	cin >> newAnketa.age;

	writeProfileInFileAdd(file, newAnketa);
}

void Viewing(HANDLE file)
{
	int num;
	cout << "Select the questionnaire number" << endl;
	cin >> num;

	Anketa profile = readProfile(file, num);
	writeProfile(profile);
}

void Editing(HANDLE file)
{
	int num;
	cout << "Select the questionnaire number to edit" << endl;
	cin >> num;

	int startPoint = sizeof(Anketa) * (num - 1);
	lockFile(file, startPoint, sizeof(Anketa), LOCKFILE_EXCLUSIVE_LOCK);

	cout << "Editing your profile" << endl;
	Anketa newAnketa;
	cout << "Enter your name" << endl;
	cin >> newAnketa.name;
	cout << "Enter your age" << endl;
	cin >> newAnketa.age;

	SetFilePointer(file, startPoint, 0, FILE_BEGIN);
	writeFile(file, (char*)&newAnketa, sizeof(newAnketa));
}

int main()
{

	while (true)
	{
		HANDLE file;
		// hFile = CreateFile(L"Text.dat", GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		LPCWSTR path = L"C:\\Users\\Seraphic\\Desktop\\test.bin";
		char num;
		file = openFile(path);

		cout << "Select action 1 - Viewing the questionnaire, 2 - Editing the questionnaire, 3 - Adding a new questionnaire" << endl;
		cin >> num;
		if (num == '1')
			Viewing(file);
		else if (num == '2')
			Editing(file);
		else if (num == '3')
			AddNew(file);

		CloseHandle(file);
	}


}