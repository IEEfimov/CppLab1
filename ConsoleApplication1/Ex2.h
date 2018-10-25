#include "Base.h"

class Ex2 : public Base
{
public:
	Ex2();
	~Ex2();

	float* mass2;
	int size = 0;


	unsigned long doParralel(int cpuCount, int n);
	unsigned long doSingle(int n);
	unsigned long writeData(int n, byte toLog);

};


