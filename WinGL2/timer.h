#ifndef TIMER_H
#define TIMER_H

#include "utility.h"

class Timer{
public:
	LARGE_INTEGER frequency;        // ticks per second
    LARGE_INTEGER start, stop;           // ticks
    double elapsedTime;
	double memory[10];
	Timer(){
		elapsedTime = 0.0;
	}
	
	
	void StartTimer(){
		 QueryPerformanceFrequency(&frequency);
		 QueryPerformanceCounter(&start);
	}
	
	double StopTimer(){
		QueryPerformanceCounter(&stop);
		elapsedTime = (stop.QuadPart - start.QuadPart) * 1000.0 / frequency.QuadPart;
		return elapsedTime;
	}

};

#endif