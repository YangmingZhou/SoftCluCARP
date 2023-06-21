#include  "Solution.h"

using namespace std;


Solution::Solution(Params* params)
{
	params_ = params;
	vehicleNum_ = params->nbVehiculesPerDep;
	totalDist_ = 0.0;
	totalArcDist_ = 0.0;
	vehicleCap_ = params->vehicleCapacity;
}

Solution::Solution(Solution* s)
{
	this->params_ = s->params_;
	this->vehicleNum_ = s->vehicleNum_;
	this->totalDist_ = s->totalDist_;
	this->totalArcDist_ = s->totalArcDist_;
	this->vehicleCap_ = s->vehicleCap_;
	for (int i = 0; i < s->vTrips_.size(); i++)
	{
		//Trip* newT = new Trip(s->vTrips_.at(i));
		Trip* newT = new Trip(s->vTrips_.at(i));
		this->vTrips_.push_back(newT);
		//delete newT;
	}
}

Solution::~Solution()
{
	FreeClear(vTrips_);
}


void Solution::addTrip(Trip* t)
{
	vTrips_.push_back(t);
	totalDist_ += t->dist_;
}


