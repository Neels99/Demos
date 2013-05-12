#include "StdAfx.h"
#include "protector.h"
#include <iostream>

using namespace std;


protector::protector(void)
{
	setlocale(LC_CTYPE,"rus");
	cout<<"Объект создан"<<endl;
}


protector::~protector(void)
{
	cout<<"Объект разрушен"<<endl;
}
