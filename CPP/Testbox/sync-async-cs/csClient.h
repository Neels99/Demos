#pragma once

#include <string>

/*

Универсальный клиент.
Отправляет информацию, получает отклик. Всё.

*/

class csClient
{
private:
	csClient(void){};
public:
	csClient(std::string& server, std::string& port);
	virtual ~csClient(void);
};

