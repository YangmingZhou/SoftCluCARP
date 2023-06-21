#include <algorithm>
#include <stdlib.h>
#include <stdio.h> 
#include <string>
#include "commandline.h"
#include "Solution.h"
#include "FileHandler.h"
#include "Prove.h"
#include "CluVRPsolver.h"
using namespace std;
int main()
{
	FileHandler* fileHandler; fileHandler = new FileHandler();
	commandline* commandlin = new commandline(fileHandler);
	CluVRPsol* cluVRPsol = nullptr;
	while (1)
	{
		commandlin->getNextInstance(); 
		commandlin->getNextCheckInstance();
		Params* mesParametres = new Params(commandlin->get_path_to_check(), commandlin->get_path_to_instance(), commandlin->get_path_to_solution(), commandlin->get_path_to_BKS(), commandlin->get_seed(), commandlin->get_type(), commandlin->get_nbVeh(), commandlin->get_nbDep());//²ÎÊýÉèÖÃ
		CluVRPsolver* cluVRPsolver = new CluVRPsolver();
		string check = commandlin->get_path_to_check();
		cluVRPsol = cluVRPsolver->solve(check, mesParametres); 
		delete mesParametres;
		delete cluVRPsolver;
	}
	delete fileHandler;
	delete commandlin;  
	
	return 0;
}