#pragma once

#include "cThreadPool.h"

// ���������� ��������� ������� � ����� �� � ��� �������
class cTaskGenerator
{
	cThreadPool* ctpool;	// ��� �������

public:
	cTaskGenerator(void);
	~cTaskGenerator(void);

	void GeterateTask(int count = 1); // ��������� ��������� ���������� ������������ �����
	// �������� ������� �������������� ��������� ���� �������	
};

