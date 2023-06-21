#pragma once

#include <vector>
#include "Params.h"
#include"Trip.h"
using namespace std;

class Solution
{
	friend class Move;

public:
	Params* params_;
	double totalDist_;
	double totalArcDist_;
	double vehicleNum_;
	double vehicleCap_;
	vector< Trip* > vTrips_;
	bool flag_ = false;

	Solution(Params *);
	Solution(Solution*);
	~Solution();

	void addTrip(Trip* t);
	inline Trip* getTrip(int i) const
	{
		return vTrips_.at(i);
	}
	inline int getnTrips(void) const
	{
		return (int)vTrips_.size();
	}
private:

};

