//Created By: Andrew Brown 20/10/28

#include <iostream>
#include "SharedObject.h"

struct MyShared{
	int threadNum;
	int ID;
	int reportID;
	bool Running;
};

int main(void)
{
	std::cout << "I am a reader" << std::endl;

	Shared<MyShared> sharedMem("Shared Memory");//create object of type MyShared named SharedMem  

	//Reader will poll the shared memory to determine if it is in use, if it is in use
	// then it will display the data, if it is not it will break 
	while (true){
		if (sharedMem->Running == true){
			std::cout << "ThreadID: "<< sharedMem->reportID
		}

	
	}
}
