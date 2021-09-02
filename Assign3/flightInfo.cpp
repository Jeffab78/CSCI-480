/*
Assignment 3
Name: Jeff Byerly
Zid: z1860060
Date: 4/13/2021
*/

#include <algorithm>
#include <vector>
#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <string.h>
#include <fstream>
#include <regex>

#include "flightInfo.h"

using namespace std;

flightInfo::flightInfo(string s)
{
	//begins breaking record down

		
	int foundSlash1 = s.find('/');
	Date = s.substr(0,foundSlash1);

	//further breaks down Date into Day/Month/Year
	Day = stoi(Date.substr(0,2));

	string tempMonth = Date.substr(2,3);
	if (tempMonth == "JAN")
		Month = "January";
	else if (tempMonth == "FEB")
		Month ="February";
	else if (tempMonth == "MAR")
		Month = "March";
	else if (tempMonth=="APR")
		Month = "April";
	else if (tempMonth == "MAY")
		Month = "May";
	else if (tempMonth== "JUN")
		Month = "June";
	else if (tempMonth=="JUL")
		Month = "July";
	else if (tempMonth=="AUG")
		Month = "August";
	else if (tempMonth == "SEP")
		Month = "September";
	else if (tempMonth == "OCT")
		Month = "October";
	else if (tempMonth == "NOV")
		Month = "November";
	else
		Month = "December";

	Year = 2000+ stoi(Date.substr(5,2));

	int foundSlash2 = s.find('/',foundSlash1+1);
	flightNum = s.substr(foundSlash1+1,(foundSlash2-foundSlash1)-1);

	int foundSlash3 = s.find('/',foundSlash2+1);
	airports = s.substr(foundSlash2+1,(foundSlash3-foundSlash2)-1);

	int foundSlash4 = s.find('/',foundSlash3+1);
	flightLeg = s.substr(foundSlash3+1,(foundSlash4-foundSlash3)-1);

	int foundSlash5 = s.find('/',foundSlash4+1);
	lastName = s.substr(foundSlash4+1,(foundSlash5-foundSlash4)-1);

	int foundSlash6 = s.find('/',foundSlash5+1);
	firstName = s.substr(foundSlash5+1,(foundSlash6-foundSlash5)-1);


}
//test
string flightInfo::getDate() const
{
	return Date;
}


string flightInfo::getFlightNum() const
{
	return flightNum;
}

string flightInfo::getAirports() const
{
	return airports;
}

string flightInfo::getFlightLeg() const
{
	return flightLeg;
}

string flightInfo::getFirstName() const
{
	return firstName;
}

string flightInfo::getLastName() const
{
	return lastName;
}

int flightInfo::getYear() const
{
	return Year;
}

string flightInfo::getMonth() const
{
	return Month;
}

int flightInfo::getDay() const
{
	return Day;
}



//comparator
bool flightComp (flightInfo* first, flightInfo* second)
{
	bool ret;

	if (first->getYear() != second ->getYear())
	{
		ret = (first ->getYear() < second ->getYear());
		return ret;
	}

	if (first->getMonth() != second ->getMonth())
	{

		ret = (first ->getMonth() < second ->getMonth());
		return ret;
	
	}
	else
	{
		ret = (first->getDay() < second->getDay());
		return ret;
	}
}
