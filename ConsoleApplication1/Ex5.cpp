#include "stdafx.h"
#include "Ex5.h"

using namespace std;


Ex5::Ex5()
{
	ExName = (char *) " average";
}

unsigned long Ex5::writeData(int n, byte toLog) {
	mass = mass2;
	unsigned long ret = Base::writeData(size, toLog);
	return ret;
}
unsigned long Ex5::doParralel(int cpuCount, int n) {
	int i;
	int mySize = NUM;
	mass2 = (float*)malloc(sizeof(float)*n / mySize);
	cpuCount += 1;
	auto start = chrono::high_resolution_clock::now();

	//#pragma omp parallel private(i) shared(mySize, chunk) num_threads(cpuCount)

	int chunk = NUM;

#pragma omp parallel for schedule(static, chunk) num_threads(cpuCount)
	for (int i = 0; i < n / mySize; i++)
	{
		float temp = 0;
		for (int j = 0; j < mySize; j++) {
			temp += mass[i*mySize + j];
		}
		mass2[i] = temp / mySize;
	}
	size = n / mySize;
	auto finish = chrono::high_resolution_clock::now();
	unsigned long duration = chrono::duration_cast<chrono::nanoseconds>(finish - start).count();
	return duration;
}

unsigned long Ex5::doSingle(int n)
{
	int i;
	int mySize = NUM;
	mass2 = (float*)malloc(sizeof(float)*n / mySize);

	auto start = chrono::high_resolution_clock::now();

	for (int i = 0; i < n / mySize; i++)
	{
		float temp = 0;
		for (int j = 0; j < mySize; j++) {
			temp += mass[i*mySize + j];
		}
		mass2[i] = temp / mySize;
	}

	size = n / mySize;
	singleSize = size;
	auto finish = chrono::high_resolution_clock::now();
	long duration = chrono::duration_cast<chrono::nanoseconds>(finish - start).count();

	return duration;
}



Ex5::~Ex5()
{
}
