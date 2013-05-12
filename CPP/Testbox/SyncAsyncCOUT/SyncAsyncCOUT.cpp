// SyncAsyncCOUT.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include <iostream>

using namespace std;

int cnt = 10;

void print1(const char* tparam)
{
	cout<<tparam<<"->"<<(--cnt)<<endl;
}


void print2()
{
	cout<<"Sync print"<<endl;
}

int _tmain(int argc, _TCHAR* argv[])
{
	setlocale (LC_CTYPE,"rus");

	// ������������� io
	boost::asio::io_service io;
	// �������������� "�������������" ������� � ������������ �������. � ����� ������ - ����� � �������
	boost::asio::strand st(io);
	// �������
	boost::asio::deadline_timer t1(io, boost::posix_time::seconds(1));
	boost::asio::deadline_timer t2(io, boost::posix_time::seconds(1));
	// ������������� ������� � ������
	// �������� ��������: ��������� ���������� ������� ������� ����� boost::bind, � st.wrap ������������ ������������� ������
	t1.async_wait( st.wrap( boost::bind(&print1,"timer1") ) );
	t2.async_wait( st.wrap( boost::bind(&print1,"timer2") ) );
	/*
		������ ����� �������� � ���� ���������� � ������� � ������ ��������� ����������, �� � �� ���� ��� ������ :-)
	*/

	// ������ ��������� � ������
	cout<<"Start async output"<<endl;
	// ����� ������; ��� ���� ������� ������� �� ���������
	io.run();


	// ������������ ����������� �������: ������ ����������� �������� ������� Sleep(), ������ �������
	boost::asio::deadline_timer t3(io, boost::posix_time::seconds(3));
	boost::system::error_code ec; //�������������� ��������, �������� ���� ������������: � ������ ������ ������� �� ��� ����� ���������
	t3.wait(ec); 
	cout<<ec.message().c_str()<<endl; 
	print2();

	cin.get();
	return 0;
}

