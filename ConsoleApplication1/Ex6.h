#pragma once
#include "Base.h"

#define VECTOR {1,2,3,4,5,6,7,8,9};
#define VECTOR_LENGTH 9


class Ex6 : public Base
{
public:
	Ex6();
	~Ex6();

	float* mass2;
	int size;

	unsigned long doParralel(int cpuCount, int n);
	unsigned long doSingle(int n);
	unsigned long writeData(int n, byte toLog);

};


