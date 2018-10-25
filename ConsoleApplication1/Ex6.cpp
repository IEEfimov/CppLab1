#include "stdafx.h"
#include "Ex6.h"

using namespace std;


Ex6::Ex6()
{
	ExName = (char *) " zero select";
}

unsigned long Ex6::writeData(int n, byte toLog) {
	mass = mass2;
	unsigned long ret = Base::writeData(size, toLog);
	return ret;
}

unsigned long Ex6::doParralel(int cpuCount, int n) {
	int i;
	int mySize = VECTOR_LENGTH;
	float vector[VECTOR_LENGTH] = VECTOR;
	cpuCount++;
	mass2 = (float*)malloc(sizeof(float)*n / mySize);
	auto start = chrono::high_resolution_clock::now();

#pragma omp parallel for schedule(runtime) num_threads(cpuCount)
	for (int i = 0; i < n / mySize; i++)
	{
		float temp = 0;
		for (int j = 0; j < mySize; j++) {
			temp += mass[i*mySize + j] * vector[j];
		}
		mass2[i] = temp;
	}
	size = n / mySize;
	auto finish = chrono::high_resolution_clock::now();
	unsigned long duration = chrono::duration_cast<chrono::nanoseconds>(finish - start).count();
	return duration;
}

unsigned long Ex6::doSingle(int n)
{
	int i;
	int mySize = VECTOR_LENGTH;
	float vector[VECTOR_LENGTH] = VECTOR;
	mass2 = (float*)malloc(sizeof(float)*n / mySize);
	auto start = chrono::high_resolution_clock::now();

	for (int i = 0; i < n / mySize; i++)
	{
		float temp = 0;
		for (int j = 0; j < mySize; j++) {
			temp += mass[i*mySize + j] * vector[j];
		}
		mass2[i] = temp;
	}
	size = n / mySize;
	singleSize = size;
	auto finish = chrono::high_resolution_clock::now();
	unsigned long duration = chrono::duration_cast<chrono::nanoseconds>(finish - start).count();
	return duration;
}

Ex6::~Ex6()
{
}
