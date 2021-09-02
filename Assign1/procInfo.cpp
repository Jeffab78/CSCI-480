/**********************************************
Assignment: 1
Zid: z1860060
Name: Jeff Byerly
Date: 1/29/2021
***********************************************/

#include "procInfo.h"

#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>

using namespace std;

procInfo::procInfo(string s)
{
	//temp string variables
	string tempSubStr;
	string tempCache;
	string tempPhysSize;
	string tempVirtSize;


	//uses temp to split for phys/virt addresses
	tempSubStr = s.substr((s.find("address sizes")+1),string::npos);
	tempPhysSize = tempSubStr.substr((tempSubStr.find(":")+1),((tempSubStr.find(","))-(tempSubStr.find(":"))));
	
	physSize = stoi(tempPhysSize);

	tempVirtSize = tempSubStr.substr((tempSubStr.find(",")+1),string::npos);

	virtSize = stoi(tempVirtSize);

	//splits string for cache size
	tempSubStr = s.substr((s.find("cache size")+1),string::npos);
	tempCache = tempSubStr.substr((tempSubStr.find(":")+1),((tempSubStr.find("KB"))-(tempSubStr.find(":"))));

	cacheKB = stoi(tempCache);
	

	//splits to check for fpu
	tempSubStr = s.substr((s.find("fpu")+1),string::npos);
	if (tempSubStr.find("yes") != string::npos)
	{
		fpu = true;
	}

}
/*
function: getPhysSize()
Use: gets the physSize data member
Params: none
Returns: an int
*/
int procInfo::getPhysSize() const 
{
	return physSize;
}

/*
function: getVirtsize()
Use: gets the virtsize data members
Params: none
Returns: an int
*/
int procInfo::getVirtSize() const
{
	return virtSize;
}

/*
function: getRatio()
Use: calculates and returns the ratio
Params: none
Returns: an int
*/
int procInfo::getRatio()
{
	int xp = virtSize - physSize;

	return pow(2,xp);
}

/*
function: getCacheKB()
use: returns the cacheKB data members
Params: none
Returns: an int
*/
int procInfo::getCacheKB() const
{
	return cacheKB;
}

/*
Function: getCachebytes()
Use: calculates and returns the cache in Bytes
Params: none
Returns: an int
*/
int procInfo::getCacheBytes()
{
	return cacheKB*1024;
}

/*
function: getFpu()
Use: checks whether the fpu is set to true
PArams: none
Returns: a bool whether or not the fpu is set
*/
bool procInfo::getFpu()
{
	return fpu;
}
