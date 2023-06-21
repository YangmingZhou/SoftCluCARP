#include "Params.h"

vector<cluster*> Params::getClientClusters()
{
	std::vector<cluster*> v;
	for (int i = 1; i < allCluster.size(); i++)
	{
		v.push_back(&allCluster.at(i));
	}
	return v;
}


void Params::preleveDonnees(string nomInstance)
{

	vector <Vehicle> tempI;
	double vc;
	string contenu, useless2;
	nbTotalServices = 0;
	totalDemand = 0;
	multiDepot = false;
	periodique = false;
	isTurnPenalties = false;

	if (type == 30 || type == 33)
	{

		getline(fichier, contenu);
		getline(fichier, contenu);
		fichier >> useless2;
		fichier >> useless2;
		fichier >> bestValue;
		fichier >> useless2;
		fichier >> useless2;
		fichier >> ar_NodesNonRequired;
		fichier >> useless2;
		fichier >> useless2;
		fichier >> ar_EdgesRequired;
		fichier >> useless2;
		fichier >> useless2;
		fichier >> ar_EdgesNonRequired;
		fichier >> useless2;
		fichier >> useless2;
		fichier >> clusterNum;
		fichier >> useless2;
		fichier >> useless2;
		fichier >> nbVehiculesPerDep;

		fichier >> useless2;

		fichier >> useless2;
		fichier >> vc;
		getline(fichier, contenu);
		getline(fichier, contenu);
		getline(fichier, contenu);
		getline(fichier, contenu);

		ar_NodesRequired = 0;
		ar_ArcsRequired = 0;
		ar_ArcsNonRequired = 0;
		ar_Edges = ar_EdgesRequired + ar_EdgesNonRequired;
		vehicleCapacity = vc;
		ar_InitializeDistanceNodes();
	}
	nbDays = 1;
	ancienNbDays = nbDays;
	nbDepots = 1; 
	nbClients = ar_ArcsRequired + ar_EdgesRequired + ar_NodesRequired;

	if (nbVehiculesPerDep == -1) throw string("WARNING : some type of instances do not specify a fleet size, please specify an иооч upper bound manually using -veh XX in the commandline");

	if (nbClients < 0 || nbClients > 1000000)
		throw string("ERROR WHEN READING : Number of services has not been correctly read. A very likely cause is the use of the wrong problem type for a given problem instance");

	cli_all = new Client[nbDepots + nbClients];

	for (int i = 0; i < nbClients + nbDepots; i++)
	{
		getClient(i, &cli_all[i]);
	}
	if (type == 30 || type == 33 || type == 35) 
	{
		ar_parseOtherLinesCARP();
		ar_computeDistancesNodes(); 

		getline(fichier, contenu);
		getline(fichier, contenu);
		cluster* clu = NULL;
		for (int i = 0; i < clusterNum + 1; i++)
		{
			clu = new cluster();
			getCluster(i, clu);
			allCluster.push_back(*clu);
		}

	}
}

bool compPredicate(pairB i, pairB j)
{
	return (i.myparams->timeCost[i.myInt][i.iCour] < i.myparams->timeCost[j.myInt][i.iCour]);
}

void Params::getCluster(int i, cluster* clu)
{
	clu->cluNum = i;
	clu->allDemand = 0;


	if (i < nbDepots)
	{
		clu->allClient.push_back(&cli_all[0]);
		clu->clientNum = 1;
		clu->allDemand += cli_all[0].demand;
		cli_all[0].clusterID = i;
	}
	else
	{
		string tempstring;
		int node0, node1;

		fichier >> tempstring;
		fichier >> tempstring;
		fichier >> clu->clientNum;

		fichier >> tempstring;
		fichier >> tempstring;

		for (int i = 0; i < clu->clientNum; i++)
		{
			fichier >> tempstring;
			fichier >> node0;
			fichier >> tempstring;
			fichier >> node1;
			fichier >> tempstring;
			int j;
			for (j = 0; j < nbClients + nbDepots; j++)
			{
				if (cli_all[j].ar_nodesExtr0 == node0 && cli_all[j].ar_nodesExtr1 == node1)
					break;
			}
			cli_all[j].clusterID = clu->cluNum;
			clu->allClient.push_back(&cli_all[j]);
			clu->allDemand += cli_all[j].demand;
		}

	}

}
void Params::getClient(int i, Client* myCli)
{

	string tempstring;
	pattern p;

	myCli->custNum = i;
	myCli->freq = 1;
	myCli->serviceDuration = 0;

	if (type == 30 || type == 33) 
	{
		myCli->ar_nodesExtr0 = -1;
		myCli->ar_nodesExtr1 = -1;
		myCli->serviceDuration = 0;

		if (i < nbDepots)
		{
			myCli->demand = 0;
			myCli->ar_nodeType = AR_DEPOT;
			myCli->ar_serviceCost01 = 0.;
			myCli->ar_serviceCost10 = 0.;
			myCli->freq = 0;
		}
		else
		{
			fichier >> tempstring;
			fichier >> myCli->ar_nodesExtr0;
			fichier >> tempstring;
			fichier >> myCli->ar_nodesExtr1;
			fichier >> tempstring;
			fichier >> tempstring;
			fichier >> myCli->ar_serviceCost01;
			myCli->ar_serviceCost10 = myCli->ar_serviceCost01;

			ar_distanceNodes[myCli->ar_nodesExtr0][myCli->ar_nodesExtr1] = myCli->ar_serviceCost01;
			ar_distanceNodes[myCli->ar_nodesExtr1][myCli->ar_nodesExtr0] = myCli->ar_serviceCost01;

			fichier >> tempstring;
			fichier >> myCli->demand;
			totalDemand += myCli->demand;
			myCli->ar_nodeType = AR_CLIENT_EDGE;
		}
	}
	if (type != 32 || i == 0)
	{
		p.dep = 0;
		p.cost = 0;
		p.pat = 1;
		myCli->visits.push_back(p);
	}

	if (i >= 1) nbTotalServices += myCli->freq;
}

Params::Params(string check,string nomInstance, string nomSolution, string nomBKS, int seedRNG, int type, int nbVeh, int nbDep) :type(type), nbVehiculesPerDep(nbVeh), nbDepots(nbDep)
{
	pathToCheck = check;
	pathToInstance = nomInstance;
	pathToSolution = nomSolution;
	pathToBKS = nomBKS;
	borne = 2.0;
	sizeSD = 10;

	seed = seedRNG;
	if (seed == 0)
		srand((unsigned int)time(NULL));
	else
		srand(seed);

	fichier.open(nomInstance.c_str());
	fichier2.open(check.c_str());

	if (fichier.is_open())
		preleveDonnees(nomInstance);
	else
		throw string(" Impossible to find instance file ");

}

Params::~Params(void)
{
	for (int i = 0; i < nbClients + nbDepots; i++)
	{

		delete[] timeCostAll[i];
	}
	delete[] timeCost;
	delete[] timeCostAll;
	delete[] cli;
	delete[] cli_all;
	allCluster.clear();

}




void Params::ar_InitializeDistanceNodes()
{
	if (ar_NodesNonRequired + ar_NodesRequired < 0 || ar_NodesNonRequired + ar_NodesRequired  > 1000000)
		throw string("ERROR WHEN READING : Number of nodes has not been correctly read. A very likely cause is the use of the wrong problem type for a given problem instance");

	vector <double> myTemp = vector <double>(ar_NodesNonRequired + ar_NodesRequired + 1);
	for (int i = 0; i <= ar_NodesNonRequired + ar_NodesRequired; i++)
		myTemp[i] = 1.e20;

	ar_distanceNodes.clear();
	for (int i = 0; i <= ar_NodesNonRequired + ar_NodesRequired; i++)
		ar_distanceNodes.push_back(myTemp);
}

void Params::ar_InitializeDistancePassNodes()
{
	vector <int> myTemp = vector <int>(ar_NodesNonRequired + ar_NodesRequired + 1);
	for (int i = 0; i <= ar_NodesNonRequired + ar_NodesRequired; i++)
		myTemp[i] = 0;

	ar_distancePassNodes.clear();
	for (int i = 0; i <= ar_NodesNonRequired + ar_NodesRequired; i++)
		ar_distancePassNodes.push_back(myTemp);
}

void Params::ar_computeDistancesNodes()
{
	ar_InitializeDistancePassNodes();

	for (int ii = 1; ii <= ar_NodesNonRequired + ar_NodesRequired; ii++)
	{
		ar_distanceNodes[ii][ii] = 0;
	}

	for (int k = 1; k <= ar_NodesNonRequired + ar_NodesRequired; k++)
	{
		for (int i = 1; i <= ar_NodesNonRequired + ar_NodesRequired; i++)
		{
			for (int j = 1; j <= ar_NodesNonRequired + ar_NodesRequired; j++)
			{
				if (ar_distanceNodes[i][k] + ar_distanceNodes[k][j] < ar_distanceNodes[i][j])
				{
					ar_distanceNodes[i][j] = ar_distanceNodes[i][k] + ar_distanceNodes[k][j];
					ar_distancePassNodes[i][j] = k;
				}
			}
		}
	}
	double d;
	timeCostAll = new double* [nbClients + nbDepots];
	for (int i = 0; i < nbClients + nbDepots; i++)
	{
		timeCostAll[i] = new double[nbClients + nbDepots];
		for (int j = 0; j < nbClients + nbDepots; j++)
		{
			d = min(min(ar_distanceNodes[cli_all[i].ar_nodesExtr0][cli_all[j].ar_nodesExtr0],
				ar_distanceNodes[cli_all[i].ar_nodesExtr0][cli_all[j].ar_nodesExtr1]),
				min(ar_distanceNodes[cli_all[i].ar_nodesExtr1][cli_all[j].ar_nodesExtr0],
					ar_distanceNodes[cli_all[i].ar_nodesExtr1][cli_all[j].ar_nodesExtr1]));

			timeCostAll[i][j] = d;
		}
	}
}


void Params::ar_parseOtherLinesCARP()
{
	string contenu;
	string useless;
	int startNode;
	int endNode;
	double myCost;

	getline(fichier, contenu);
	if (ar_EdgesNonRequired >= 0) getline(fichier, contenu);

	for (int k = 0; k < ar_EdgesNonRequired; k++)
	{
		fichier >> useless;
		fichier >> startNode;
		fichier >> useless;
		fichier >> endNode;
		fichier >> useless;
		fichier >> useless;
		fichier >> myCost;
		ar_distanceNodes[startNode][endNode] = myCost;
		if (type != 35) 
			ar_distanceNodes[endNode][startNode] = myCost;
		else
			fichier >> ar_distanceNodes[endNode][startNode];
	}

	fichier >> useless;
	fichier >> useless;
	fichier >> startNode;
	cli_all[0].ar_nodesExtr0 = startNode;
	cli_all[0].ar_nodesExtr1 = startNode;


}
