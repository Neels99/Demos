#include "StdAfx.h"
#include "protector.h"
#include <iostream>

using namespace std;


protector::protector(void)
{
	setlocale(LC_CTYPE,"rus");
	cout<<"������ ������"<<endl;
}


protector::~protector(void)
{
	cout<<"������ ��������"<<endl;
}
