#ifndef COMMAND_LINE_H
#define COMMAND_LINE_H

#include <iostream>
#include <cstdlib>
#include <string>
#include "FileHandler.h"

using namespace std;

class commandline
{
    private:
        bool command_ok;
        int cpu_time;
		int seed;
		int type;
		int nbVeh ;
		int nbDep ;
        string instance_name;
        string check_name;
		string output_name;
		string BKS_name;
        FileHandler *fileHandler_;
    public:
        commandline(FileHandler*&);
        void getNextInstance();
        void getNextCheckInstance();
        ~commandline();
        string get_path_to_instance();
        string get_path_to_check();
        string get_path_to_solution();
        string get_path_to_BKS();
        int get_cpu_time();
		int get_type();
		int get_nbVeh();
		int get_nbDep();
        int get_seed();
};
#endif
