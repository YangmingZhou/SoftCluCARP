#ifndef PARAMS_H
#define PARAMS_H

#include <string>
#include <vector>
#include <list>
#include <fstream>
#include <iostream>
#include "math.h"
#include <time.h>
#include <algorithm>
#include "Client.h"
#include "Vehicle.h"
//#include "Trip.h"

using namespace std;

template <class C> void FreeClear(C& cntr) {
	for (typename C::iterator it = cntr.begin();
		it != cntr.end(); ++it) {
		delete* it;
	}

	cntr.clear();
}

class Params;
class Vehicle;

struct pairB
{
	int myInt;
	int iCour;
	Params* myparams;
};

struct cluster
{
	int clientNum;
	int cluNum;
	double allDemand;
	vector<Client*> allClient;
	vector<int> node;
	bool flag = false;
};

class Params
{
public:
	int clusterNum;
	int seed;
	string pathToInstance;
	string pathToCheck;
	string pathToSolution;
	string pathToBKS;
	vector<cluster> allCluster;
	vector<cluster*> getClientClusters();

	int type;
	bool multiDepot;
	bool periodique;
	bool isTurnPenalties;

	int ar_NodesRequired; 
	int ar_NodesNonRequired;
	int ar_EdgesRequired;
	int ar_EdgesNonRequired;
	int ar_ArcsRequired;
	int ar_ArcsNonRequired;
	int ar_Edges;
	void ar_InitializeDistanceNodes();
	void ar_InitializeDistancePassNodes();
	vector < vector < double > > ar_distanceNodes;
	vector < vector < int > > ar_distancePassNodes;
	double bestValue = 0;
	int nbClients;
	int nbTotalServices;
	double totalDemand;
	int nbDays;
	int ancienNbDays;
	int nbVehiculesPerDep;
	int nbDepots;
	double vehicleCapacity;
	Client* cli;
	Client* cli_all;
	double totalDemand1;
	double** timeCost;
	double** timeCostAll;
	double borne;
	int sizeSD;
	ifstream fichier;
	ifstream fichier2;
	void preleveDonnees(string nomInstance);
	void ar_parseOtherLinesCARP();
	void ar_computeDistancesNodes();
	void getClient(int i, Client* myCli);
	Params(string check, string nomInstance, string nomSolution, string nomBKS, int seedRNG, int type, int nbVeh, int nbDep);
	void getCluster(int i, cluster* clu);
	~Params(void);
};
#endif

