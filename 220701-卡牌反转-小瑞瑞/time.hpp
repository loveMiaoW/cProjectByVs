#pragma once
#include "myHead.h"
class myTime {
public:
	static bool timer(time_t num, int id) {
		static time_t startTime[10];
		time_t endTime = clock();
		if (endTime - startTime[id] >= num) {
			startTime[id] = endTime;
			return true;
		}
		return false;
	}
protected:

};