//Created By: Andrew Brown 20/10/28
#include <iostream>
#include "SharedObject.h"
#include "thread.h"
#include <string> 
#include "Semaphore.h"
#include "semaphore.h"

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
			std::cout<<"Got here1"<<std::endl;
			Semaphore sem1("writerSemaphore"); //creating semaphores for the writer and reader
			Semaphore sem2("readerSemaphore");

				while(true)// Here the memory values of the thread must be updated
			{
				sem1.Wait(); //Lock resource so no others can write to the shared memory at the same time
				//Update the thread information while it is locked
				sharedMemory->sthreadID = threadID; //sets thread ID
				sharedMemory->sreportID = reportID; //sets number of reports
				sharedMemory->sdelay = delay;//sets delay
				reportID ++; //increments the number of reports 
				
				sem1.Signal(); //once the information is set the resource can be unlocked for other read write operations to occur as needed
				sem2.Signal(); //signal the reader semaphore so that reads can occur from the shared resource 
				
				sleep(delay); //sleeps the thread for the amount of delay set by the user
				if(flag){
					break;
				}

			}

			return 1;
			
		}
};



int main(void)
{
	Semaphore sem1("writerSemaphore",1,true); //Creates sem with initial value of one and owner status as true
	Semaphore sem2("readerSemaphore",0,false); //Creates sem with initial value of zero and owner status as false	
	
	
	std::cout<<"Got here3"<<std::endl;
	std::string  userInput;
	std::string userDelay;
	int numThreads=1; //Used for creating writerThread objects where numThreads will be used to give threads ID #s

	std::cout << "I am a Writer" << std::endl;
	
	WriterThread * thread; //declare thread 
	std::cout<<"Got here2"<<std::endl;
	Shared<MyShared> shared("sharedMemory", true); //This is the owner of sharedMamory
	//Set the running value to true so the reader can poll the shared memory
	shared ->sRunning = true;

	
	while(true){
		//Prompt user and get input. 
		std::cout << "Would you like to create a writer thread? Enter Y or N: "<< std::endl;
		getline(std::cin,userInput);
		if(userInput == "Y"){
			std::cout << "Please enter a delay time for this thread: "<< std::endl;
			getline(std::cin,userDelay);
			int delay = atoi(userDelay.c_str()); //Convert the string to and int

			//Create a new writerThread object 
			thread = new WriterThread(delay,numThreads);//instantiate thread 
			numThreads++; //Increase the number of threads 
		}
		else if (userInput == "N"){
			//If the user enters N then the while statement will break and threads will be handled 
			if(numThreads -1 !=0){ //Avoids core dump in the case N is entered first and no threads were created
				shared->sRunning = false;
				break;
			}
			else{
				break;
			}
		}
		else
		{
			//To handle inproper inputs. 
			std::cout << "Invalid input entered." << std::endl;
		}
	}//end while 
	if(numThreads-1 != 0){ //Avoids core dump in the case N is entered first and no threads were created
		thread ->flag = true;
		delete thread; 
	}
	

	return 0;	
}//end main 