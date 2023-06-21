#pragma once

#include "Solution.h"
#include "Prove.h"
#include "CluVRPsol.h"
#include <fstream>
#include <iostream>


class CluVRPsolver
{
private:
	Solution* currentSol_;
	Prove* prove_;
	ifstream fichier2;
public:
	CluVRPsolver();
	~CluVRPsolver();

	void inputCheck(string nomInstance, Params* params);




	CluVRPsol* solve(string,Params*);
};