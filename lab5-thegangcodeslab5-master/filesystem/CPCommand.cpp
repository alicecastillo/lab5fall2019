#include "CPCommand.h"

#include <iostream>
using namespace std;

CPCommand::CPCommand(AbstractFileSystem* fileSys) : fs(fileSys) {}

int CPCommand::execute(std::string& CWD, std::string options) {
	AbstractFile* f = fs->openFile(CWD);
	if (f == nullptr) { // file creation failed
		cout << "failed to open directory" << endl;
		return directorydoesnotexist;
	}
	int argCheck = getArgs(options);
	if (argCheck != success) {
		fs->closeFile(f);
		return argCheck;
	}
	
	//see if file actually does exist to be copied
	std::string filePath = CWD + "/" + args[copyname];
	AbstractFile* file = fs->openFile(filePath);
	if (file == nullptr) { 
		cout << "Invalid file" << endl;
		fs->closeFile(file);
		fs->closeFile(f);
		return filenotfound;
	}

	//checks to see if path given is valid
	AbstractFile* pathCheck = fs->openFile(args[copypath]);
	if (pathCheck == nullptr) { //invalid path for copy
		cout << "Invalid destination" << endl;
		fs->closeFile(pathCheck);
		fs->closeFile(file);
		fs->closeFile(f);
		return invalidpath;
	}
	
	//request files from factory
	std::string copyFilePath = args[copypath] + "/" + args[copyname];
	AbstractFile* copyOfFile = cpf->createFile(file);
	fs->addFile(copyFilePath, copyOfFile);


	fs->closeFile(pathCheck);
	fs->closeFile(file);
	fs->closeFile(f);
	return success; //if no errors, return success
}
 
void CPCommand::displayInfo() {
	cout << "Copies files" << endl;
	cout << "Usage: cp <file to copy> <full path to destination>" << endl;
}


int CPCommand::getArgs(std::string options) {
	size_t firstSpace, lastSlash;
	args = new string[2];
	firstSpace = options.find(" ");
	lastSlash = options.find_last_of("/");
	
	if (firstSpace != options.npos) { //there may be a flag
		args[copyname] = options.substr(0, firstSpace);
		if (lastSlash != options.npos || options.substr(firstSpace + 1) == "root") {
			args[copypath] = options.substr(firstSpace+1);
		}
		else {
			cout << "No valid path given" << endl;
			return invalidpath;
		}
	}
	else {//no path is given
		return invalidargs;
	}

	return success;
}