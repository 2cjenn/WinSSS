// class of myrand  www.agner.org

#ifndef __MYRAND__
#define __MYRAND__

#pragma once

class MyRand
{
public:
	MyRand(long int seed);
	~MyRand(void);

	enum constants {                     // define parameters
    KK = 17, JJ = 10, R1 = 13, R2 =  9};

public:
	void RandomInit(long int seed);      // initialization
	int IRandom(int min, int max);       // get integer random number in desired interval
	double Random();                     // get floating point random number
	
protected:
	int p1, p2;                          // indexes into buffer
	unsigned long randbuffer[KK];        // history buffer

};

#endif
