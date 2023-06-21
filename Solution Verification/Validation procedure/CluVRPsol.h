#pragma once
#include "Solution.h"

struct CluVRPsol
{
	Solution *sol_;
	Params *params_;
	bool flag_;

	CluVRPsol(Solution*, Params*, bool);
	~CluVRPsol();
};

