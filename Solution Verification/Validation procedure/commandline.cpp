#include "commandline.h"

commandline::commandline(FileHandler*& fileHandler)
{
	fileHandler_ = fileHandler;
	cpu_time = 100000;
	seed = 0;
	type = 30;
	nbVeh = -1;
	nbDep = -1;
	command_ok = true;
	instance_name = FileHandler::getCurrentInstanceName();
	check_name = FileHandler::getCheckInstanceName();
	output_name = fileHandler->filePathSolutionOverview_;
	BKS_name = fileHandler->filePathTracker_; 
}

void commandline::getNextInstance()
{
	instance_name = fileHandler_->getFilePathInstance();
}

void commandline::getNextCheckInstance()
{
	check_name = fileHandler_->getCheckPathInstance();
}
commandline::~commandline(){}

string commandline::get_path_to_instance()
{
	return instance_name;
}
string commandline::get_path_to_check()
{
	return check_name;
}
string commandline::get_path_to_solution()
{
	return output_name;
}

string commandline::get_path_to_BKS()
{
	return BKS_name;
}

int commandline::get_type()
{
	return type;
}

int commandline::get_nbVeh()
{
	return nbVeh ;
}

int commandline::get_nbDep()
{
	return nbDep ;
}

int commandline::get_cpu_time()
{
	return cpu_time;
}

int commandline::get_seed()
{
	return seed;
}