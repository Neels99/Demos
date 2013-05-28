// RemoteCall.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"

#include <string>
#include <iostream>
#include <sstream>
#include "windows.h"

using namespace std;

/*
������ ������-��������� ������ 

"������ 1" ���������� ������ �� ���������� �������� ��������� (� ��������)
"������ 2" �������� ������ �� ���������� �������� ��������� (�� ��������) � ���������� ���������
*/

string stub(string& in);

/*���������� ����������: ��������� �������� ������
������� "r" � �������� ������� - ������ "���������" ����������
*/
class cClient
{
private:
	/* ��-��������, ��� ���� ���� �� ������������ ���-�� ����� xml-������������ ��� �������� ������������ */	
	string extTrigReq(string funcName, double param) // �������� ����� ������������������ �������
	{		
		stringstream ss (stringstream::in | stringstream::out);
		ss << param;

		string send("");
		send.append(funcName);
		send.append("\r\n");
		send.append(ss.str());
		send.append("\r\n");
		return stub(send);
	}

	string extCoordReq(string funcName, int param1, int param2)
	{
		stringstream ss (stringstream::in | stringstream::out);		

		string send("");
		send.append(funcName);
		send.append("\r\n");
		ss << param1;
		send.append(ss.str());
		send.append("\r\n");
		ss.clear();
		ss<<param2;
		send.append(ss.str());
		send.append("\r\n");

		return stub(send);
	}

	// ���������� ������
	void exceptor(string& str)
	{
		if(str.compare(0,4,"Fx01") == 0) throw new exception("�������� �������� �������");
		if(str.compare(0,4,"Fx02") == 0) throw new exception("�������� ���������");		
		// ... ��� ����� ������� ����� ��������
		if(str.compare(0,4,"FxFF") == 0) throw new exception("������ �� ����� ���������� �������");		
	}

public:
	double rSin(double x)
	{
		string a = extTrigReq("sin",x);		
		exceptor(a);// ���������: ���� ����� ������ - ������ �������������� ��������
		return atof(a.c_str());
	}

	double rCos(double x)
	{
		string a = extTrigReq("cos",x);		
		exceptor(a);// ���������: ���� ����� ������ - ������ �������������� ��������
		return atof(a.c_str());
	}

	// �������, ������� ���������� �������� �������� ������
	void aprioryErrorFunc()
	{
		string a = extCoordReq("efunc",10,20);		
		exceptor(a);// ���������: ���� ����� ������ - ������ �������������� ��������
	}
};

/*��������� ����������: ������������ �������� ������ � ���������� �����*/
class cServer
{
private:
	double Sin(double x)
	{
		return sin(x);
	}
	double Cos(double x)
	{
		return cos(x);
	}
	// ��������� ��������� ������, ��������� �� � ���������� ������
	string AssignFunc(string& data)
	{
		/*
		1. �������� ������
		2. ���������� � �������� �������
		3. ���������� ������������ ����� ������ ����������
		4. ���������� �����
		5. ��� ���������� ������
		*/
		string answer("");
		try
		{
			string fParam("");			
			stringstream ss;
			fParam = data.substr(0,data.find("\r\n",0)); data.erase(0,data.find("\r\n",0)+2);

			if(fParam.compare(0,3,"sin") == 0)
			{
				if(fParam.length()<3) throw 2;
				fParam = data.substr(0,data.find("\r\n",0));				
				ss<<Sin(atof(fParam.data()));
				answer = ss.str();
			} else
	
			if(fParam.compare(0,3,"cos") == 0)
			{
				if(fParam.length()<3) throw 2;
				fParam = data.substr(0,data.find("\r\n",0));				
				ss<<Cos(atof(fParam.data()));
				answer = ss.str();
			} else

			if(fParam.compare(0,5,"efunc") == 0)
			{
				// ��� ������ �� �������������� - ������� �������� ��������				
				throw 100;
			} else
			// ����������� �������
			throw 1;
		}
		catch(int error)	// ���� ������
		{
			switch(error)
			{
			case 1: answer = "Fx01";break;// ����������� �������
			case 2: answer = "Fx02";break;// �������� � �����������
			
			case 100: answer = "FxFF"; break;	// �������� � ����������� �������
			}
		}
		catch(exception&) // ������ ��������
		{
			answer = "FxFF";
		}

		return answer;
	}

public:
	string Execute(string& inputData)
	{
		return AssignFunc(inputData);
	}
};


/* �������� - ��������������� */
string stub(string& in)
{
	cServer server;
	return server.Execute(in);
}


int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_CTYPE,"rus");

	cClient client;
	// ��������� "����������" �������
	cout<<client.rSin(0.5)<<endl;
	cout<<client.rCos(0.5)<<endl;

	// ��������� "������������" �������
	try
	{
		client.aprioryErrorFunc();
	} catch(exception* e)
	{
		cout<<e->what()<<endl;
	}

	
	cin.get();
	return 0;
}

