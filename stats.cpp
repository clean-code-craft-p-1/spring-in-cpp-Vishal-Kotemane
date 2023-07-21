#include "stats.h"
#include <numeric>
#include <algorithm>
#include <iostream>

using namespace Statistics;
Stats Statistics::ComputeStatistics(const std::vector<double>& inpVec) {
    //Implement statistics here
	Stats temp = { 0 };
	
	if ( false == inpVec.empty())
	{
		temp.average = std::accumulate(inpVec.begin(), inpVec.end(), 0.0) / inpVec.size();
		auto itr = std::max_element(inpVec.begin(), inpVec.end());
		temp.max = *itr;

		itr = std::min_element(inpVec.begin(), inpVec.end());
		temp.min = *itr;
	}
	else
	{
		temp.average = NAN;
		temp.max = NAN;
		temp.min = NAN;
	}
	return temp;

}
