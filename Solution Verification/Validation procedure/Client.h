#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <vector>
#include <iostream>
#include "math.h"
using namespace std ;

struct pattern {
	int pat;
	int dep;
	double cost;
};

enum ClientType {AR_DEPOT, AR_CLIENT_NODE, AR_CLIENT_EDGE, AR_CLIENT_ARC};

class Client
{
	public:
	
	int clusterID;
    int custNum ;
	double serviceDuration ;
	double demand ;
	int freq ;
	ClientType ar_nodeType ;
	int ar_nodesExtr0 ;
	int ar_nodesExtr1 ;
	double ar_serviceCost01 ;
	double ar_serviceCost10 ;
    vector <pattern> visits ;
	vector <int> visitsDyn ;
	Client();

	~Client(void);
};

#endif
