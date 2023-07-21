//****************************************************************************//
//                                                                            //
//   Filename   : stats.cpp                                                   //
//                                                                            //
//   Description: Contains Stats Funcitons                                    //
//                                                                            //
//   Copyright  : Philips Medical Systems Nederland B.V., 2023.               //
//                                                                            //
//****************************************************************************//
#include "stats.h"
#include <numeric>
#include <limits>
#include <algorithm>
#include <iostream>

using namespace Statistics;
#define CUSTOM_NAN (std::numeric_limits<double>::quiet_NaN())
Stats Statistics::ComputeStatistics(const std::vector<double>& inpVec) {
    //Implement statistics here
	Stats temp = { 0 };
	
	if (!inpVec.empty())
	{
		temp.average = std::accumulate(inpVec.begin(), inpVec.end(), 0.0) / inpVec.size();
		auto itr = std::max_element(inpVec.begin(), inpVec.end());
		temp.max = *itr;

		itr = std::min_element(inpVec.begin(), inpVec.end());
		temp.min = *itr;
	}
	else
	{
		temp.average = CUSTOM_NAN;
		temp.max = CUSTOM_NAN;
		temp.min = CUSTOM_NAN;
	}
	return temp;

}
