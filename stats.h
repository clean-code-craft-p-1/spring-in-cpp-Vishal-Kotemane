//****************************************************************************//
//                                                                            //
//   Filename   : stats.h                                                     //
//                                                                            //
//   Description: Contains Stats Funcitons                                    //
//                                                                            //
//   Copyright  : Philips Medical Systems Nederland B.V., 2023.               //
//                                                                            //
//****************************************************************************//
#ifndef STATS_H
#define STATS_H

#include <vector>

namespace Statistics {
    // define the Stats structure here. See the tests to infer its properties
    struct Stats
	{
		double average;
		double max;
		double min;
	};
	
    Stats ComputeStatistics(const std::vector<double>& inpvec );
}

//Definition of IAlerter
enum class ALERTYPE { EMAIL = 0 , LED = 1, MAX_ALERT = 2 };

class IAlerter
{
public:
	IAlerter();
	~IAlerter();
	bool check(const float val) const;
	const float getThreshold() const;
	ALERTYPE alert_type;
private:
	const float threshold = 10.2f;
};

//Definition of EmailAlert
class EmailAlert :public IAlerter
{
public:
	EmailAlert();
	~EmailAlert();
	bool emailSent;
private:
	
};

//Definition of LEDAlert
class LEDAlert :public IAlerter
{
public:
	LEDAlert();
	~LEDAlert();
	bool ledGlows;
private:
	
};

//Definition of StatsAlerter
class StatsAlerter
{
public:
	StatsAlerter();
	StatsAlerter(const float maxthreshold, std::vector<IAlerter*> InplistOfAlerters);
	~StatsAlerter();
	void checkAndAlert(std::vector<float> Inplist);
	void setAlert(IAlerter* alerter);
private:
	std::vector<IAlerter*> listOfAlerters;
};

#endif // !STATS_H