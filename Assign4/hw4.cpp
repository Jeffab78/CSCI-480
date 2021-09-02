/*
Assignment 4
Name: Jeff Byerly
Zid: z1860060
Date: 4/23/2021
*/

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <semaphore.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <errno.h>
#include <unistd.h>
#include <cstdlib>
#include <cstring>
#include "Street.h"

using namespace std;

//structure for semaphores
struct sem_struct
{
	sem_t semlock[5];
};

//prototypes for useful functions
void process_street(Street s, sem_struct * sem_addr);
void print_msg(sem_t* sem, string msg);

int main(int argc, char *argv[])
{

	if (argc != 1 )
	{
		cout << "Invalid Parameters. Program takes no arguments.\n";
		return 1;
	}

	cout << unitbuf;

	//creates shared memory and checks that it worked
	int segment_id = shmget(IPC_PRIVATE,(sizeof(sem_t)*5), S_IRUSR | S_IWUSR);
	if (segment_id == -1)
	{
		cout << "failed to create shared memory" << endl;
		return 1;
	}

	cout << "Successfully got shared memory with id: " << segment_id << endl;
	
	//creates semaphore struct
	sem_struct *sem_addr;

	//attaches memory and checks that it worked
	sem_addr = (sem_struct *)shmat(segment_id, NULL, 0);

	if (sem_addr == (sem_struct *)-1)
	{
		cout << "Failed to attach memory" << endl;
		return 1;
	}

	cout << "Successfully attached to shared memory at: " << &(sem_addr) << endl;
	
	int initSem;

	//initializes all 5 semaphores
	for (int i=0; i<5;i++)
	{

		initSem = sem_init(&sem_addr->semlock[i], 1,1);
		if (initSem == -1)
			cout << "failed to initialize semaphore " << i << endl;
		else
		{
			int value;
			sem_getvalue(&sem_addr->semlock[i],&value);
			if (i!=4)
				cout << "Initialized semaphore #" << i << ": to "<< value << endl;
			else
				cout << "Initialized semaphore #" << i << "(for cout): to " << value << endl << endl;
		}
	}	


	//create the Street objects
	Street streets[4];
	streets[0] = Street(0, "Lincoln Hwy", "West","NE","NW");
	streets[1] = Street(1, "Annie Glidden", "North", "SE", "NE");
	streets[2] = Street(2, "Lincoln Hwy", "East", "SE","SW");
	streets[3] = Street(3, "Annie Glidden", "South", "NW", "SW");


	int pid;
	int childID[4];
	//loop to create 4 child processes
	for (int i=0; i<4;i++)
	{	
		 pid = fork();
		if (pid <0)
		{	
			cout << "failed to create child\n";
			return 1;
		}
		else
			childID[i] = pid;
	
		if (childID[i] == 0)
		{
			//makes string and grabs semaphore for cout to begin processing street
			string message = "Child #"; 
			message+= to_string(i);
			message += " working with " + streets[i].getStreetName() +" " + streets[i].getDirection() + "\n";

			print_msg(&sem_addr->semlock[4],message);
			
			process_street(streets[i],sem_addr);
			//
			exit(0);
		}
	}
		
	//detach and free the memory when done.
	 int freeMem = shmdt((void*)sem_addr);
	 if (freeMem == -1)
	 {
		 cout << "Failed to detach shared memory." << endl;
		 return 1;
	 }

	 freeMem = shmctl(segment_id, IPC_RMID, NULL);
	 if (freeMem == -1)
	 {
		 cout << "Failed to free the shared memory." << endl;
		 return 1;
	 }


		

	
return 0;


}
/*
function: process_street
Use: Uses to process each lane
Params: Takes in the street object to parse and the struct of semaphores
Returns: nothing
*/
void process_street(Street s, sem_struct* sem_addr)
{
	string msg, tempmsg;
	int status1, status2;
	//process 9 cars each
	 for (int x=1; x < 10;x++)
	 {	
		msg ="On " + s.getStreetName() +" " + s.getDirection()+ ", " + "car ";
		msg += to_string(x);
		

		//if LHW West
		if (s.getStreetNum() == 0)
		{
			//grabs NE semaphore
			status1 = sem_wait(&sem_addr->semlock[0]);
			if (status1 == -1)
				cout << "failed to lock semaphore 0";
			else
			{
				tempmsg = msg;
			        tempmsg	+= " has obtained lock for NE\n";
				print_msg(&sem_addr->semlock[4],tempmsg);

			}
			//grabs NW semaphore
			status2 = sem_wait(&sem_addr->semlock[1]);
			if (status2 == -1)
				cout << "failed to lock semaphore 1";
			else
			{
				tempmsg=msg;
				tempmsg+= " has obtained lock for NW\n";
				print_msg(&sem_addr->semlock[4],tempmsg);
			}

			tempmsg=msg;
			tempmsg += " now has both locks.\n";
			print_msg(&sem_addr->semlock[4],tempmsg);

			tempmsg=msg;
			tempmsg += " has crossed.\n";
			print_msg(&sem_addr->semlock[4],tempmsg);

			//releases NE semaphore
			status1 = sem_post(&sem_addr->semlock[0]);
			if (status1 == -1)
				cout << "failed to release semaphore 0\n";
			else
			{
				tempmsg=msg;
				tempmsg += " has unlocked NE\n";
				print_msg(&sem_addr->semlock[4],tempmsg);
			}

			//release NW semaphore
			status2 = sem_post(&sem_addr->semlock[1]);
			if (status2==-1)
				cout << "Failed to release semaphore 1\n";
			else
			{
				tempmsg=msg;
				tempmsg+= " has unlocked NW\n";
				print_msg(&sem_addr->semlock[4],tempmsg);

				tempmsg=msg;
				tempmsg+= " has released both locks.\n";
				print_msg(&sem_addr->semlock[4],tempmsg);

			}





		}
		//if AG North
		else if (s.getStreetNum() ==1)
		{
			//grabs NE semaphore
			status1 = sem_wait(&sem_addr->semlock[0]);
			if (status1 == -1)
				cout << "failed to lock semaphore 0";
			else
			{
				tempmsg = msg;
			        tempmsg	+= " has obtained lock for NE\n";
				print_msg(&sem_addr->semlock[4],tempmsg);

			}
			//grabs SE semaphore
			status2 = sem_wait(&sem_addr->semlock[2]);
			if (status2 == -1)
				cout << "failed to lock semaphore 2";
			else
			{
				tempmsg=msg;
				tempmsg+= " has obtained lock for SE\n";
				print_msg(&sem_addr->semlock[4],tempmsg);
			}

			tempmsg=msg;
			tempmsg += " now has both locks.\n";
			print_msg(&sem_addr->semlock[4],tempmsg);

			tempmsg=msg;
			tempmsg += " has crossed.\n";
			print_msg(&sem_addr->semlock[4],tempmsg);

			//releases NE semaphore
			status1 = sem_post(&sem_addr->semlock[0]);
			if (status1 == -1)
				cout << "failed to release semaphore 0\n";
			else
			{
				tempmsg=msg;
				tempmsg += " has unlocked NE\n";
				print_msg(&sem_addr->semlock[4],tempmsg);
			}

			//release SE semaphore
			status2 = sem_post(&sem_addr->semlock[2]);
			if (status2==-1)
				cout << "Failed to release semaphore 2\n";
			else
			{
				tempmsg=msg;
				tempmsg+= " has unlocked SE\n";
				print_msg(&sem_addr->semlock[4],tempmsg);

				tempmsg=msg;
				tempmsg+= " has released both locks.\n";
				print_msg(&sem_addr->semlock[4],tempmsg);

			}





		}

		//if LHW East
		else if (s.getStreetNum() ==2)
		{
		
			//grabs SE semaphore
			status1 = sem_wait(&sem_addr->semlock[2]);
			if (status1 == -1)
				cout << "failed to lock semaphore 2";
			else
			{
				tempmsg = msg;
			        tempmsg	+= " has obtained lock for SE\n";
				print_msg(&sem_addr->semlock[4],tempmsg);

			}
			//grabs SW semaphore
			status2 = sem_wait(&sem_addr->semlock[3]);
			if (status2 == -1)
				cout << "failed to lock semaphore 3";
			else
			{
				tempmsg=msg;
				tempmsg+= " has obtained lock for SW\n";
				print_msg(&sem_addr->semlock[4],tempmsg);
			}

			tempmsg=msg;
			tempmsg += " now has both locks.\n";
			print_msg(&sem_addr->semlock[4],tempmsg);

			tempmsg=msg;
			tempmsg += " has crossed.\n";
			print_msg(&sem_addr->semlock[4],tempmsg);

			//releases SE semaphore
			status1 = sem_post(&sem_addr->semlock[2]);
			if (status1 == -1)
				cout << "failed to release semaphore 2\n";
			else
			{
				tempmsg=msg;
				tempmsg += " has unlocked SE\n";
				print_msg(&sem_addr->semlock[4],tempmsg);
			}

			//release SW semaphore
			status2 = sem_post(&sem_addr->semlock[3]);
			if (status2==-1)
				cout << "Failed to release semaphore 3\n";
			else
			{
				tempmsg=msg;
				tempmsg+= " has unlocked SW\n";
				print_msg(&sem_addr->semlock[4],tempmsg);
				
				tempmsg=msg;
				tempmsg+= " has released both locks.\n";
				print_msg(&sem_addr->semlock[4],tempmsg);



			}

		}

		//if AG South
		else if (s.getStreetNum() == 3)
		{
			//grabs NW semaphore
			status1 = sem_wait(&sem_addr->semlock[1]);
			if (status1 == -1)
				cout << "failed to lock semaphore 1";
			else
			{
				tempmsg = msg;
			        tempmsg	+= " has obtained lock for NW\n";
				print_msg(&sem_addr->semlock[4],tempmsg);

			}
			//grabs SW semaphore
			status2 = sem_wait(&sem_addr->semlock[3]);
			if (status2 == -1)
				cout << "failed to lock semaphore 3";
			else
			{
				tempmsg=msg;
				tempmsg+= " has obtained lock for SW\n";
				print_msg(&sem_addr->semlock[4],tempmsg);
			}

			tempmsg=msg;
			tempmsg += " now has both locks.\n";
			print_msg(&sem_addr->semlock[4],tempmsg);

			tempmsg=msg;
			tempmsg += " has crossed.\n";
			print_msg(&sem_addr->semlock[4],tempmsg);

			//releases NW semaphore
			status1 = sem_post(&sem_addr->semlock[1]);
			if (status1 == -1)
				cout << "failed to release semaphore 1\n";
			else
			{
				tempmsg=msg;
				tempmsg += " has unlocked NW\n";
				print_msg(&sem_addr->semlock[4],tempmsg);
			}

			//release SW semaphore
			status2 = sem_post(&sem_addr->semlock[3]);
			if (status2==-1)
				cout << "Failed to release semaphore 3\n";
			else
			{
				tempmsg=msg;
				tempmsg+= " has unlocked SW\n";
				print_msg(&sem_addr->semlock[4],tempmsg);

				tempmsg=msg;
				tempmsg+= " has released both locks.\n";
				print_msg(&sem_addr->semlock[4],tempmsg);


			}



		}
	

	 }
}

/*
function: print_msg
Use: Uses the semaphores to print each msg
Params: Takes a semeaphore and the string to print
Returns: nothing
*/
void print_msg(sem_t* sem, string msg)
{
	int status;

	status = sem_wait(sem);
	if (status == -1)
		cout << "Failed to lock semaphore\n";

	cout << msg;

	status = sem_post(sem);
	if (status == -1)
		cout << "Failed to unlock semaphore\n";
	
}
