#pragma once

#include <vector>
#include "Params.h"

class Trip
{
	friend class Move;

private:

public:
	int size_;
	int demand_;
	double dist_;
	double arcDist_;
	vector <int> chromt_;
	vector <int> newChromt_;
	vector <pair<int, int>> chromp_;
	vector <pair<int, int>> newChromp_;
	Params* params_;
	vector < cluster* > trip_; 
	bool flag_ = false;

	Trip(Params*);
	Trip(Trip*);
	~Trip();
	void addCluster(cluster* c);

	inline int getSize(void) const
	{
		return size_;
	}

	inline cluster* getCluster(int it) const
	{
		return trip_.at(it);
	}

	inline int getSpareCapacity(void) const
	{
		return params_->vehicleCapacity - this->demand_;
	}

	inline void altSize(int diff)
	{
		size_ += diff;
	}

	inline void insertStop(cluster* n, int& i)
	{
		this->trip_.insert(trip_.begin() + i + 1, n);
		this->size_++;
	}

	bool calcArcDist()
	{
		double d = 0.0;
		for (int i = 0; i < chromp_.size() - 1; i++)
			d += params_->cli_all[chromt_[i]].ar_serviceCost01 + params_->ar_distanceNodes[chromp_[i].second][chromp_[i + 1].first];
		this->arcDist_ = d;
		return d;
	}

	inline double getDistance()
	{
		return dist_;
	}

	inline double getArcDistance()
	{
		return arcDist_;
	}
	inline void setFlag()
	{
		flag_ = true;
	}
	inline void resetFlag()
	{
		flag_ = false;
	}
	inline bool getFlag()
	{
		return flag_;
	}
};
