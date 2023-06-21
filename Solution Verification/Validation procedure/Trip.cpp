#include "Trip.h"

Trip::Trip(Params* params)
{
	params_ = params;
	size_ = 0;
	demand_ = 0;
	dist_ = 0.0;
	arcDist_ = 0.0;
}

Trip::Trip(Trip* t)
{
	for (int i = 0; i < t->size_; i++)
	{
		this->trip_.push_back(t->trip_.at(i));
	}
	this->params_ = t->params_;
	this->size_ = t->size_;
	this->demand_ = t->demand_; 
	this->dist_ = t->dist_;
	this->arcDist_ = t->arcDist_;
	this->chromt_ = t->chromt_;
	this->chromp_ = t->chromp_;
	this->newChromt_ = t->newChromt_;
	this->newChromp_ = t->newChromp_;
}

Trip::~Trip()
{ 

}


void Trip::addCluster(cluster* c)
{
	size_++;
	demand_ += c->allDemand;
	trip_.push_back(c);

}