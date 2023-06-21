#include "FileHandler.h"
#include<iostream>
#include <direct.h>

using namespace std;

std::string FileHandler::currentInstanceName_;
std::string FileHandler::currentCheckInstanceName_;

void FileHandler::createFilePathNextInstance(void)
{
	char temp[30];
	char temp0[30];
	fscanf_s(fpo_, "%s", &temp, sizeof(temp));
	std::ostringstream temp2;
	temp2 << temp;

	currentInstanceName_ = temp2.str();

	if (currentInstanceName_ == "STOP")
	{
		exit(0);
	}

	std::ostringstream buff1;

	if (setSelection_ == 0)
	{
		buff1 << "\\instances\\egl-s3-B_clustered58\\" << currentInstanceName_;

	}
	else if (setSelection_ == 1)
	{
		buff1 << "\\instances\\egl-s3-C_clustered61\\" << currentInstanceName_;
	}
	else if (setSelection_ == 2)
	{
		buff1 << "\\instances\\egl-s3-C_clustered65\\" << currentInstanceName_;
	}
	else if (setSelection_ == 3)
	{
		buff1 << "\\instances\\egl-s4-A_clustered48\\" << currentInstanceName_;
	}
	else if (setSelection_ == 4)
	{
		buff1 << "\\instances\\egl-s4-A_clustered51\\" << currentInstanceName_;
	}
	else if (setSelection_ == 5)
	{
		buff1 << "\\instances\\egl-s4-B_clustered69\\" << currentInstanceName_;
	}
	else if (setSelection_ == 6)
	{
		buff1 << "\\instances\\egl-s4-C_clustered84\\" << currentInstanceName_;
	}
	//cout << "currentInstanceName_=" << currentInstanceName_ << endl;
	char cwd1[300];
	filePathInstance_ = _getcwd(cwd1, 300) + buff1.str();
}
void FileHandler::createCheckPathNextInstance(void)
{
	char temp0[100];
	fscanf_s(checkfpo_, "%s", &temp0, sizeof(temp0));
	std::ostringstream temp3;
	temp3 << temp0;
	currentCheckInstanceName_ = temp3.str();
	if (currentCheckInstanceName_ == "STOP")
	{
		exit(0);
	}
	std::ostringstream buff2;

	if (setSelection_ == 0)
	{
		buff2 << "\\instances\\egl-s3-B_clustered58\\" << currentCheckInstanceName_;
	}
	else if (setSelection_ == 1)
	{
		buff2 << "\\instances\\egl-s3-C_clustered61\\" << currentCheckInstanceName_;
	}
	else if (setSelection_ == 2)
	{
		buff2 << "\\instances\\egl-s3-C_clustered65\\" << currentCheckInstanceName_;
	}
	else if (setSelection_ == 3)
	{
		buff2 << "\\instances\\egl-s4-A_clustered48\\" << currentCheckInstanceName_;
	}
	else if (setSelection_ == 4)
	{
		buff2 << "\\instances\\egl-s4-A_clustered51\\" << currentCheckInstanceName_;
	}
	else if (setSelection_ == 5)
	{
		buff2 << "\\instances\\egl-s4-B_clustered69\\" << currentCheckInstanceName_;
	}
	else if (setSelection_ == 6)
	{
		buff2 << "\\instances\\egl-s4-C_clustered84\\" << currentCheckInstanceName_;
	}
	char cwd2[300];
	checkPathInstance_ = _getcwd(cwd2, 300) + buff2.str();
}
void FileHandler::createFilePathSolutionOverview(void)
{
	std::ostringstream buff;
	if (setSelection_ == 0)
	{
		buff << "\\solutions\\sol-egl-s3-B_clustered58-Full." << SUFFIX <<".txt";
	}
	else if (setSelection_ == 1)
	{
		buff << "\\solutions\\sol-egl-s3-C_clustered61-Full." << SUFFIX << ".txt";
	}
	else if (setSelection_ == 2)
	{
		buff << "\\solutions\\sol-egl-s3-C_clustered65-Full." << SUFFIX << ".txt";
	}
	else if (setSelection_ == 3)
	{
		buff << "\\solutions\\sol-egl-s4-A_clustered48-Full." << SUFFIX << ".txt";
	}
	else if (setSelection_ == 4)
	{
		buff << "\\solutions\\sol-egl-s4-A_clustered51-Full." << SUFFIX << ".txt";
	}
	else if (setSelection_ == 5)
	{
		buff << "\\solutions\\sol-egl-s4-B_clustered69-Full." << SUFFIX << ".txt";
	}
	else if (setSelection_ == 6)
	{
		buff << "\\solutions\\sol-egl-s4-C_clustered84-Full." << SUFFIX << ".txt";
	}
	char cwd[300];
	filePathSolutionOverview_ = _getcwd(cwd, 300) + buff.str();

	cout << "filePathSolutionOverview_ =" << filePathSolutionOverview_  << endl;
	txtSolOverview_.open(filePathSolutionOverview_);
}

void FileHandler::createTrack(void)
{
	std::ostringstream buff;
	if (setSelection_ == 0)
	{
		buff << "\\solutions\\track-egl-s3-B_clustered58-Full." << SUFFIX << ".txt";
	}
	else if (setSelection_ == 1)
	{
		buff << "\\solutions\\track-egl-s3-C_clustered61-Full." << SUFFIX << ".txt";
	}
	else if (setSelection_ == 2)
	{
		buff << "\\solutions\\track-egl-s3-C_clustered65-Full." << SUFFIX << ".txt";
	}
	else if (setSelection_ == 3)
	{
		buff << "\\solutions\\track-egl-s4-A_clustered48-Full." << SUFFIX << ".txt";
	}
	else if (setSelection_ == 4)
	{
		buff << "\\solutions\\track-egl-s4-A_clustered51-Full." << SUFFIX << ".txt";
	}
	else if (setSelection_ == 5)
	{
		buff << "\\solutions\\track-egl-s4-B_clustered69-Full." << SUFFIX << ".txt";
	}
	else if (setSelection_ == 6)
	{
		buff << "\\solutions\\track-egl-s4-C_clustered84-Full." << SUFFIX << ".txt";
	}
	char cwd[300];
	filePathTracker_ = _getcwd(cwd, 300) + buff.str();

	txtTrack_.open(filePathTracker_);
}

void FileHandler::initOverview(void)
{
	string instSet;
	bool again;

	do{
		again = false;

		if (__argc == 1)
		{
			cout << "	***	Welcome to the SoftCluCarp - solver.	***" << endl << endl << "Select the set of test instances you want to run :" << endl << \
				"0 = egl-s3-B_clustered58" << endl << \
				"1 = egl-s3-C_clustered61" << endl << \
				"2 = egl-s3-C_clustered65" << endl << \
				"3 = egl-s4-A_clustered48" << endl << \
				"4 = egl-s4-A_clustered51" << endl << \
				"5 = egl-s4-B_clustered69" << endl << \
				"6 = egl-s4-C_clustered84" << endl << \
				"Press 9 to quit" << endl << endl;

			scanf_s("%d", &setSelection_);
		}
		else
		{
			if (!sscanf_s(__argv[1], "%i", &setSelection_)) { cout << "ERROR while reading argv"; };
		}

		if (setSelection_ == 0)
		{
			instSet = "egl-s3-B_clustered58";
		}
		else if (setSelection_ == 1)
		{
			instSet = "egl-s3-C_clustered61";
		}
		else if (setSelection_ == 2)
		{
			instSet = "egl-s3-C_clustered65";
		}
		else if (setSelection_ == 3)
		{
			instSet = "egl-s4-A_clustered48";
		}
		else if (setSelection_ == 4)
		{
			instSet = "egl-s4-A_clustered51";
		}
		else if (setSelection_ == 5)
		{
			instSet = "egl-s4-B_clustered69";
		}
		else if (setSelection_ == 6)
		{
			instSet = "egl-s4-C_clustered84";
		}
		else if (setSelection_ == 9)
		{
			exit(0);
		}
		else
		{
			cout << "ERROR no valid instance selected.  Choose again.";
			again = true;
		}
	} while (again);

	std::ostringstream buff;
	buff << "\\instances\\" << instSet << "\\overview.txt";
	std::ostringstream buff2;
	buff2 << "\\instances\\" << instSet << "\\overview2.txt";
	char cwd[300];
	filePathOverview_ = _getcwd(cwd, 300) + buff.str();
	char cwd2[300];
	checkPathOverview_ = _getcwd(cwd2, 300) + buff2.str();
	cout << "filePathOverview_=" << filePathOverview_ << endl;
	if (fopen_s(&fpo_, filePathOverview_.c_str(), "r")) { cout << "ERROR overview file could not be found"; }
	if (fopen_s(&checkfpo_, checkPathOverview_.c_str(), "r")) { cout << "ERROR overview file could not be found"; }
}


void FileHandler::initOutputFiles(void)
{
	createFilePathSolutionOverview();
	createTrack();
}

FileHandler::FileHandler()
{
	this->initOverview();
	this->initOutputFiles();
}

FileHandler::~FileHandler()
{
	fclose(fpo_);				
	txtSolOverview_.close();	
	txtTrack_.close();		

	delete fpo_;
}	

std::string FileHandler::getFilePathInstance(void)
{
	createFilePathNextInstance();
	return filePathInstance_;
}
std::string FileHandler::getCheckPathInstance(void)
{
	createCheckPathNextInstance();
	return checkPathInstance_;
}
std::string FileHandler::getCurrentInstanceName(void)
{
	return currentInstanceName_;
}
std::string FileHandler::getCheckInstanceName(void)
{
	return currentCheckInstanceName_;
}