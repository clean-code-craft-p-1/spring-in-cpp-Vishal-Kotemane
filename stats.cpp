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

//Definition of IAlerter
IAlerter::IAlerter()
{
	alert_type = ALERTYPE::MAX_ALERT;
}

IAlerter::~IAlerter()
{
}

bool IAlerter::check(const float val) const
{
	bool retValue = false;
	if (val > getThreshold())
	{
		retValue = true;
	}
	return retValue;
}

const float IAlerter::getThreshold() const
{
	return threshold;
}

//Definition of EmailAlert
EmailAlert::EmailAlert():emailSent(false)
{
	alert_type = ALERTYPE::EMAIL;
}

EmailAlert::~EmailAlert()
{
}

//Definition of LEDAlert
LEDAlert::LEDAlert():ledGlows(false)
{
	alert_type = ALERTYPE::LED;
}

LEDAlert::~LEDAlert()
{
}

//Definition of StatsAlerter
StatsAlerter::StatsAlerter()
{
}

StatsAlerter::StatsAlerter(const float maxthreshold, std::vector<IAlerter*> InplistOfAlerters)
{
	this->listOfAlerters = InplistOfAlerters;
}

StatsAlerter::~StatsAlerter()
{
}

//This function iterates through the list
void StatsAlerter::checkAndAlert(std::vector<float> Inplist)
{
	for (auto itr : listOfAlerters)
	{
		for (auto i : Inplist)
		{
			if (itr->check(i))
			{
				setAlert(itr);
			}
		}
	}
}

//This function sets the value
void StatsAlerter::setAlert(IAlerter* alerter)
{
	switch (alerter->alert_type)
	{
	case ALERTYPE::EMAIL:
	{
		EmailAlert* emailalert = static_cast<EmailAlert*>(alerter);
		emailalert->emailSent = true;
		break;
	}
	case ALERTYPE::LED:
	{
		LEDAlert* ledAlert = static_cast<LEDAlert*>(alerter);
		ledAlert->ledGlows = true;
		break;
	}
	case ALERTYPE::MAX_ALERT:
		std::cout << "Programming error!" << std::endl;
		break;
	}
}

