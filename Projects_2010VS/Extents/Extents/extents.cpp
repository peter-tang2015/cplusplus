/* Extents.cpp : Defines the entry point for the console application.
Platform: Windows 8, 64 bit version
Machine: i3-3327U @1.9G, 6G RAM
Compiler: Visual Studio 2010 Express (Win32 Console Application)
Author: Peter Tang

Delivery:
A single thread version
A multi thread version: 1 producer thread and 1 consumer thread
Performance: 
- Output directly to file
Single thread: 0.196 second to read numbers from numbers.txt and process it
Multi-thread: 0.170 second to read numbers from numbers.txt and process it
(numbers.txt provieded by Barclays)
- Output to screen
Multi-thread has no advantage over single-thread as both takes around 31 
seconds.
- Analysis: The most of time is consumed is to display to the screen.

The default version is Multi-thread version. Can be easily switched into 
single-thread by #if 0/1.

Assumption:
1. The maximally size of interval source file (extents.txt) is limited to 50 
millions records, so these should be no problem to load it to memory.
It takes roughly 0.088 seconds to load the exmaple provided by Barclays.
(Read from the file, process the string and sort the lower and upper bounds)

2. The number input file could be huge, so the mutli-thread (producer-consumer
mechanism) could benefit the performance. As the size could be billions, so
the reading from the file has to be chopped into multi.

3. The extends.txt and numbers.txt have to be end with an empty line.

4. "stdafx.h" is auto-generated header files from Visual Studio 2010 Express

Alogrithms:
Sweep line algorithms: http://en.wikipedia.org/wiki/Sweep_line_algorithm
Interval's lower bounds and upper bounds are sorted into two arraries. In this 
case we use qsort. Then find out how many lower bounds and upper bounds the 
number sweeps. The count  of this number crossing the intervals is equal to 
the difference of sweeping the lower bounds and upper bounds.

For say the intervals has 50 millions. 50 millons is > 2^25 and < 2^26. For a 
number it takes 26*2 = 52 times searching at most.

*/

#include "stdafx.h"
#include <algorithm>
#include <cassert>
#include <ctime>
#include <iostream>
#include <iterator>
#include <fstream>
#include <queue>
#include <string>
#include <vector>

// system specific headers
#include <Windows.h>
#include <process.h>

using namespace std;

namespace Utility {
class BigTextFile
{
protected:
	BigTextFile(const string &fileName) : m_FileName(fileName){
	}

	virtual ~BigTextFile() {};
	
private:
	string m_FileName;
};

class BigTextInputFile : BigTextFile
{
public:
	BigTextInputFile(const string &fileName);
	~BigTextInputFile();

	// put the lines of data into text
	// and return the acutal lines that read into text
	size_t ReadLines(size_t lines, string &text);

	// read the whole file into one string
	void ReadAll(string &text);

private:
	ifstream m_IFileStream;
};

class BigTextOutputFile : BigTextFile
{
public:
	BigTextOutputFile(const string &fileName);
	~BigTextOutputFile();

	void WriteResults(vector<unsigned int> &results);

private:
	ofstream m_OFileStream;
};

class DataParser{
public:
	static void ParseIntervalStringToNumber(const string &text, 
											vector<unsigned int> &lowerBounds,
											vector<unsigned int> &upperBounds);
	static void ParseValueStringToNumber(const string &text,
										 vector<unsigned int> &vals);
	static void ParseOneIntervalToBounds(const string &oneInterval,
										 unsigned int &lowerBound,
										 unsigned int &upperBound);
	static void ParserOneLineValueStringToNumber(const string &oneLineValueString,
												 vector<unsigned int> &vals);
};

BigTextInputFile::BigTextInputFile(const string &fileName)
	:BigTextFile(fileName), 
	 m_IFileStream(fileName)
{
}

BigTextInputFile::~BigTextInputFile()
{
	if (m_IFileStream.is_open()) {
		m_IFileStream.close();
	}
}

size_t BigTextInputFile::ReadLines(size_t lines, string &text)
{
	if (m_IFileStream.is_open()) {
		size_t readLines= 0;
		text.clear();
		string oneLineString;
		while (readLines < lines && m_IFileStream.good()){
			getline(m_IFileStream, oneLineString);
			text += '\n';
			text += oneLineString;
			++readLines;
		}
		if (m_IFileStream.good()) {
			text += '\n'; // append an return at the end if not EOF
		}

		return readLines;
	}
	else {
		throw std::runtime_error("BigTextFile:: invalid file");
	}
}

void BigTextInputFile::ReadAll(string &text)
{
	if (m_IFileStream.is_open()){
		text = string((istreambuf_iterator<char>(m_IFileStream)), istreambuf_iterator<char>());
	}
	else {
		throw std::runtime_error("BigTextFile:: invalid input file");
	}
}

BigTextOutputFile::BigTextOutputFile(const string &fileName)
	:BigTextFile(fileName), m_OFileStream(fileName)
{
}

BigTextOutputFile::~BigTextOutputFile()
{
	if (m_OFileStream.is_open()){
		m_OFileStream.close();
	}
}

void BigTextOutputFile::WriteResults(vector<unsigned int> &results)
{
	if (m_OFileStream.good()){
		copy(results.begin(), results.end(), ostream_iterator<unsigned int>(m_OFileStream,"\n"));
	}
	else{
		throw std::runtime_error("BigTextFile:: invalid output file");
	}
}

void DataParser::ParseIntervalStringToNumber(const string &text,
										   vector<unsigned int> &lowerBounds,
										   vector<unsigned int> &upperBounds)
{
	size_t found, cur_pos = 0;
	string oneIntervalString;
	unsigned int lowerBound, upperBound;
	while ((found = text.find('\n', cur_pos + 1)) != string::npos) {
		oneIntervalString = text.substr(cur_pos, found - cur_pos);
		ParseOneIntervalToBounds(oneIntervalString, lowerBound, upperBound);
		lowerBounds.push_back(lowerBound);
		upperBounds.push_back(upperBound);
		cur_pos = found;
	}

}

void DataParser::ParseValueStringToNumber(const string &text,
									      vector<unsigned int> &values)
{
	size_t found, cur_pos = 0;
	string oneLineString;
	while ((found = text.find('\n', cur_pos + 1)) != string::npos) {
		oneLineString = text.substr(cur_pos, found - cur_pos);
		ParserOneLineValueStringToNumber(oneLineString, values);
		cur_pos = found;
	}
}

void DataParser::ParserOneLineValueStringToNumber(const string &oneLineValueString,
												  vector<unsigned int> &vals)
{
	size_t found, cur_pos = 0;
	string oneValueString;
	while ((found = oneLineValueString.find(' ', cur_pos + 1)) != string::npos) {
		oneValueString = oneLineValueString.substr(cur_pos, found - cur_pos);
		vals.push_back(atoi(oneValueString.c_str()));
		cur_pos = found;
	}

	// hit here if oneValueString has one one value left
	if (!oneLineValueString.empty()){
		vals.push_back(atoi(oneLineValueString.c_str()));
	}
}

void DataParser::ParseOneIntervalToBounds(const string &oneInterval,
										  unsigned int &lowerBound,
										  unsigned int &upperBound)
{
	size_t found;
	if ((found = oneInterval.find(' ')) != string::npos){
		string str_LowerBound = oneInterval.substr(0, found);
        string str_UpperBound = oneInterval.substr(found + 1, oneInterval.size() - found -1);
		lowerBound = atoi(str_LowerBound.c_str());
		upperBound = atoi(str_UpperBound.c_str());
	}
	else{
		throw std::runtime_error("Invalid Interval Input");
	}
}

}; // Utility

namespace Intervals{
enum IntervalCounterAlgType : unsigned int{
	SWEEPLINE,
	OTHER_ALG
};

// interface class
class IntervalCounter{
public:
	virtual ~IntervalCounter() = 0  {};
	// set the intervals based on the exisiting intervals
	virtual void SetIntervals(const vector<unsigned int> &lowerBounds,
							  const vector<unsigned int> &upperBounds) = 0;
	
	// Read intervals from the files 
	virtual void SetIntervals(const string &fileName) = 0;

	// Get the counter againt a vlaue
	virtual unsigned int GetCounter(unsigned int val) = 0;

	// Get the counters against a list of value
	virtual void GetCounters(const vector<unsigned int> &vals,
							 vector<unsigned int> &counters) = 0;
};

// algorithms to detect the counters of intervals
class IntervalCounterDetector{
public:
	virtual ~IntervalCounterDetector() = 0 {};

	// any preprocess work need to be done before calling detect
	virtual void PreProcess(vector<unsigned int> &lowerBounds,
							vector<unsigned int> &upperBounds) = 0;
	// detect the coutner
	virtual unsigned int DetectCounter(unsigned int val,
									   const vector<unsigned int> &lowerBounds,
									   const vector<unsigned int> &upperBounds) = 0;
	virtual void DetectCounters(const vector<unsigned int> &vals,
								vector<unsigned int> &results,
								const vector<unsigned int> &lowerBounds,
								const vector<unsigned int> &upperBounds) = 0;
};

// implementation of IntervalCounter
// base on Sweep Line Algorithm
class IntervalCounterImp : public IntervalCounter {
public:
	IntervalCounterImp(IntervalCounterAlgType);
	virtual ~IntervalCounterImp();

public:
	void SetIntervals(const vector<unsigned int> &lowerBounds,
					  const vector<unsigned int> &upperBounds);
	void SetIntervals(const string &intervalSrcFile);
	unsigned int GetCounter(unsigned int val);
	void GetCounters(const vector<unsigned int> &vals,
					 vector<unsigned int> &coutners);
private:
	void InitDetector(IntervalCounterAlgType);
private:
	// list of start values of intervals
	vector<unsigned int> m_LowerBounds;
	// list of end values of intervals
	vector<unsigned int> m_UpperBounds;

	// alorithms
	std::auto_ptr<IntervalCounterDetector> m_Detector;
};

// sweep line algorithm  to detect the counter
// here maybe we can have some api for alogrithm ?
class SweepLineAlg : public IntervalCounterDetector{
public:
	SweepLineAlg();
	~SweepLineAlg();

public:
	// this function is to preprocess on the intervals
	void PreProcess(vector<unsigned int> &lowerBounds,
					vector<unsigned int> &upperBounds);

	unsigned int DetectCounter(unsigned int val,
							   const vector<unsigned int> &lowerBounds,
							   const vector<unsigned int> &upperBounds);
	void DetectCounters(const vector<unsigned int> &vals,
						vector<unsigned int> &results,
						const vector<unsigned int> &lowerBounds,
						const vector<unsigned int> &upperBounds);
private:
	static int CompareFunc(const void *a, const void *b);

	struct SweepLineFunctor{
		SweepLineFunctor(const vector<unsigned int> &lowerBounds,
						 const vector<unsigned int> &upperBounds);

		unsigned int operator()(unsigned int val);

		const vector<unsigned int> &m_SortedLowerBounds;
		const vector<unsigned int> &m_SortedUpperBounds;
	};

};

IntervalCounterImp::IntervalCounterImp(IntervalCounterAlgType algType)
{
	InitDetector(algType);
}

IntervalCounterImp::~IntervalCounterImp()
{

}

void IntervalCounterImp::InitDetector(IntervalCounterAlgType algType)
{
	switch(algType){
	case SWEEPLINE:
		m_Detector = auto_ptr<IntervalCounterDetector>(new SweepLineAlg());
		break;
	default:
		assert(false);
		break;
	}
}

void IntervalCounterImp::SetIntervals(const vector<unsigned int> &lowerBounds,
									  const vector<unsigned int> &upperBounds)
{
	// shrink the size
	vector<unsigned int>().swap(m_LowerBounds);
	vector<unsigned int>().swap(m_UpperBounds);

	// make the copy -- not good for big data
	m_LowerBounds = lowerBounds;
	m_UpperBounds = upperBounds;

	// get ready for use
	m_Detector->PreProcess(m_LowerBounds, m_UpperBounds);
}

void IntervalCounterImp::SetIntervals(const string &intervalSrcFileName)
{
	// populate out the intervals to m_LowerBound and m_UpperBound
	Utility::BigTextInputFile file(intervalSrcFileName);
	string text;
	file.ReadAll(text);

	// parse the result
	Utility::DataParser::ParseIntervalStringToNumber(text, m_LowerBounds, m_UpperBounds);

	m_Detector->PreProcess(m_LowerBounds, m_UpperBounds);
}

unsigned int IntervalCounterImp::GetCounter(unsigned int val)
{
	return m_Detector->DetectCounter(val, m_LowerBounds, m_UpperBounds);
}

void IntervalCounterImp::GetCounters(const vector<unsigned int> &vals,
									 vector<unsigned int> &counters)
{
	m_Detector->DetectCounters(vals, counters, m_LowerBounds, m_UpperBounds);
}

SweepLineAlg::SweepLineAlg()
{
}
SweepLineAlg::~SweepLineAlg()
{
}
void SweepLineAlg::PreProcess(vector<unsigned int> &lowerBounds,
							  vector<unsigned int> &upperBounds)
{
	// sort the start/end arraries of intervals
	qsort(&lowerBounds[0], lowerBounds.size(), sizeof(unsigned int), SweepLineAlg::CompareFunc);
	qsort(&upperBounds[0], upperBounds.size(), sizeof(unsigned int), SweepLineAlg::CompareFunc);
}

int SweepLineAlg::CompareFunc(const void *a, const void *b)
{
	return (*(const unsigned int*)a - *(const unsigned int*)b);
}

SweepLineAlg::SweepLineFunctor::SweepLineFunctor(const vector<unsigned int> &lowerBounds,
					 const vector<unsigned int> &upperBounds):
	m_SortedLowerBounds(lowerBounds),
	m_SortedUpperBounds(upperBounds)
{

}

unsigned int SweepLineAlg::SweepLineFunctor::operator()(unsigned int val)
{
	// find out how many "lowerBounds" and "upperBounds" val has sweeped
    vector<unsigned int>::const_iterator sweepCountInLowerBound = 
			upper_bound(m_SortedLowerBounds.begin(), m_SortedLowerBounds.end(), val);
    vector<unsigned int>::const_iterator sweepCountInUpperBound = 
			lower_bound(m_SortedUpperBounds.begin(), m_SortedUpperBounds.end(), val);
		
	return (distance(m_SortedLowerBounds.begin(), sweepCountInLowerBound) - 
			distance(m_SortedUpperBounds.begin(), sweepCountInUpperBound));
}

unsigned int SweepLineAlg::DetectCounter(unsigned int val,
										 const vector<unsigned int> &lowerBounds,
										 const vector<unsigned int> &upperBounds)
{
	return SweepLineFunctor(lowerBounds, upperBounds)(val);
}

void SweepLineAlg::DetectCounters(const vector<unsigned int> &vals,
								  vector<unsigned int> &results,
								  const vector<unsigned int> &lowerBounds,
								  const vector<unsigned int> &upperBounds)
{
	// shrink results to the needed
	vector<unsigned int>().swap(results);
	results.resize(vals.size());

	// iterator each value and save the result
	transform(vals.begin(), vals.end(), results.begin(), SweepLineFunctor(lowerBounds, upperBounds));
}

} // Intervals

using namespace Intervals;
using namespace Utility;

struct IntervalLock{
	IntervalCounter& ic;
	queue<vector<unsigned int> > numbersFromFile;
	string numbersFileName;
    bool eof;
    HANDLE mutex;
    HANDLE controlsemaphore;
	size_t countOfConsumerThreads;
	
	IntervalLock(IntervalCounter &intervalCounter,
				 size_t consumerThreads, const string &numbersSrcFileName) 
		: ic(intervalCounter), eof(false),
		  countOfConsumerThreads(consumerThreads),
		  numbersFileName(numbersSrcFileName)
	{
		mutex = CreateMutex(NULL, false, NULL);
		controlsemaphore = CreateSemaphore(NULL, 0, countOfConsumerThreads,NULL);
	}

	~IntervalLock()
	{
		CloseHandle(mutex);
		CloseHandle(controlsemaphore);
	}
};

DWORD WINAPI threadReadNumbersFromFile(void* lp){
     IntervalLock *il = (IntervalLock*)lp;

	try{
		BigTextInputFile numFile(il->numbersFileName);

#ifdef _DEBUG
		BigTextOutputFile numResult("expected.txt");
#endif

		const size_t toReadLines = 8096;
		vector<unsigned int> values;
		string text;
		while (numFile.ReadLines(toReadLines, text) > 0){
			DataParser::ParseValueStringToNumber(text, values);

			WaitForSingleObject(il->mutex, INFINITE); //Mutex Lock
			il->numbersFromFile.push(values);
			ReleaseMutex(il->mutex); //Mutex Unlock

			//ReleaseSemaphore(il->controlsemaphore,1, NULL);

			// clear the data
			values.clear();
		}
	}
	catch (std::exception &e) {
		il->eof=true;
		// ReleaseSemaphore(il->controlsemaphore, il->countOfConsumerThreads, NULL); //Release all comsumer threads
		cout << e.what() << endl;
	}

	il->eof=true;
	// ReleaseSemaphore(il->controlsemaphore, il->countOfConsumerThreads, NULL); //Release all comsumer threads
    return 0;
}

DWORD WINAPI threadDetector(void* lp){
     IntervalLock *il = (IntervalLock*)lp;
#ifdef _DEBUG
	 BigTextOutputFile numResult("expected.txt");
#endif
     while(!il->eof || il->numbersFromFile.size()>0){
         //WaitForSingleObject(il->controlsemaphore,INFINITE); //Wait for producer;
 
		 vector<unsigned int> numbers;

		 WaitForSingleObject(il->mutex, INFINITE); //Mutext Lock
		 if (il->numbersFromFile.size() > 0){
			 numbers = vector<unsigned int>(il->numbersFromFile.front());// have a local copy
			 il->numbersFromFile.pop();
		 }
		 ReleaseMutex(il->mutex); //Mutex Unlock	
		 
		 if (!numbers.empty()){
			 vector<unsigned int> results;
			 il->ic.GetCounters(numbers, results);
			 copy(results.begin(),
				  results.end(),
				  ostream_iterator<unsigned int>(cout,"\n"));				 
#ifdef _DEBUG
			numResult.WriteResults(results);
#endif
         }          
     }
     return 0;
}

#if 1
int _tmain(int argc, _TCHAR* argv[])
{
#ifdef PROFILING_STATS
	clock_t pre_clock = clock();
	clock_t cur_clock;
	float timeToProcessInterval;
#endif
	try {
		// load the intervals
		IntervalCounter &ic = IntervalCounterImp(SWEEPLINE);
		ic.SetIntervals("extents.txt");

#ifdef PROFILING_STATS
		cur_clock = clock();
		timeToProcessInterval = (float) (cur_clock - pre_clock);
		pre_clock = cur_clock;
#endif

		IntervalLock il(ic, 1, "numbers.txt");
		
		HANDLE handles[2];
		handles[0] = CreateThread(0,0,&threadReadNumbersFromFile, (void*)&il , 0,0);
		handles[1] = CreateThread(0,0,&threadDetector, (void*)&il, 0,0);
 
		WaitForMultipleObjects(2, handles, true, INFINITE); //"Join" trreads
	}
	catch (std::exception &e){
		cout << e.what();
	}

#ifdef PROFILING_STATS
	cur_clock = clock();
	cout << "Time consumed to process intervals" << timeToProcessInterval/CLOCKS_PER_SEC << endl;
	cout << "Mutlithread time consumed to process the numbers:" << ((float)(cur_clock - pre_clock))/CLOCKS_PER_SEC << endl;
#endif 

	return 0;
}
#endif

#if 0
// single thread version
int _tmain(int argc, _TCHAR* argv[])
{
#if PROFILING_STATS
	clock_t pre_clock = clock();
	clock_t cur_clock;
	float timeToProcessInterval;
#endif

	try {
		IntervalCounter &ic = IntervalCounterImp(SWEEPLINE);
		ic.SetIntervals("extents.txt");

#ifdef PROFILING_STATS
		cur_clock = clock();
		timeToProcessInterval = (float) (cur_clock - pre_clock);
		pre_clock = cur_clock;
#endif

		BigTextInputFile numFile("numbers.txt");

#ifdef _DEBUG
		BigTextOutputFile numResult("expected.txt");
#endif

		const size_t toReadLines = 4096;
		vector<unsigned int> values, results;
		string text;
		while (numFile.ReadLines(toReadLines, text) > 0){
			DataParser::ParseValueStringToNumber(text, values);
			ic.GetCounters(values, results);
			copy(results.begin(),
				 results.end(),
				 ostream_iterator<unsigned int>(cout,"\n"));
#ifdef _DEBUG
			numResult.WriteResults(results);
#endif
			assert(values.size() == results.size());
			values.clear();
			results.clear();
		}
	}
	catch (std::exception &e) {
		cout << e.what() << endl;
	}

#ifdef PROFILING_STATS
	cur_clock = clock();
	cout << "Time consumed to process intervals" << timeToProcessInterval/CLOCKS_PER_SEC << endl;
	cout << "Single thread time consumed to process the numbers:" << ((float)(cur_clock - pre_clock))/CLOCKS_PER_SEC << endl;
#endif

	return 0;
}
#endif