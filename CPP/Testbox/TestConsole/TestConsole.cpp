// TestConsole.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"
#include <iostream>
#include "windows.h"
int _tmain(int argc, _TCHAR* argv[])
{
	setlocale (LC_CTYPE,"rus");
	int i = 10, p_pSrcBuf = 100;
	UINT32 x = 0;//( *( p_pSrcBuf + i ) );
	
	std::cout<<(( x ));
	std::cout<<"������ �������� ���� ������"<<std::endl;
	std::cin.get();
	return 0;
}

