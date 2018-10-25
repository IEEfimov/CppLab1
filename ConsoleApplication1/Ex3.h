#pragma once
#include "Base.h"

#define VALUE_MIN 2.0f
#define VALUE_MAX 5.0f


class Ex3 : public Base
{
public:
	Ex3();
	~Ex3();

	float* mass2;
	int size;

	unsigned long doParralel(int cpuCount, int n);
	unsigned long doSingle(int n);
	unsigned long writeData(int n, byte toLog);

	
};


