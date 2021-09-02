#ifndef FLIGHTINFO_H
#define FLIGHTINFO_H

#include <string>

using namespace std;

class flightInfo
{
	private:
		int Year;
		int Month;
		int Day;
		string flightNum;
		string airports;
		string flightLeg;
		string passengerName;
		
	public:
		//string or char[]?
		flightInfo(string s);
		int getYear() const;
		int getMonth() const;
		int getDay() const;

};

//comparator here
bool flight_comp(flightInfo* first, flightInfo* second);

#endif
