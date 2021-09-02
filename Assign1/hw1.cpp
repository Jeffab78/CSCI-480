/******************************************
Assignment 1
Name: Jeff Byerly
Zid: z1860060
Date: 1/29/21

Purpose: Reads files either from /proc or user defined to read cpu data


*******************************************/

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <vector>
#include "procInfo.h"

using namespace std;


int main(int argc, char *argv[])
{
	//variables
	string cpuInfo = "default1";
	string cpuUptime = "defualt2";
	int days;
	int hours;
	int minutes;
	int seconds;
	int recordCount = 0;
	int charCount = 0;
	int procCount = 0;
	int physProcCount = 0;
	bool newID = false;
	string physIDs = "";
	string tempPhysID = "";
	string newPhysIDName;
	vector<string> physIDNames;
	

	//begins checking how many command line arguments
	if (argc == 1)
	{
		cpuInfo = "/proc/cpuinfo";
		cpuUptime = "/proc/uptime";
	}

	else if (argc == 3)
	{
		cpuInfo = argv[1];
		cpuUptime = argv[2];
	}

	else
	{
		cout << "please enter valid parameters.";
	}

	//variable for info(line and full) & uptime strings
	string uptimeInfo;
	string infoStr;
	string fullInfoStr = "";
	

	//creates ifstream objects
	ifstream cpuInfoFile(cpuInfo);
	ifstream cpuUptimeFile(cpuUptime);

	vector<procInfo *> procs;

	//reads in cpuInfo file
	while (true)
	{
		getline(cpuInfoFile, infoStr);
		fullInfoStr += infoStr;

		//pushes new procInfo object into vector after each new entry
	//	if (infoStr.length() < 2)
	//	{
	//		procs.push_back(new procInfo(fullInfoStr);
	//		fullInfoStr = "";
	//	}
		
		//counts the number of processors
		if (infoStr.find("processor") != string::npos)
		{
			if (procCount != 0)
			{
				procInfo * procInfoTemp = new procInfo(fullInfoStr);
				procs.push_back(procInfoTemp);
			}
			procCount++;
			fullInfoStr = "";			
		}

		//counts the physical CPU's
		if (infoStr.find("physical id") != string::npos)
		{

			newPhysIDName = infoStr.substr((infoStr.find(":")+1),string::npos);
			
			//If empty, always pushed first occurance.
			if (physIDNames.empty())
			{
				physIDNames.push_back(newPhysIDName);
				physProcCount++;
			}

			//if current value not in, add
			for (auto it = physIDNames.begin(); it != physIDNames.end(); it++)
			{
				if (*it != newPhysIDName)
				{
					newID = true;
				}
				else
				{
					newID = false;
				}

			}

			//if new, add new processor
			if (newID == true)
			{	
				physProcCount++;
				physIDNames.push_back(newPhysIDName);
				
			}

				

		}
			

		


		//breaks when eof
		if (cpuInfoFile.eof())
		{
			procs.push_back(new procInfo(fullInfoStr));
			break;
		}

		//increments the record and char counts
		charCount += infoStr.length()+1;	 
		recordCount++;
	}


	






	//gets uptime info and splits string for math
	getline(cpuUptimeFile, uptimeInfo, ' ');
	int secondsTotal = stoi(uptimeInfo);
	days = secondsTotal / 86400;
	hours = (secondsTotal%86400) /3600;
	minutes = ((secondsTotal%86400)%3600) / 60;
	seconds = (((secondsTotal%86400)%3600)%60);

	


	//start creating output for part A
	cout << "A: Questions about the cpuinfo file" << endl;
	cout << " 1. The file names are " << cpuInfo << " and " << cpuUptime << endl;
	cout << " 2. There are " << recordCount << " records in this file." << endl;
	cout << " 3. There are " << charCount << " characters in this file." << endl;
	cout << " 4. I used wc -l and wc -m to check if the numbers were correct." << endl << endl;

	//output for questions B
	cout <<	"B: Questions about the configuration" << endl;
	cout << " 1. There are " << procCount << " processors in this system" << endl;
	cout << " 2. There are " << physProcCount << " physical CPUs in this system." << endl;
	cout << " 3. The physical ID's are: ";
       for (auto it = physIDNames.begin(); it != physIDNames.end(); it++)
       {
	       cout << *it << ", ";
       }	
       cout << endl;
       if (procCount / physProcCount > 1)
		cout << " 4. " << "Yes, some processors are sharing cache." << endl << endl;
	else
		cout << " 4. " << "No processors are sharing cache." << endl << endl;

	//output for questions C
	cout << "C: Questions about the first processor in the file" << endl;
	cout << " 1. The physical address size is ";	
	
	cout << (int)(*procs.begin())->getPhysSize();
	cout << " bytes." << endl;

	cout << " 2. The virtual address size is ";
	cout << (int)(*procs.begin())->getVirtSize();
	cout << " bytes." << endl;

	cout << " 3. The ratio of physical to virtual size is ";
	cout << (int)(*procs.begin())->getRatio();
       	cout << "." << endl;

	cout << " 4. This ";
	if ((bool)(*procs.begin())->getFpu()==true)
	{
		cout << "does";
	}
	else
	{
		cout << "does not";
	}
	cout << " have a floating point unit." << endl;
	
	cout << " 5. The cache is ";
	cout << (int)(*procs.begin())->getCacheKB();
	cout << " KB's." << endl;

	cout << " 6. The cache is ";
       	cout << (int)(*procs.begin())->getCacheBytes();
	cout << " bytes." << endl << endl;


	//questions about uptime
	cout << "D. Questions about uptime" << endl;
	cout << " 1. The System has been up for " << uptimeInfo << " seconds." <<endl;
	cout << " 2. The system has been up for " << days << " days, " << hours << " hours, " << minutes <<  " minutes, and " << seconds << " seconds." << endl << endl;
		

	

	return 0;
}

