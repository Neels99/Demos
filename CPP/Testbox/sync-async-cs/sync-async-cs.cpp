// sync-async-cs.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"
#include <iostream>
#include <string>

#include "csasServer.h"
#include "csClient.h"

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_CTYPE,"rus");
	/*
		������������� ����������. ���������
		1. ������/������ = �/s
		2. ip = 127.0.0.1
		3. ���� = 555
		4. ����������/����������� s/a
	*/

	// ������������� ����������
	if(argc < 5) exit(0x010);
	bool serverMode;
	bool syncMode;

	bool testmode = false;

	string ip_("");
	string port_("");
	try
	{
		serverMode = argv[1][0] == 'c' ? false : true;
		syncMode =  argv[4][0] == 's' ? true : false;
		ip_ = argv[2];
		port_ = argv[3];
		// ����� �������
		if(argc>5) testmode = argv[5][0]=='t'?true:false;
	}
	catch(...)
	{
		exit(0x011);
	}
	
	if(serverMode) // ��������� ������
	{
		cout<<"������ �������: "<<(syncMode?"����������":"�����������")<<" ����� ("<<ip_.c_str()<<":"<<port_.c_str()<<")"<<endl;
		csasServer server(ip_.c_str(),port_.c_str(),syncMode);
	}else // ��������� �������
	{
		cout<<"������ �������"<<endl;
		csClient client(ip_,port_);
	}


	if(!testmode)cin.get();
	return 0;
}

