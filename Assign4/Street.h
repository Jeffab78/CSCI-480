#ifndef STREET_H
#define STREET_H

#include <string>

using namespace std;

class Street
{
	private:
	int streetNum;
	string streetName;
	string direction;
	string corners[2];

	public:
	Street();
	Street(int, string, string, string, string);
	void setStreetNum(int);
	void setStreetName(string);
	void setDirection(string);
	void setCorners(string, string);
	int getStreetNum() const;
	string getStreetName() const;
	string getDirection() const;
	string getCorners() const;

	

};




#endif
