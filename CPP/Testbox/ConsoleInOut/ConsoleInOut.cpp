// ConsoleInOut.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"
#include <iostream>

using namespace std;

/*
-l <login, string> -p <password, string> -to <timeout, int> -fm <mappedfile, string>
*/

/*
- ������������� ��������� ������������
- ����������� ��������� ������������
- ��������� ���� ������ ������
- ��������� ���������� �� ����� "-"
- ������� �������������� ���������� ����� �������� ��-���������
- ������� ������������ ���������� ���������� ������ - ������� � �������
- ���� ����� ����� ��������� ��� ������ ���� ��������� - ������ ������������
*/

/*
- �������� ����������� �� ���������������� (��� int)
- 
*/

// ������ ������������
string login("");
string password("");
int timeout(100);
string mapfile("");


int _tmain(int argc, _TCHAR* argv[])
{
	setlocale (LC_CTYPE,"rus");

	bool isKey = false;
	string keyName("");
	string keyValue("");

	// ������������ ����������
	for(int cnt = 1; cnt<argc;cnt++)
	{		
		isKey = strlen(argv[cnt])>0 && argv[cnt][0] == '-' ? true : false;		
		if(isKey) 
		{
			keyName.clear();// �� ������, ���� ���� ���������������
			keyName.append(argv[cnt],1,strlen(argv[cnt])-1);
		} else {keyValue.append(argv[cnt]);}
		if(keyName.length()>0 && keyValue.length()>0)
		{

			if(strcmp(keyName.c_str(),"l") == 0)		{login		= keyValue;}
			if(strcmp(keyName.c_str(),"p") == 0)		{password	= keyValue;}
			if(strcmp(keyName.c_str(),"fm") == 0)		{mapfile	= keyValue;}
			if(strcmp(keyName.c_str(),"to") == 0)		{timeout	= atoi(keyValue.c_str());}

			//cout<<"��������="<<keyName.c_str()<<", ��������="<<keyValue.c_str()<<endl;
			keyName.clear();
			keyValue.clear();
		}
						
	}

	// �������� �� ������������� ����� ��������� �������
	if(login.length()<1 || password.length()<1 || mapfile.length()<1)
	{
		cout<<"�� ������� ���������� ��� ���������� ��������� �������"<<endl;
	} else
	{
		cout<<"��������� �������: ������� ������ "<<login.c_str()<<", ������ "<<password.c_str()<<". ����, ������������ � ������: "<<mapfile.c_str()<<". ������������� ����� �������� "<<timeout<<"."<<endl;
	}

	cin.get();
	return 0;
}

