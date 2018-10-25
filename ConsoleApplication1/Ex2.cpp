#include "stdafx.h"
#include "Ex2.h"

using namespace std;

Ex2::Ex2()
{
	ExName = (char *) " zero select";
}
unsigned long Ex2::writeData(int n, byte toLog) {
	mass = mass2;
	unsigned long ret = Base::writeData(size, toLog);
	return ret;
}

unsigned long Ex2::doParralel(int cpuCount, int n) {
	float result = 0;
	cpuCount += 1;
	int chunk = n / cpuCount;
	float** masses = (float**)malloc(sizeof(float*)*cpuCount);
	int* massesCounts = (int*)malloc(sizeof(int)*cpuCount);
	auto start = chrono::high_resolution_clock::now();
#pragma omp parallel num_threads(cpuCount) shared(chunk)
	{
		int num_thr = omp_get_thread_num();
		float* masa = (float*)malloc(sizeof(float)*chunk);
		int count = 0;
		for (int i = chunk * num_thr; i < chunk*(num_thr + 1); i++)
		{
			if (mass[i] != 0.0f)
			{
				masa[count] = mass[i];
				count++;
			}
		}

		masses[num_thr] = masa;
		massesCounts[num_thr] = count;
	}

	int sizeSum = 0;
	for (int i = 0; i < cpuCount; i++) sizeSum += massesCounts[i];
	mass2 = (float*)malloc(sizeof(float)*sizeSum);
	size = 0;
#pragma omp parallel for schedule (static, 1) num_threads(cpuCount)
	for (int i = 0; i < cpuCount; i++) {
		int index = omp_get_thread_num(); // выбираем нужный массив
		int startFrom = 0;

		// определяем начало своей части массива
		for (int z = 0; z < index; z++) startFrom += massesCounts[z];

		int currentCount = massesCounts[index]; // определяем, сколько элементов нужно записать
		for (int j = 0; j < currentCount; j++) {
			mass2[startFrom + j] = masses[index][j]; // в итоге каждый из потоков
													//	пишет в свою часть массива 
		}
	}
	auto finish = chrono::high_resolution_clock::now();
	unsigned long duration = chrono::duration_cast<chrono::nanoseconds>(finish - start).count();
	return duration;
}

unsigned long Ex2::doSingle(int n)
{
	int i, chunk;
	float result = 0;

	int mSize = 0;
	
	readData(n, false);

	auto start = chrono::high_resolution_clock::now();

	singleMass = (float*)malloc(sizeof(float)*n);

	for (int i = 0; i < n; i++)
	{
		if (mass[i] != 0.0f)
		{
			singleMass[mSize] = mass[i];
			mSize++;
		}

	}

	auto finish = chrono::high_resolution_clock::now();
	long duration = chrono::duration_cast<chrono::nanoseconds>(finish - start).count();
	return duration;
}

Ex2::~Ex2()
{
}
