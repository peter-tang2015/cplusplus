// Try.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <algorithm>
#include <iostream>
#include <vector>

#include <windows.h>
#include <iostream>
#include <queue>
#include <process.h>
 
using namespace std;
 
DWORD WINAPI threadConsumer(void*);
DWORD WINAPI threadProducer(void*);
 
#define GETMYRAND() (int)(((double)rand()/(double)RAND_MAX)*100)
 
struct MyData{
     queue<int> food;
     bool producerfinished;
     HANDLE mutex;
     HANDLE controlsemaphore;
};

int _tmain(int argc, _TCHAR* argv[])
{
#if 0
	std::cout << "hello world" << std::endl;

	unsigned int a[] = {1, 2, 4, 8, 8};
	unsigned int val = 5;
	std::vector<unsigned int> aVector(a, a+5);
	std::vector<unsigned int>::iterator lowBound = std::lower_bound(aVector.begin(), aVector.end(), val);

	size_t x = std::distance(aVector.begin(), lowBound);
#endif

     MyData mydata;
     mydata.mutex = CreateMutex(NULL, false, NULL);
     mydata.controlsemaphore = CreateSemaphore(NULL,0,2,NULL);
     mydata.producerfinished=false;
 
     HANDLE handles[3];
 
     handles[0] = CreateThread(0,0,&threadConsumer, (void*)&mydata , 0,0);
     handles[1] = CreateThread(0,0,&threadProducer, (void*)&mydata, 0,0);
     handles[2] = CreateThread(0,0,&threadConsumer, (void*)&mydata, 0,0);
 
     WaitForMultipleObjects(3, handles, true, INFINITE); //"Join" trreads
     
     CloseHandle(mydata.mutex);
     CloseHandle(mydata.controlsemaphore);
	return 0;
}

DWORD WINAPI threadConsumer(void* lp){
     MyData * md = (MyData*)lp;
     
     while(!md->producerfinished){
 
         Sleep(GETMYRAND());
 
         WaitForSingleObject(md->controlsemaphore,INFINITE); //Wait for producer;
 
         WaitForSingleObject(md->mutex, INFINITE); //Mutext Lock
         while(md->food.size()>0){
             char tmps[32];
             sprintf(tmps, "\t%d\t(%d)\n",md->food.front(), GetCurrentThreadId());
             cout<<tmps;
             md->food.pop();
         }
         ReleaseMutex(md->mutex); //Mutex Unlock
 
     }
     return 0;
}
 
DWORD WINAPI threadProducer(void* lp){
     MyData * md = (MyData*)lp;
 
     for(int i =0 ; i < 100; i++){
         char tmps[32];
         sprintf(tmps, "%d\t\t%d\n",i,GetCurrentThreadId());
         cout<<tmps;
     
         Sleep(GETMYRAND());
 
         WaitForSingleObject(md->mutex, INFINITE); //Mutex Lock
         md->food.push(i);
         if(md->food.size()>0)
            ReleaseSemaphore(md->controlsemaphore,1, NULL);
	     ReleaseMutex(md->mutex); //Mutex Unlock
     }
     md->producerfinished=true;
     ReleaseSemaphore(md->controlsemaphore,2, NULL); //Release both threads
     return 0;
}