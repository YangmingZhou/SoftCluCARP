#pragma once
#include <string>
#include <fstream>		
#include <iostream>		
#include <sstream>		


#include "Global.h"

class FileHandler
{
private:

	int setSelection_;

	static std::string currentInstanceName_;
	static std::string currentCheckInstanceName_;

	std::string checkPathOverview_;
	std::string filePathOverview_;
	std::string filePathInstance_;
	std::string checkPathInstance_;
	FILE* fpo_;
	FILE* checkfpo_;

	void createFilePathNextInstance(void);

	void createCheckPathNextInstance(void);

	void createFilePathSolutionOverview(void);
	void createTrack(void);

	void initOverview(void);
	void initOutputFiles(void);
public:

	std::string filePathSolutionOverview_;
	std::ofstream txtSolOverview_;
	std::string filePathTracker_;
	std::ofstream txtTrack_;

	FileHandler();
	~FileHandler();

	std::string getFilePathInstance(void);
	std::string getCheckPathInstance(void);
	static std::string getCurrentInstanceName(void);
	static std::string getCheckInstanceName(void);
};

