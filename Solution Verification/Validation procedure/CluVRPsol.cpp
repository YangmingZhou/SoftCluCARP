#include "CluVRPsol.h"


CluVRPsol::CluVRPsol(Solution *sol, Params *params, bool flag)
{
	sol_ = sol;
	params_ = params;
	flag_ = flag;
}

CluVRPsol::~CluVRPsol()
{
	delete sol_;

}
