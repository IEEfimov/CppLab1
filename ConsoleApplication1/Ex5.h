#pragma once
#include "Base.h"

#define NUM 2;

class Ex5 : public Base
{
public:
	Ex5();
	~Ex5();

	float* mass2;
	int size;

	unsigned long doParralel(int cpuCount, int n);
	unsigned long doSingle(int n);
	unsigned long writeData(int n, byte toLog);
};


