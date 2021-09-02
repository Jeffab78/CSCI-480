#ifndef PROCINFO_H
#define PROCINFO_H

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

class procInfo
{
	private:
	int physSize;
	int virtSize;
	int ratio;
	int cacheKB;
	int cacheBytes;
	bool fpu = false;

	public:
	procInfo(string x);
	int getPhysSize() const;
	int getVirtSize() const;
	int getRatio();
	int getCacheKB() const;
	int getCacheBytes();
	bool getFpu();
	
};








#endif
