#include "CluVRPsolver.h"
#include "Global.h"

using namespace std;
CluVRPsolver::CluVRPsolver()
{
	currentSol_ = nullptr;

}

CluVRPsolver::~CluVRPsolver()
{

}
void CluVRPsolver::inputCheck(string nomInstance, Params* params)
{
	string contenu, useless2;

	getline(fichier2, contenu);

	for (int i = 0; i < params->nbVehiculesPerDep ; i++)
	{
		getline(fichier2, contenu);
		fichier2 >> useless2;
		fichier2 >> currentSol_->getTrip(i)->demand_;
		fichier2 >> useless2;
		fichier2 >> currentSol_->getTrip(i)->arcDist_;
		int j = 0;
		std::vector<cluster*> v = params->getClientClusters();
		cluster* c = nullptr;
		getline(fichier2, contenu);
		getline(fichier2, contenu);
		while (1) {

			fichier2>>useless2;
			if (stoi(useless2) == 0)
				break;
			for (int k = 0; k < v.size(); k++)
			{
				if (v[k]->cluNum == stoi(useless2)) {
					c = v.at(k);
				}
			}
			currentSol_->vTrips_.at(i)->insertStop(c, j);
			j++;
			getline(fichier2, contenu);

			
		}
		getline(fichier2, contenu);
		getline(fichier2, contenu);
		getline(fichier2, contenu);
		getline(fichier2, contenu);

		
		j = 0;
		while (1) {
			fichier2 >> useless2;
			int arcNum;
			fichier2 >> arcNum;
			currentSol_->getTrip(i)->chromt_.push_back(arcNum);
			if (arcNum == 0) {
				j++;
				if (j == 2) {
					break;
				}
			}
			fichier2 >> useless2;
			fichier2 >> useless2;
		}
		fichier2 >> useless2;
		fichier2 >> useless2;
		fichier2 >> useless2;
		fichier2 >> useless2;
		getline(fichier2, contenu);
		getline(fichier2, contenu);
		j = 0;
		
		while (1) {
			int left, right;
			fichier2 >> useless2;
			fichier2 >> left;
			fichier2 >> useless2;
			fichier2 >> right;
			pair<int, int> and1(left,right);
			
			currentSol_->getTrip(i)->chromp_.push_back(and1);
			if (left == 1&&right==1) {
				j++;
				if (j == 2) {
					break;
				}
			}
			getline(fichier2, contenu);
		}
		getline(fichier2, contenu);
		getline(fichier2, contenu);
		getline(fichier2, contenu);
		getline(fichier2, contenu);
	}

}
CluVRPsol* CluVRPsolver::solve(string check,Params* params)
{

	CluVRPsol* cluVRPsol = nullptr;
	currentSol_ = new Solution(params);
	prove_ = new Prove(params);
	bool flag = false;
	
	for (int i = 0; i < params->nbVehiculesPerDep; i++)
	{
		Trip* t = new Trip(params);

		t->addCluster(&params->allCluster.at(0));
		t->addCluster(&params->allCluster.at(0));
		currentSol_->addTrip(t);
	}


	fichier2.open(check.c_str());
	if (fichier2.is_open())
		inputCheck(check,params);
	else
		throw string(" Impossible to find instance file ");

	flag = prove_->run(currentSol_);
	if (flag == false) {
		cout << "success!" << endl;
	}

	delete prove_;
	delete currentSol_;
	return cluVRPsol;
}