#include "Base.h"

#define INDEX 10;
#define N 100;


class Ex4 : public Base
{
public:
	Ex4();
	~Ex4();

	int count;
	int size = 0;

	unsigned long doParralel(int cpuCount, int n);
	unsigned long doSingle(int n);
	unsigned long writeData(int n, byte toLog);

};


