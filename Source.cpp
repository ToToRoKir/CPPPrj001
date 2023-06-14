#include <stdlib.h>     
#include <iostream>
#include <random>
#include <chrono>
#include <thread>

#include "Header.h"



void Philosophie::eat()
{
	using namespace std::chrono;
	milliseconds ms = duration_cast<milliseconds>( system_clock::now().time_since_epoch() );

	waitTime += ms - startWait;
	std::cout << "Philosophie " << _iPosition << " is eating." << "\n";

	try
	{

//		unsigned int microseconds = static_cast<unsigned int>(rand() % _MAXRND_);
//		std::this_thread::sleep_for( std::chrono::microseconds(microseconds) );
		unsigned int milliseconds = static_cast<unsigned int>(rand() % _MAXRND_);
		std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));

		//std::this_thread::sleep_for(std ::chrono::seconds(1) );
		//std::this_thread::sleep_for(microseconds);
		//std::chrono::seconds(1)
		//Sleep(microseconds);

	}
	catch (const std::exception& except)
	{
		std::cout << "Philosophie [" << _iPosition << "] is go down for exceptions (eating)!!!" << "\n";
	}
//count for eating
	eatCount++;

	std::cout << "Philosophie [" << _iPosition << "] is finished eating." << "\n";

}

void Philosophie::think()
{
	using namespace std::chrono;

	std::cout << "Philosophie [" << _iPosition << "] is thinking." << "\n";

	try
	{

//		unsigned int microseconds = static_cast<unsigned int>(rand() % _MAXRND_);
//		std::this_thread::sleep_for(std::chrono::microseconds(microseconds));
		unsigned int milliseconds = static_cast<unsigned int>(rand() % _MAXRND_);
		std::this_thread::sleep_for( std::chrono::milliseconds(milliseconds) );

	}
	catch (const std::exception& except)
	{
		std::cout << "Philosophie [" << _iPosition << "] is go down for exceptions (thinking)!!!" << "\n";
	}

	std::cout << "Philosophie [" << _iPosition << "] is hungry." << std::endl;

	this->startWait = duration_cast<milliseconds>(system_clock::now().time_since_epoch());

}

void test()
{

}

int main()//int argc, char* argv[])
{
	Fork* fleft = nullptr;
	Fork* fright = nullptr;

	MyPhilosophie arrPhils[_MAX_PHIL_];
	Fork arrForks[_MAX_PHIL_+1];

//
	milliseconds ms = 0ms;
	milliseconds gl_timeToWait = 0ms;
	milliseconds gl_startWait = duration_cast<milliseconds>(system_clock::now().time_since_epoch());

	std::cout << " START: [" << gl_startWait.count() << "]" << std::endl;
	//

	//init Phils
	if (_MAX_PHIL_ == 1)
	{ 
		arrForks[0].setNumber(0);
		arrForks[1].setNumber(1);

		arrPhils[0].setPhils(0, &(arrForks[1]), &(arrForks[0]));
	}
	else
	{
		for (int _i = 0; _i <= _MAX_PHIL_ - 1; _i++)
		{
			//set fork number 
			arrForks[_i].setNumber(_i);

			fright = &(arrForks[_i]);
			fleft = ((_i == _MAX_PHIL_ - 1) ? &arrForks[0] : &arrForks[_i + 1]);

			arrPhils[_i].setPhils(_i, fleft, fright);

		}
	}

	//cout Phils stats
	for (int _i = 0; _i <= _MAX_PHIL_ - 1; _i++)
	{
		auto elapsed = arrPhils[_i].waitTime;
		std::cout << " Philosopher " << arrPhils[_i]._iPosition << " eate " << arrPhils[_i].eatCount << " and waited " << arrPhils[_i].startWait.count() << "\n";
	}

	//init & run Threads
	std::thread ptrTreads[_MAX_PHIL_];
	MyPhilosophie* ptrPyhil = nullptr;

	for (int _i = 0; _i <= _MAX_PHIL_ -1 ; _i++)
	{
//ToDo: &(arrPhils[_i]) - ??????????????????????????????????????????????????????????
		//ptrTreads[_i] = std::thread ( test );
		//ptrTreads[_i] = std::thread ( &(arrPhils[_i])->run);
		ptrPyhil = &(arrPhils[_i]);
		ptrTreads[_i] = std::thread([ptrPyhil]() { ptrPyhil->run_try(); });
		
	};

	std::this_thread::sleep_for(5000ms);

	//init Threads stopping
	for (int _i = 0; _i <= _MAX_PHIL_ - 1; _i++)
	{
		arrPhils[_i].stopFlag = true; 
	}

	//	std::thread* ptrTread = nullptr;
	for (int _i = 0; _i <= _MAX_PHIL_ - 1; _i++)
	{
		if (ptrTreads[_i].joinable())
		{
			ptrTreads[_i].join();
		}
	}


	//cout Phils stats
	for (int _i = 0; _i <= _MAX_PHIL_ - 1; _i++)
	{
		auto elapsed = arrPhils[_i].waitTime;
		std::cout << " Philosopher " << arrPhils[_i]._iPosition << " eate " << arrPhils[_i].eatCount << " and waited " << arrPhils[_i].waitTime.count() << "\n";
	}


/*
	std::this_thread::sleep_for(500ms);

	ms = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
	gl_timeToWait += ms - gl_startWait;
	gl_startWait = ms;

	std::this_thread::sleep_for(500ms);

	ms = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
	gl_timeToWait += ms - gl_startWait;

	std::cout << " TIMER: [" << gl_timeToWait.count() << "]" << std::endl;
	std::cout << " TIME:  [" << ms.count() << "]" << std::endl;
*/
//	return EXIT_SUCCESS;

}