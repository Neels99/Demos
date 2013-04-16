#pragma once

#include "cThreadPool.h"

// генерирует случайные задания и отдаёт их в пул потоков
class cTaskGenerator
{
	cThreadPool* ctpool;	// пул потоков

public:
	cTaskGenerator(void);
	~cTaskGenerator(void);

	void GeterateTask(int count = 1); // генерация заданного количества произвольных задач
	// добавить функцию принудительной остановки всех потоков	
};

