#pragma once

#include "Params.h"
#include "Solution.h"

class  Prove
{
public:
	 Prove(Params *);
	~ Prove();
	bool run(Solution*);
	int yekrun(int i, int j, vector<pair<int, int>> &vec,int flag);
private:
	Params* params_;
	Solution* sol_;

};

 