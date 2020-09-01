/*
Author: Jon Shidal
Purpose: CSE 332 lab 5
*/

#include "TouchCommand.h"
#include<iostream>

using namespace std;

TouchCommand::TouchCommand(AbstractFileFactory* fileFactory, AbstractFileSystem* fileSys) : 
	ff(fileFactory), fs(fileSys) { }

int TouchCommand::execute(std::string& CWD, std::string options) {
	string filename;
	bool makeRO = setRO(options);
	if (!makeRO && options.find("-") != string::npos) {
		cout << "Invalid command given" << endl;
		return invalidcommandprompt;
	}
	else if (makeRO) {
		std::string newOptions = options.substr(0, options.find_first_of(' '));
		options = newOptions;
	}

	if (options.find_last_of('/') != string::npos) {
		// create file with filename only, allows for creating files with directories not currently the working directory
		filename = options.substr(options.find_last_of('/') + 1, string::npos);
	}
	else {
		filename = options;
	}

	//can't make directories read only
	if (makeRO) {
		if (filename.find(".") == string::npos) {
			cout << "Cannot make directories read only" << endl;
			return invalidcommandprompt;
		}
	}

	AbstractFile * f = ff->createFile(filename);
	if (f == nullptr) { // file creation failed
		cout << "failed to create file" << endl;
		return failedtocreatefile;
	}
	string fullPath = CWD;
	fullPath += '/';
	fullPath += options;
	int result;
	AbstractFile* newProxy = nullptr;
	if (makeRO) {
		newProxy = pff->createFile(f, makeRO);
		if (newProxy == nullptr) {
			fs->closeFile(f);
			delete f;
			delete newProxy;
			return failedtocreatefile;
		}
		result = fs->addFile(fullPath, newProxy); //add the proxy 
		if (result != success) {
			delete f;
			delete newProxy;
		}
		fs->closeFile(f);
		return success;
	}
	else {
		result = fs->addFile(fullPath, f);
	}
	if (result != success) {
		cout << "failed to add file to file system, deleting file" << endl;
		delete f;
		return failedtoadd;
	}
	return result;
}
void TouchCommand::displayInfo() {
	cout << "touch creates a file" << endl;
	cout << "Usage: touch <filename>" << endl;
	cout << "Touch can create a READ-ONLY file-> Optional Usage: touch <filename> [-ro]" << endl;
}

bool TouchCommand::setRO(std::string options) {
	size_t dashIndex = options.find("-");
	if (dashIndex != std::string::npos) {
		std::string argstring = options.substr(dashIndex, string::npos);
		if (argstring == "-ro" && argstring.length() == 3) {
			return true;
		}
	}
	return false;
}

