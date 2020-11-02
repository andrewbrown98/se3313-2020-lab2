//Created By: Andrew Brown 20/10/28

#include <iostream>
#include "SharedObject.h"
#include "Semaphore.h"

struct MyShared{
	int sdelay;
	int sthreadID;
	int sreportID;
	bool sRunning;
};


int main(void)
{
	std::cout << "I am a reader" << std::endl;

	Semaphore semR("ReaderSem");
	Shared<MyShared> sharedMemory("sharedMemory");
	

	//Reader will poll the shared memory to determine if it is in use, if it is in use
	// then it will display the data, if it is not it will break 
	while (true){
		if (sharedMemory->sRunning == true){
			semR.Wait();
			std::cout << "ThreadID: " << sharedMemory->sthreadID <<" ReportID: "<<sharedMemory->sreportID <<" Delay: " <<sharedMemory->sdelay <<std::endl;
		
		}else {
			//When a user enters n the value of Running will be set to false and the loop will break causing the reader to terminate
			break;
		}
	}
	//return 0;
}

