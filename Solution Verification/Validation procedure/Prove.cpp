#include "Prove.h"

Prove::Prove(Params* params)
{
	params_ = params;
}

Prove::~Prove()
{
}
int Prove::yekrun(int i, int j, vector<pair<int,int>> &vec,int flag)
{
	if (i == j) return flag;
	if (params_->ar_distancePassNodes[i][j] == 0)
	{
		vec.emplace_back(i, j);
		flag = 1;
	}
	else {
		yekrun(i, params_->ar_distancePassNodes[i][j],vec,flag);
		yekrun(params_->ar_distancePassNodes[i][j], j,vec,flag);
		flag = 1;
	}
}
bool Prove::run(Solution* sol)
{
	bool flag = false;
	sol_ = sol;
	

	int count = 0;
	for (int i = 0; i < params_->nbVehiculesPerDep; i++)
	{
		count += sol_->getTrip(i)->getSize() - 2;
	}
	if (count > params_->allCluster.size() - 1)
	{
		std::cout << "There are clusters being served multiple times\n";
		flag = true;
	}
	if (count < params_->allCluster.size() - 1)
	{
		std::cout << "There are clusters that are not served\n";
		flag = true;
	}

	for (int i = 0; i < params_->nbVehiculesPerDep; i++)
	{
		int count = 0;
		for (int j = 1; j < sol_->getTrip(i)->size_ - 1; j++)
			count += sol_->getTrip(i)->trip_[j]->clientNum;
		if (count != sol_->getTrip(i)->chromt_.size() - 2)
			cout << "Mismatch between the number of clusters and customers of the i-th car " << i << endl;
	}
	if (params_->nbVehiculesPerDep != sol_->getnTrips())
	{
		std::cout << "Vehicle count and route mismatch" << params_->nbVehiculesPerDep << "   " << sol_->getnTrips() << std::endl;
		flag = true;
	}

	//Testing constraints£¨1c)
	for (int i = 0; i < params_->nbVehiculesPerDep; i++) 
	{
		int q = 0;
		int fg = 0;
		int fgg = 0;
		int r = 0;
		vector<int> S;
		for (int j = 1; j < sol_->getTrip(i)->getSize() - 1; j++)
		{
			q = 0;
			for (int k = 0; k < sol_->getTrip(i)->getCluster(j)->clientNum; k++) {
				if (sol_->getTrip(i)->getCluster(j)->allClient.at(k)->ar_nodesExtr0 == 1\
					|| sol_->getTrip(i)->getCluster(j)->allClient.at(k)->ar_nodesExtr1 == 1)
				{
					q++;
					if (q == sol_->getTrip(i)->getCluster(j)->clientNum) {
						S.clear();
						fg += 1;
					}
				}
			}
		}
		fgg = fg;
		while (fg!=sol_->getTrip(i)->getSize() - 2)
		{
			
			fg = fgg;
			S.clear();  
			r = (rand() % (params_->ar_NodesNonRequired - 2 - 2 + 1)) + 2;
			for (int k = 0; k < r; k++) {
				int rr = (rand() % (params_->ar_NodesNonRequired - 2 + 1)) + 2;
				if (!std::count(S.begin(), S.end(), rr)) {
					S.push_back(rr);
				}
				else
					k--;
			}
			for (int j = 1; j < sol_->getTrip(i)->getSize() - 1; j++) {
				for (int k = 0; k < sol_->getTrip(i)->getCluster(j)->clientNum; k++) {

					
					if (sol_->getTrip(i)->getCluster(j)->allClient.at(k)->ar_nodesExtr0!=1\
						&& sol_->getTrip(i)->getCluster(j)->allClient.at(k)->ar_nodesExtr1!=1\
						&& std::count(S.begin(), S.end(), sol_->getTrip(i)->getCluster(j)->allClient.at(k)->ar_nodesExtr0) \
						&& std::count(S.begin(), S.end(), sol_->getTrip(i)->getCluster(j)->allClient.at(k)->ar_nodesExtr1))
					{
						fg ++;
						break;
					}
				}
			}

		}
	
		int yek = 0;
		int com = 0;
		if (S.empty()) 
		{
			break;
		}
		for (int k = 0; k < sol_->getTrip(i)->chromp_.size(); k++)
		{
			if ((std::count(S.begin(), S.end(), sol_->getTrip(i)->chromp_[k].first) \
				|| std::count(S.begin(), S.end(), sol_->getTrip(i)->chromp_[k].second)))
			{
				com++;
			}
			if ((std::count(S.begin(), S.end(), sol_->getTrip(i)->chromp_[k].first) \
				&& std::count(S.begin(), S.end(), sol_->getTrip(i)->chromp_[k].second)))
			{
				com--;
			}

		}
		vector<pair<int, int>> vec;
		int flag1 = 0;
		for (int k = 0; k < sol_->getTrip(i)->chromp_.size() - 1;k++) {
			vec.clear();
			if (yekrun(sol_->getTrip(i)->chromp_[k].second, sol_->getTrip(i)->chromp_[k+1].first,vec,flag1)) {
				for (int l = 0; l < vec.size(); l++) {
					if ((std::count(S.begin(), S.end(), vec[l].first) \
						|| std::count(S.begin(), S.end(), vec[l].second)))
					{
						yek++;
					}
					if ((std::count(S.begin(), S.end(), vec[l].first) \
						&& std::count(S.begin(), S.end(), vec[l].second)))
					{
						yek--;
					}
				}
			}
		}
		if (yek + com - 2 < 0) {
			cout << "Violation of constraint(1c)£¡" << endl;
			flag = true;
		}
		
	}
	
	//Testing constraints£¨1d£©
	
	for (int i = 0; i < params_->nbVehiculesPerDep; i++) {
		vector<pair<int, int>> vec;
		int flag1 = 0;
		for (int k = 0; k < sol_->getTrip(i)->chromp_.size() - 1; k++) {

			vec.emplace_back(sol_->getTrip(i)->chromp_[k].first, sol_->getTrip(i)->chromp_[k].second);
			yekrun(sol_->getTrip(i)->chromp_[k].second, sol_->getTrip(i)->chromp_[k + 1].first, vec, flag1);

		}
		int temp1 = 0;
		int it1 = 0;
		for (int k = 1; k < vec.size(); k++) {
			temp1 = vec[k].first;
			for (int j = 1; j < vec.size(); j++) {
				if (temp1 == vec[j].first)
					it1++;
				if (temp1 == vec[j].second)
					it1++;
			}

			if (it1 % 2) {
				cout << "Violation of restraint (1d)" << endl;
				flag = true;
			}
		}
		
	}

	
	for (int i = 0; i < params_->nbVehiculesPerDep; i++)
	{
		int demand = 0;
		for (int j = 0; j < sol_->getTrip(i)->getSize(); j++)
		{
			demand = demand + sol_->getTrip(i)->getCluster(j)->allDemand;
		}
		if (demand > params_->vehicleCapacity)
		{
			std::cout << "car" << i << "Service Overrun\n";
			flag = true;
		}
	}



	double totalArcDis = sol->totalArcDist_;

	for (int i = 0; i < params_->nbVehiculesPerDep; i++)
	{
		double arcDis = sol_->getTrip(i)->arcDist_;
		sol_->getTrip(i)->calcArcDist();
		
		if (fabs(arcDis - sol_->getTrip(i)->arcDist_) > 0.0001)
		{
			std::cout << "car" << i << "customer distance error\n";
			flag = true;
		}
	}

	if (fabs(totalArcDis - sol_->totalArcDist_) > 0.0001)
	{
		std::cout << "Vehicle customer distance error\n";
		flag = true;
	}

	for (int i = 0; i < params_->nbVehiculesPerDep; i++)
	{
		if (sol_->getTrip(i)->chromt_.size() != sol_->getTrip(i)->chromp_.size())
		{
			cout << "chromt_ and chromp_ do not match" << endl;
			flag = true;
		}
		for (int j = 0; j < sol_->getTrip(i)-> chromt_.size(); j++)
		{
			if(params_->cli_all[sol_->getTrip(i)->chromt_[j]].ar_nodesExtr0 != sol_->getTrip(i)->chromp_[j].first\
				&& params_->cli_all[sol_->getTrip(i)->chromt_[j]].ar_nodesExtr0 != sol_->getTrip(i)->chromp_[j].second)
			{
				cout << "chromt_ and chromp_ do not match" << endl;
				flag = true;
			}
		}
	}

	return flag;

}