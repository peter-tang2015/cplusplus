========================================================================
    CONSOLE APPLICATION : Extents Project Overview
========================================================================

AppWizard has created this Extents application for you.

This file contains a summary of what you will find in each of the files that
make up your Extents application.


Extents.vcxproj
    This is the main project file for VC++ projects generated using an Application Wizard.
    It contains information about the version of Visual C++ that generated the file, and
    information about the platforms, configurations, and project features selected with the
    Application Wizard.

Extents.vcxproj.filters
    This is the filters file for VC++ projects generated using an Application Wizard. 
    It contains information about the association between the files in your project 
    and the filters. This association is used in the IDE to show grouping of files with
    similar extensions under a specific node (for e.g. ".cpp" files are associated with the
    "Source Files" filter).

Extents.cpp
    This is the main application source file.

/////////////////////////////////////////////////////////////////////////////
Other standard files:

StdAfx.h, StdAfx.cpp
    These files are used to build a precompiled header (PCH) file
    named Extents.pch and a precompiled types file named StdAfx.obj.

/////////////////////////////////////////////////////////////////////////////
Other notes:

AppWizard uses "TODO:" comments to indicate parts of the source code you
should add to or customize.

/////////////////////////////////////////////////////////////////////////////

Code review comments:
1. The string parsing in extent.txt: using find() is O(N)
 - How about the reading the string into a std::vector<std::string>
2. The atoi() funciton
 - Bug: (unsigned int) (atoi()), as atoi() returns an integer
        again what if atoi() fail, it will returns "0"
 - Think about strtol(), to convet from string to unsigned int
3. Use muiti-threading (producer-consumer machanism to parse the intervals)
 - Just in case the machine runs this software is slow and old
   (Basically not enough mem)
4. Check std::runtime_error(string &) if platform portable
5. Remove the unused variable "result" in Line 511
6. controlsemaphore is not used, the main issue is that in the current scenario
   the conusmer thread runs much ... slower than the producer thread. When the
   consumer thread comes back to wait for semaphore from the producer, the producer
   may have finished the reading&parsing the file. Hence the consumer thread will
   be sitting there to wait for semaphore releasing forever, as this will never
   be happening again because the producer thread has been terminated.
7. if (il->numbersFromFile.size() > 0){
	   WaitForSingleObject(il->mutex, INFINITE); //Mutext Lock
   In the consumer thread, this is not thread-safe for multi-consumer threads.
   For instance two consumer threads reach "il->numbersFromFile.size() > 0" at 
   the same time (we know that only one element in the queue), both threads read
   out the queue is not empty. Then when coming to acquire the mutex, only one can
   get hook the mutex and gain the only one element and parse it, afterwards release
   the mutex. At this moment the other consumer thread acquires the mutex and try
   to process this only one element, but actually now here it is empty.

		 if (il->numbersFromFile.size() > 0){
			 WaitForSingleObject(il->mutex, INFINITE); //Mutext Lock
			 vector<unsigned int> numbers(il->numbersFromFile.front());// have a local copy
			 il->numbersFromFile.pop();
			 ReleaseMutex(il->mutex); //Mutex Unlock	
			 vector<unsigned int> results;
			 il->ic.GetCounters(numbers, results);
			 copy(results.begin(),
				  results.end(),
				  ostream_iterator<unsigned int>(cout,"\n"));				 
		#ifdef _DEBUG
					numResult.WriteResults(results);
		#endif
         }  

		 ======>
		 vector<unsigned int> numbers;
		 WaitForSingleObject(il->mutex, INFINITE);
		 if (il->numbersFromFile.size() > 0) {
			 numbers = vector<unsigned int> (il->umbersFromFile.front());
			 il->numbersFromFile.pop();
		 }
		 ReleaseMutex(il->mutex);
		 if (!numbers.empty()) {
		     vector<unsigned int> results;
			 il->ic.GetCounter(numbers, results);
			 copy(results.begin(), results.end(), ostream_iterator<unsinged int> (cout, "\n");
		#ifdef _DEBUG
		     numResult.WriteResults(results);
	    #endif
		 }
8. Multi consumer threading: discussion to sync the output.
9. Move SweepLineFunctor as an inner struct of SweepLineAlg class
