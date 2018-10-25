#include "stdafx.h"
#include "Ex4.h"

using namespace std;

TCHAR szPath4[] = TEXT("ChartView.exe"); // Путь к файлу
										 // Необходимые для запуска процесса структуры

Ex4::Ex4()
{
	ExName = (char *) " index count";
}

unsigned long Ex4::writeData(int n, byte toLog) {
	FILE *f;
	/*string fileName = FOLDER_NAME;
	if (CreateDirectory(fileName.c_str() , NULL) ||
	ERROR_ALREADY_EXISTS == GetLastError())
	{

	}
	else return -1;*/


	string fileName = "output_";
	fileName.append(to_string(n));
	fileName.append(".bin");
	if (toLog) printf_s("Starting to write the file %s... ", fileName.c_str());
	auto start = chrono::high_resolution_clock::now();
	int err = fopen_s(&f, fileName.c_str(), "wb");
	if (err == 0) {
		fprintf_s(f, "%d ", count);
		fclose(f);
	}
	auto finish = chrono::high_resolution_clock::now();
	unsigned long duration = chrono::duration_cast<chrono::nanoseconds>(finish - start).count();
	if (toLog) printf_s(" Done in %dms \n", duration);
	return duration;
}

unsigned long Ex4::doParralel(int cpuCount, int n) {
	int i;
	int result = 0;
	cpuCount += 1;
	int rows = N;
	int index = INDEX;
	auto start = chrono::high_resolution_clock::now();


#pragma omp parallel for schedule(runtime) reduction(+:result) num_threads(cpuCount) shared (rows)
	for (int i = 0; i < n / rows; i++)
	{
		if (mass[i*rows + index] == 0.0f)
		{
			result++;
		}
	}
	auto finish = chrono::high_resolution_clock::now();
	unsigned long duration = chrono::duration_cast<chrono::nanoseconds>(finish - start).count();
	count = result;
	return duration;
}

unsigned long Ex4::doSingle(int n)
{
	int i;
	int result = 0;
	int rows = N;
	int index = INDEX;
	auto start = chrono::high_resolution_clock::now();

	for (int i = 0; i < n / rows; i++)
	{
		if (mass[i*rows + index] == 0.0f)
		{
			result++;
		}
	}
	singleSize = 1;
	auto finish = chrono::high_resolution_clock::now();
	unsigned long duration = chrono::duration_cast<chrono::nanoseconds>(finish - start).count();
	count = result;
	return duration;
}

Ex4::~Ex4()
{
}
