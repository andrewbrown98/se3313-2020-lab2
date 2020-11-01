//Created By: Andrew Brown 20/10/28
#include <iostream>
#include "SharedObject.h"
#include "thread.h"
#include <string> 


struct MyShared{
	int sdelay;
	int sthreadID;
	int sreportID;
	bool sRunning;
};

class WriterThread : public Thread{
	public:
		int 	delay;
		int 	threadID;
		int 	reportID = 1;
		bool	flag;
		
		WriterThread(int in, int threadid):Thread(8*1000){
			this->delay = in;
			this->threadID = threadid;
		}

		virtual long ThreadMain(void) override{
			
			Shared<MyShared> sharedMemory ("sharedMemory");
			while(true)// Here the memory values of the thread must be updated
			{
				sharedMemory->sthreadID = threadID; //sets thread ID
				sharedMemory->sreportID = reportID; //sets number of reports
				reportID ++; //increments the number of reports 
				sharedMemory->sdelay = delay;//sets delay
				sleep(delay); //sleeps the thread for the amount of delay set by the user
				if(flag){
					break;
				}
			}
		}
};



int main(void)
{
	std::string userInput;
	std::string userDelay;


	std::cout << "I am a Writer" << std::endl;
	std::cout << "Would you like to create a writer thread?"<< std::endl;

	
	Shared<MyShared> shared("sharedMemory", true); //This is the owner of sharedMamory
	
	while(true){
		
	
		
	}
	
	return 0;	
}