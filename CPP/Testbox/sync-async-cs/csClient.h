#pragma once

#include <string>

/*

������������� ������.
���������� ����������, �������� ������. ��.

*/

class csClient
{
private:
	csClient(void){};
public:
	csClient(std::string& server, std::string& port);
	virtual ~csClient(void);
};

