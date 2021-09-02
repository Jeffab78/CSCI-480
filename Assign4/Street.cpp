/*
Assignment 4
Name: Jeff Byerly
Zid: z1860060
Date: 4/23/2021
*/

#include "Street.h"
#include <iostream>
#include <iomanip>


using namespace std;

//default constructor
Street::Street()
{

}
//constructor
Street::Street(int i, string s1, string s2, string s3, string s4)
{
	streetNum = i;
	streetName = s1;
	direction = s2;
	corners[0] = s3;
	corners[1] = s4;
}

void Street::setStreetNum(int i)
{
	this->streetNum = i;
}

int Street::getStreetNum() const
{
	return streetNum;
}

void Street::setStreetName(string s)
{
	this->streetName = s;
}

string Street::getStreetName() const
{
	return streetName;
}

void Street::setDirection(string s)
{
	this->direction = s;
}

string Street::getDirection() const
{
	return direction;
}
