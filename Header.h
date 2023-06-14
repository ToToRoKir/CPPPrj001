#pragma once
#include <random>
#include <chrono>
#include <mutex>

using namespace std::chrono;

const unsigned int _MAXRND_ = 100;
const unsigned int _MAX_PHIL_ = 5;

void synth_out(char* pChar);


class Fork
{
private:
public:
	int _iNumber;
	std::mutex m; // Fork
	Fork() : _iNumber(0) {};
	Fork(int _i): _iNumber(_i){};
	void setNumber(int _i) { _iNumber = _i; };
	~Fork() {};
};

class Philosophie 
{
private:

public:
	int _iPosition;
	Fork* fleft;
	Fork* fright;

	int eatCount;
	//	long unsigned int waitTime;
	//	long unsigned int startWait;
	milliseconds waitTime;
	milliseconds startWait;
	int _iRnd;


	Philosophie():fleft(nullptr), fright(nullptr), eatCount(0), waitTime(0ms), startWait(0ms), _iPosition(0) {};
	Philosophie(int _iPos, Fork* fl, Fork* fr) 
	{
		this->_iPosition = _iPos;  
		this->fleft = fl; 
		this->fright = fr; 
		this->eatCount = 0; 
		this->waitTime = 0ms; //underlying integer value is 5.; 
		this->startWait = 0ms; //underlying integer value is 5.;  
		this->_iPosition = 0;
	};

	void setPhils(int _iPos, Fork* fl, Fork* fr) { this->_iPosition = _iPos;  this->fleft = fl; this->fright = fr; };
	void eat();
	void think();

//	friend std::ostream& operator<<(std::ostream& os, const Philosophie& ph);


	~Philosophie() {};
};

class MyPhilosophie : public Philosophie
{
public:
	volatile bool stopFlag;
	MyPhilosophie() : Philosophie{} { stopFlag = false; };
	MyPhilosophie(int _iPos, Fork* fl, Fork* fr) : Philosophie{ _iPos, fl, fr } { stopFlag = false; }

	void run()
	{
		while(!stopFlag)
		{ 
			think();
			std::lock_guard<std::mutex> lg(this->fleft->m);
			{
				std::cout << "Philosophie [" << this->_iPosition << "] get left fork!" << "\n";
				std::lock_guard<std::mutex> lg(this->fright->m);
				{
					std::cout << "Philosophie [" << this->_iPosition << "] get right fork!" << "\n";
					eat();
				}
			}

		}

		std::cout << "Philosophie [" << this->_iPosition << "] stopped!" << "\n";

	}

	void run_try()
	{
		while (!stopFlag)
		{
			think();
			//std::lock_guard<std::mutex> lg(this->fleft->m);
			std::lock(this->fleft->m, this->fright->m );

			std::lock_guard<std::mutex> lg1(this->fleft->m, std::adopt_lock);
			{
				std::cout << "Philosophie [" << this->_iPosition << "] get left fork!" << "\n";
				std::lock_guard<std::mutex> lg2(this->fright->m, std::adopt_lock);
				{
					std::cout << "Philosophie [" << this->_iPosition << "] get right fork!" << "\n";
					eat();
				}
			}

		}

		std::cout << "Philosophie [" << this->_iPosition << "] stopped!" << "\n";

	}

};