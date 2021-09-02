/*
Assignment 3
Name: Jeff Byerly
Zid: Z1860060
Date: 4/13/2021
*/

#include <iostream>
#include <iomanip>
#include <regex>
#include <cstdlib>
#include <string>
#include <fstream>
#include <unistd.h>
#include <sstream>

#include "flightInfo.h"


using namespace std;

int main(int argc, char *argv[])
{
	//string for input argument
	string CLInput;

	//checks input arguments
	if (argc == 1)
	{
		
		CLInput = "~t90rkf1/d480/dhw/hw3-air/resv.txt"; 
	}

	else if (argc == 2)
	{
		CLInput = argv[1];
	}

	else
	{
		cout << "Please enter valid parameters.";
	}


	vector<flightInfo*> flights;

	//opens the pipe
	int fd[2];
	if (pipe(fd) == -1)
	{
		cout << "Error opening pipe" << endl;
		return 1;
	}
	//forks to create child process
	int pid = fork();



	//clears the buffer
	cout << unitbuf;	

	//child process
	if (pid == 0)
	{
		

		//close write end of pipe since child isn't writing to it
		close(fd[1]);
	
		
		//creates c-string and does 2 reads: 1 for the length to read and second for the data	
		char newRecord[1000];
		char tempRecord[1000];
		int length;
		for (int i=0;i<10;i++)
		{
		read(fd[0], &length, sizeof(int));
		read(fd[0],newRecord,length);

		//checks if newly read record is same as previous, meaning done reading.
		if (tempRecord[20]== newRecord[20])
		{
			close(fd[0]);
			break;
		}
		//copies the record into a temp variable to check when done
		strcpy(tempRecord,newRecord);

		//creates stringstream object for output
		ostringstream childOutput;

		childOutput << endl <<  "Child Received: " << newRecord << endl << "Child read " << length << " bytes." << endl;
		cout << childOutput.str();
		

		
		//	flightInfo *tempFlightInfo = new flightInfo(newRecord);
		//	flights.push_back(tempFlightInfo);
		}
		
		//close read end of pipe when done.
		close(fd[0]);
	}

	//parent process
	else 
	{
		//close read FD since parent doesn't read from pipe
		close(fd[0]);
		
		
		
		ifstream infile(CLInput);
		string newRecord;
		int numRecords =1;
		while (true)
		{
			ostringstream output;
			//gets the next record
			getline(infile,newRecord);

			if (infile.eof())
				break;

			int length = newRecord.length();
				
			//test output to stdout
			output << endl << "Parent read record #" <<numRecords << ": " <<  newRecord << endl << "Parent wrote " << length << " bytes." << endl;
			cout << output.str();

			//turns the string into a cstr to send to pipe
		//	int length = newRecord.length();
			char CStrRecord[length];
			strcpy(CStrRecord, newRecord.c_str());

			//increments the number of records
			numRecords++;
			
			
			
			write(fd[1], &length, sizeof(int));

			write(fd[1], CStrRecord,length);
			

		}

		//close write end of pipe when done
		close(fd[1]);
	}







	return 0;
}
